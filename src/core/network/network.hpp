#pragma once
#include "dependencies/std_include.hpp"

namespace network
{
	using callback = std::function<bool(const command::args&, const game::netadr_t&, game::msg_t&)>;
	
	std::string get_sender_string(const game::netadr_t & from);
	void on_command(const std::string & command, const callback & callback);
	void cl_dispatch_connectionless_packet();
	void initialize();
}