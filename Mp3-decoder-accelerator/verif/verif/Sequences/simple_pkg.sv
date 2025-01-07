
package simple_pkg;

    import uvm_pkg::*;      // import the UVM library
    `include "uvm_macros.svh" // Include the UVM macros   
    
    import axi_lite_agent_pkg::axi_lite_item;
    import bram_agent_pkg::bram_item;
    import imdct_simple_pkg::imdct_item;
    
    import axi_lite_agent_pkg::axi_lite_sequencer;
    import bram_agent_pkg::bram_sequencer;
    import imdct_simple_pkg::imdct_sequencer;

    `include "axi_lite_base_seq.sv"
    `include "bram_base_seq.sv"
    `include "imdct_base_seq.sv"
    `include "axi_lite_seq.sv"
    `include "bram_seq.sv"
    `include "imdct_simple_seq.sv"

    endpackage 
