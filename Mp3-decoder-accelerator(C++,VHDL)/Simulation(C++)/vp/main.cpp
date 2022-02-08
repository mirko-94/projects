/*
 * A simplistic MPEG-1 layer 3 decoder.
 */
#include "types.hpp"
#include <systemc>
#include <fstream>
#include <stdio.h>
#include <alsa/asoundlib.h> 
#include <vector>
#include <iostream>
#include "vp.hpp"
#include "cpu.hpp"
#define ALSA_PCM_NEW_HW_PARAMS_API

int sc_main(int argc, char **argv) { 
    vp uut("uut",argv);
	sc_start(1, sc_core::SC_SEC);
  
	return 0;
}
