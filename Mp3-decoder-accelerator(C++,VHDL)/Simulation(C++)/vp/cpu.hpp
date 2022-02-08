#ifndef _CPU_H_
#define _CPU_H_

#include "types.hpp"
#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include "id3.hpp"
#include "mp3.hpp"
#include "hardware_functions.hpp"
#include "xing.hpp"
#include <alsa/asoundlib.h>


class cpu:

	public sc_core::sc_module {

		public:
			cpu(sc_core::sc_module_name, char **arg);

			tlm_utils::simple_initiator_socket<cpu> hardware_functions_isoc;
			tlm_utils::simple_initiator_socket<cpu> mem_isoc;

		protected:

			void proces();
		
			std::vector<unsigned char> file;
			float pack[2304];
			char **arg1;

			typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;
	};

	
std::vector<unsigned char> get_file(const char *dir);
	
std::vector<id3> get_id3_tags(std::vector<unsigned char> &buffer, unsigned &offset);


#endif
