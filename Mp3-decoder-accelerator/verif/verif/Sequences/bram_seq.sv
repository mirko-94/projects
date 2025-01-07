class bram_seq extends bram_base_seq;

	`uvm_object_utils(bram_seq)
	
	function new(string name = "bram_seq");
		super.new(name);
   	endfunction

  	virtual task body();
  	
  	bram_item req;
  	
  	req = bram_item::type_id::create("req");
  	
  		forever begin
  	
	  		start_item(req);
		
			req.in_data = 2;
		
			finish_item(req);
		end	  	
	endtask : body
endclass : bram_seq
