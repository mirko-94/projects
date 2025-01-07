class bram_driver extends uvm_driver #(bram_item);
  
  	`uvm_component_utils(bram_driver)
  	
	logic [31:0] address;
     
  	// virtual interface reference
  	virtual interface bram_if vif;
  
  	imdct_config cfg;
  
	// constructor
	function new(string name = "bram_driver", uvm_component parent = null);
  		super.new(name, parent);
	endfunction

	function void connect_phase(uvm_phase phase);
		super.connect_phase(phase);
      	if (!uvm_config_db#(virtual bram_if)::get(this, "*", "bram_if", vif))
      	`uvm_fatal("NOVIF",{"virtual interface must be set for: ",get_full_name(),".vif"})
   	endfunction : connect_phase
   

	// process item
	task run_phase(uvm_phase phase);
     
      forever begin
	      
		@(posedge vif.clock)begin	   
	        
	         address = vif.s_addr_bram;
	         	    
	         if(vif.s_en_bram)begin
		         
		         if(vif.s_addr_bram < 576)begin

		            seq_item_port.get_next_item(req);
		            req.address = address;
		            seq_item_port.item_done();

		            seq_item_port.get_next_item(req);
		            `uvm_info(get_type_name(), $sformatf("Driver sending...\n%s", req.sprint()), UVM_HIGH)
		            
		            vif.s_din_bram = req.in_data;
		            seq_item_port.item_done();
		            		  		            		            
		         end 	       
			 end 
	       
		end 	    
	      
      end 
      
   	endtask : run_phase

endclass : bram_driver
