/*
 * Unpacks and decodes frames/headers.
 */

#ifndef MP3_DECODER_H
#define MP3_DECODER_H

#include "types.hpp"
#include <vector>
#include "tables.hpp"
#include "mp3.hpp"
#include "id3.hpp"
#include <tlm>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>


class hardware_functions : public sc_core::sc_module {
public:
    hardware_functions(sc_core::sc_module_name);

	tlm_utils::simple_target_socket<hardware_functions> cpu_tsoc;
	tlm_utils::simple_initiator_socket<hardware_functions> hardware_functions_isoc;
	
	
protected:
	
	void frequency_inversion(int gr, int ch);
	void synth_filterbank(int gr, int ch);
	void imdct(int gr, int ch);

    typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t; 
	void b_transport(pl_t&, sc_core::sc_time&); 
	void msg(const pl_t&);  	
      
    std::vector<float> package;
	fixed_point samples2[2][2][576];
 	fixed_point fifo[2][1024];
 	fixed_point prev_samples[2][32][18];
 	
 	int block_type[2][2];
	int counter=0;
	unsigned char gr=0,ch=0;
 
};



#endif	/* MP3_DECODER_H */

