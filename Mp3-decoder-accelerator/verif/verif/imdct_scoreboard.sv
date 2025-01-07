`uvm_analysis_imp_decl(_axi_lite)
`uvm_analysis_imp_decl(_bram)

class imdct_scoreboard extends uvm_scoreboard;
	
	// control fileds
   	bit checks_enable = 1;
   	bit coverage_enable = 1;
  
	uvm_analysis_imp_axi_lite#(axi_lite_item, imdct_scoreboard) axi_lite_collected_port;
	uvm_analysis_imp_bram#(bram_item, imdct_scoreboard) bram_collected_port;

  	int num_of_data; //brojac za bram 

	`uvm_component_utils_begin(imdct_scoreboard)
      `uvm_field_int(checks_enable, UVM_DEFAULT)
      `uvm_field_int(coverage_enable, UVM_DEFAULT)
   	`uvm_component_utils_end

	function new(string name = "imdct_scoreboard", uvm_component parent);
		super.new(name,parent);
		axi_lite_collected_port = new("axi_lite_collected_port", this);
		bram_collected_port = new("bram_collected_port", this);
	endfunction

	function void report_phase(uvm_phase phase);
      `uvm_info(get_type_name(), $sformatf("Imdct scoreboard examined: %0d transactions", num_of_data), UVM_LOW);
   	endfunction : report_phase


	function void write_axi_lite(axi_lite_item axi_tr);
	axi_lite_item axi_tr_clone;
	$cast(axi_tr_clone, axi_tr.clone());
 	if(checks_enable) begin
         // do actual checking here
         // ...
         // ++num_of_tr;
	end
	endfunction : write_axi_lite

	function void write_bram(bram_item bram_tr);
	bram_item bram_tr_clone;
	$cast(bram_tr_clone, bram_tr.clone());
 	if(checks_enable) begin
         // do actual checking here
         // ...
         // ++num_of_tr;
	end
	endfunction : write_bram


endclass;