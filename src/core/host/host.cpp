#include "dependencies/std_include.hpp"
#include "host.hpp"

namespace host
{
	void __cdecl sv_set_config_string(int index, const char* value)
	{
		reinterpret_cast<decltype(&sv_set_config_string)>(0x00589C20)(2482, "uiScript_startSingleplayer");
		return reinterpret_cast<decltype(&sv_set_config_string)>(0x00589C20)(index, value);
	}

	void initialize()
	{
		utils::hook::call(0x0053B430, &sv_set_config_string); 

		utils::hook::retn(0x0053C0A0); // ScrCmd_SetMoveSpeedScale
	}
}