#ifndef _VP_HPP_
#define _VP_HPP_

#include "types.hpp"
#include <systemc>
#include "cpu.hpp"
#include "memory.hpp"
#include "hardware_functions.hpp"

class vp :
	sc_core::sc_module {
		
		public:
			vp(sc_core::sc_module_name, char **arg);

		protected:
			cpu cp;
			memory mem;
    			hardware_functions hw;
	};

#endif
