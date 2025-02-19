parameter integer C_S_AXI_ADDR_WIDTH = 5;
parameter integer C_S_AXI_DATA_WIDTH = 32;

class axi_lite_item extends uvm_sequence_item;
   
	rand bit [C_S_AXI_ADDR_WIDTH-1 : 0] address;
	rand bit [C_S_AXI_DATA_WIDTH-1 : 0] data;
	rand bit avalid;
	rand bit dvalid;
	rand bit read_write;
   
   	`uvm_object_utils_begin(axi_lite_item)
		`uvm_field_int(address, UVM_ALL_ON)
      	`uvm_field_int(data, UVM_ALL_ON)
      	`uvm_field_int(read_write, UVM_ALL_ON)
      	`uvm_field_int(avalid, UVM_ALL_ON)
      	`uvm_field_int(dvalid, UVM_ALL_ON)
   	`uvm_object_utils_end
      
   	constraint address_constraint {address inside {0, 4, 8, 12, 16, 20, 24, 28};}
   	
   	//constraint data_constraint {data <= 1;}	// P R O V E R I T I ! ! ! ! ! ! ! ! ! !
   	
   	function new(string name = "axi_lite_item");
		super.new(name);
   	endfunction 

endclass : axi_lite_item

