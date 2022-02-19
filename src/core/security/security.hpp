#pragma once
#include "dependencies/std_include.hpp"

namespace security
{
	void __cdecl sv_drop_client(game::client_t * drop, const char * reason, bool tellThem);
	void sv_packet_event();
	void rb_draw_stretch_pic_rotate();
	
	void initialize();
}