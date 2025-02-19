class test_simple extends test_base;

`uvm_component_utils(test_simple)

   axi_lite_seq seq_axi;
   bram_seq seq_bram;   
   
   function new(string name = "test_simple", uvm_component parent = null);
      super.new(name,parent);
   endfunction : new
   
   function void build_phase(uvm_phase phase);
      super.build_phase(phase);
      seq_axi = axi_lite_seq::type_id::create("seq_axi");
      seq_bram = bram_seq::type_id::create("bram_seq");
   endfunction : build_phase

   task run_phase(uvm_phase phase);
      phase.raise_objection(this);
      phase.phase_done.set_drain_time(this, 1000);
	      fork
	         seq_axi.start(env.agent_axi.axi_sequencer);	         	            
	         seq_bram.start(env.agent_bram.bram_seqr);	         
	      join_any              
      phase.drop_objection(this);
	endtask : run_phase

endclass : test_simple
