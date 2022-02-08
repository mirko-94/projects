#include "cpu.hpp"
#include "address.hpp"
#include <string>
#include <fstream>
#include <tlm_utils/tlm_quantumkeeper.h>
#include <vector>
#include "id3.hpp"
#include "mp3.hpp"
#include "hardware_functions.hpp"
#include "xing.hpp"
#include <alsa/asoundlib.h>
#define SIZE 257
#define DATA_COMPRESSION_RATIO 14.5

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;

SC_HAS_PROCESS(cpu);
cpu::cpu(sc_module_name name,char **arg):

sc_module(name) {	
	arg1=arg;
	SC_THREAD(proces);
}

void cpu::proces() { 
    sc_time loct;
	tlm_generic_payload pl;
	tlm_utils::tlm_quantumkeeper qk;
	qk.reset();


//---------------------------------------LOADING MP3 FILE------------------------------------------------	

	std::vector<unsigned char> buffer = get_file(arg1[1]);
    vector<float> help_vector;         
	unsigned offset = 0;
           
    cout<<"CPU: CODED MP3 FILE IS LOADED"<<endl;
    

//-----------------------------------CREATING DECODER----------------------------------------------------

    std::vector<id3> tags = get_id3_tags(buffer, offset);
	mp3 decoder(&buffer[offset]);


//----------------------------CPU: INITIALIZING ALSA SOUND LIBRARY---------------------------------------

	unsigned sampling_rate = 44100;
	unsigned channels = 2;
	cout<<"sampling_rate is: :"<<sampling_rate<<endl;
	cout<<"channels is:"<<channels<<endl;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *hw = NULL;
	snd_pcm_uframes_t frames = 128;

	if (snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
		exit(1);

	snd_pcm_hw_params_alloca(&hw);
	snd_pcm_hw_params_any(handle, hw);

	if (snd_pcm_hw_params_set_access(handle, hw, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
		exit(1);
	if (snd_pcm_hw_params_set_format(handle, hw, SND_PCM_FORMAT_FLOAT_LE) < 0)
		exit(1);
	if (snd_pcm_hw_params_set_channels(handle, hw, channels) < 0)
		exit(1);
	if (snd_pcm_hw_params_set_rate_near(handle, hw, &sampling_rate, NULL) < 0)
		exit(1);
	if (snd_pcm_hw_params_set_period_size_near(handle, hw, &frames, NULL) < 0)
		exit(1);
	if (snd_pcm_hw_params(handle, hw) < 0)
		exit(1);
	if (snd_pcm_hw_params_get_period_size(hw, &frames, NULL) < 0)
		exit(1);
	if (snd_pcm_hw_params_get_period_time(hw, &sampling_rate, NULL) < 0)
		exit(1);
	

//----------------------------------------DECODING-------------------------------------------------	

	while (decoder.is_valid() && buffer.size() > offset + decoder.get_header_size()) {
		decoder.init_header_params(&buffer[offset]);
		
		if (decoder.is_valid()) {
		
			decoder.init_frame_params(&buffer[offset]);
			
			for (int gr = 0; gr < 2; gr++) {
			
				for (int ch = 0; ch < 2; ch++)
					decoder.requantize(gr, ch);

				if (decoder.channel_mode == mp3::JointStereo && decoder.mode_extension[0])
					decoder.ms_stereo(gr);

				for (int ch = 0; ch < 2; ch++) {
					if (decoder.block_type[gr][ch] == 2 || decoder.mixed_block_flag[gr][ch])
						decoder.reorder(gr, ch);
					else decoder.alias_reduction(gr, ch);

					std::vector<float> package;
					std::vector<int> help_block;
				
					for(int x=0;x<2;x++)
						for(int y=0;y<2;y++)
							help_block.push_back(decoder.block_type[x][y]);
				
					cout<<"SENDING ARRAY FOR IMDCT TO MEMORY"<<endl;
					pl.set_address(ADDRESS_A);
					pl.set_command(TLM_WRITE_COMMAND);	
					pl.set_data_length(help_block.size());
					pl.set_data_ptr((unsigned char*)&help_block);
					pl.set_response_status (TLM_INCOMPLETE_RESPONSE);
	
					mem_isoc->b_transport(pl, loct);	
					qk.set_and_sync(loct);
					loct += sc_time(5, SC_NS);
					help_block.clear();
				

					for(int f=0;f<2;f++)
          				for(int h=0;h<576;h++)
          					for(int g=0;g<2;g++)
          						package.push_back(decoder.samples[f][g][h]);
		
		
					cout<<"SENDING SAMPLES TO MEMORY"<<endl;		
					pl.set_address(ADDRESS_B);
					pl.set_command(TLM_WRITE_COMMAND);	
					pl.set_data_length(package.size());
					pl.set_data_ptr((unsigned char*)&package);
					pl.set_response_status (TLM_INCOMPLETE_RESPONSE);
	
					mem_isoc->b_transport(pl, loct);	
					qk.set_and_sync(loct);
					loct += sc_time(5, SC_NS);
					package.clear();
	
					unsigned char a=(unsigned char)gr,b=(unsigned char)ch;
				
					cout<<"SENDING GR PARAMETER TO MEMORY"<<endl;
					pl.set_address(WRITE_PACKAGE);
					pl.set_command(TLM_WRITE_COMMAND);	
					pl.set_data_length(1);
					pl.set_data_ptr((unsigned char*)&a);
					pl.set_response_status(TLM_INCOMPLETE_RESPONSE);
				
					hardware_functions_isoc->b_transport(pl, loct);
					qk.set_and_sync(loct);
					loct += sc_time(5, SC_NS);	

					cout<<"SENDING CH PARAMETER TO MEMORY"<<endl;
					pl.set_address(WRITE_PACKAGE);
					pl.set_command(TLM_WRITE_COMMAND);	
					pl.set_data_length(1);
					pl.set_data_ptr((unsigned char*)&b);
					pl.set_response_status(TLM_INCOMPLETE_RESPONSE);
				
					hardware_functions_isoc->b_transport(pl, loct);
					qk.set_and_sync(loct);
					loct += sc_time(5, SC_NS);
		
	
					cout<<"RECEIVING DECODED PACKAGE"<<endl;
					pl.set_address(ADDRESS_B);
					pl.set_command(TLM_READ_COMMAND);
					pl.set_response_status (TLM_INCOMPLETE_RESPONSE);
				
        			mem_isoc->b_transport(pl, loct);
					qk.set_and_sync(loct);
					loct += sc_time(5, SC_NS);
	
					help_vector = *((vector<float>*)pl.get_data_ptr());
					int sz=help_vector.size();
					for (int i = 0; i < sz ; i++) {
						pack[i]=help_vector[i];
				
						if(i<20) cout<<pack[i]<<endl;
					}					
	
					cout<<help_vector.size()<<endl;
					help_vector.clear();
					cout<<""<<endl;
	
	
					int h=0;
					for (int i = 0; i < 2; i++)
						for (int j = 0; j < 576; j++)
							for (int k = 0; k < 2; k++)   //decoder.channels
								decoder.samples[i][k][j]=pack[h++];
		
				}	
			}
			offset += decoder.get_frame_size();
		}


//----------------------------------------STREAMING DECODED PACKAGE---------------------------------------------

		
		int e = snd_pcm_writei(handle, pack, 1152);
		if (e == -EPIPE)
			snd_pcm_recover(handle, e, 0);
//-------------------------------------------------------------------------------------------------------------			
	
	}
		snd_pcm_drain(handle);
        snd_pcm_close(handle);
}

std::vector<id3> get_id3_tags(std::vector<unsigned char> &buffer, unsigned &offset) {
	std::vector<id3> tags;
	int i = 0;
	bool valid = true;

	while (valid) {
		id3 tag(&buffer[offset]);
		valid = tag.is_valid(); //changed
		
		if (valid) {
			tags.push_back(tag);
			offset += tags[i++].get_id3_offset() + 10;
		}
	}

	return tags;
}

std::vector<unsigned char> get_file(const char *dir) {
	std::ifstream file(dir, std::ios::in | std::ios::binary | std::ios::ate);
	std::vector<unsigned char> buffer(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read((char *)buffer.data(), buffer.size());
	file.close();
	return buffer; //changed
}




