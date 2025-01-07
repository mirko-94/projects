class imdct_env extends uvm_env;
  
  	// component instance
  	axi_lite_agent agent_axi;
  	bram_agent agent_bram;
  	imdct_scoreboard scoreboard;
  	imdct_config cfg;
	`uvm_component_utils(imdct_env)

	// constructor
	function new(string name = "imdct_env", uvm_component parent = null);
  		super.new(name, parent);
	endfunction

	// build phase
	function void build_phase(uvm_phase phase);
  		super.build_phase(phase);

		if(!uvm_config_db#(imdct_config)::get(this, "", "imdct_config", cfg))
        	`uvm_fatal("NOCONFIG",{"Config object must be set for: ",get_full_name(),".cfg"})

  		agent_axi = axi_lite_agent::type_id::create("agent_axi", this);
  		agent_bram = bram_agent::type_id::create("agent_bram", this);
  		scoreboard = imdct_scoreboard::type_id::create("scoreboard", this);
  	   
	endfunction : build_phase

	// connect phase
	function void connect_phase(uvm_phase phase);
  		super.connect_phase(phase);
  	
		agent_bram.bram_mon.item_collected_port.connect(scoreboard.bram_collected_port);
        agent_axi.axi_monitor.item_collected_port.connect(scoreboard.axi_lite_collected_port);
        
    endfunction : connect_phase

endclass : imdct_env
