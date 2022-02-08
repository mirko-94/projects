#include "types.hpp"
#include "vp.hpp"

using namespace sc_core;

vp::vp(sc_module_name name, char **arg) :
	sc_module(name),
	cp("cpu", arg),
	hw("hardware_functions"),
	mem("memory")
{
	cp.mem_isoc.bind(mem.cpu_tsoc);
	cp.hardware_functions_isoc.bind(hw.cpu_tsoc);
	hw.hardware_functions_isoc.bind(mem.hardware_functions_tsoc);

	SC_REPORT_INFO("VP", "Platform is constructed");
}
