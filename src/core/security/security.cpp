#include "dependencies/std_include.hpp"
#include "security.hpp"

namespace security
{
	constexpr auto OVERFLOW_PASSWORD{ "aUmwdwevwDnr3ude4" };
	auto rb_draw_stretch_pic_rotate_original = reinterpret_cast<decltype(&rb_draw_stretch_pic_rotate)>(0x00438CF0);
	auto sv_packet_event_original = reinterpret_cast<decltype(&sv_packet_event)>(0x0058AD71);
	auto sv_drop_client_original = reinterpret_cast<decltype(&sv_drop_client)>(0x00585E30);
	
	void __cdecl net_defer_packet_to_client(game::netadr_t *net_from, game::msg_t *net_message)
	{
		if (net_message->cursize < 0 || net_message->cursize > 1404)
		{
			game::send_server_command(-1, utils::string::va("f \"^1Exploit attempt caught! %s\"", network::get_sender_string(*net_from).data()));
			return;
		}

		return reinterpret_cast<decltype(&net_defer_packet_to_client)>(0x00573290)(net_from, net_message);
	}
	
	void __cdecl sv_drop_client(game::client_t *drop, const char *reason, bool tellThem)
	{
		const auto client_num{ game::get_client_num(drop) };
		const auto return_address{ reinterpret_cast<std::uintptr_t>(_ReturnAddress()) };

		if (game::is_authed_user(client_num) && (reason && *reason || tellThem) && return_address != 0x00586591)
		{
			auto message{ "SV_DropClient called"s };
			if (reason && *reason) message.append(" with reason: "s + reason);
			game::send_server_command(client_num, "f \"" + message + "\"");
		}
		else
		{
			return sv_drop_client_original(drop, reason, tellThem);
		}
	}

	bool __cdecl callback_rb_draw_stretch_pic_rotate(game::Material* material)
	{
		const auto material_index = game::DB_GetMaterialIndex(material);
		if (material_index < 4096 && !material->info.hashIndex && material->techniqueSet && material->techniqueSet->name == "2d"s)
		{
			return false;
		}

		return true;
	}

	__declspec(naked) void rb_draw_stretch_pic_rotate()
	{
		__asm
		{
			pushad;
			mov ecx, dword ptr[ecx + 3];
			push ecx;
			call callback_rb_draw_stretch_pic_rotate;
			test al, al;
			pop ecx;
			popad;

			jz fix;

			retn;

		fix:
			jmp rb_draw_stretch_pic_rotate_original;
		}
	}

	void __cdecl callback_sv_packet_event(game::client_t* client)
	{
		game::send_server_command(-1, utils::string::va("f \"^1Freeze attempt caught! %s\"", network::get_sender_string(client->header.netchan.remoteAddress).data()));
	}
	
	__declspec(naked) void sv_packet_event()
	{
		__asm
		{
			test eax, eax; // client->reliableAcknowledge
			jge fix;

			pushad;
			push edi;
			call callback_sv_packet_event;
			pop edi;
			popad;

			push 0x0058AD85;
			retn;

		fix:
			jmp sv_packet_event_original;
		}
	}
	
	void initialize()
	{
		utils::hook::detour(&rb_draw_stretch_pic_rotate_original, &rb_draw_stretch_pic_rotate);
		utils::hook::detour(&sv_packet_event_original, &sv_packet_event);
		utils::hook::detour(&sv_drop_client_original, &sv_drop_client);

		utils::hook::call(0x0058AC3A, &net_defer_packet_to_client);
		
		utils::hook::set<std::uint8_t>(0x0058F3DD, 0x76); // SV_UpdateServerCommandsToClient
		utils::hook::set<std::uint8_t>(0x0058F415, 0x77); // SV_UpdateServerCommandsToClient_PreventOverflow
		
		command::on_command("mr", [](const auto& args, const auto& client)
		{
			if (std::atoi(args[1]) != game::sv_serverId_value)
				return true;

			const auto menu_index = utils::atoi(args[2]);
			const auto response = utils::string::to_lower(args[3]);

			if (menu_index == 2)
			{
				if (game::Dvar_FindVar("xblive_privatematch")->current.enabled || game::is_authed_user(client))
				{
					return false;
				}

				game::send_server_command(-1, utils::string::va("f \"^5'%s'^7 attempted to change their team.\"", client.name));
				return true;
			}
			else if (response == "endround")
			{
				if (client.header.netchan.remoteAddress.type == game::NA_LOOPBACK || game::is_authed_user(client))
				{
					return false;
				}

				game::send_server_command(-1, utils::string::va("f \"^5'%s'^7 attempted to end the game.\"", client.name));
				return true;
			}
				
			return false;
		});
		
		network::on_command("mstart", [](const auto&, const auto& target, const auto&)
		{
			if (game::NET_CompareBaseAdr(target, game::clc()->serverAddress))
			{
				return false;
			}

			return true;
		}); 
		
		network::on_command("requeststats", [](const auto&, const auto& target, const auto&)
		{
			if (game::CL_GetLocalClientConnectionState() == game::CA_CONNECTED
				&& game::NET_CompareBaseAdr(target, game::clc()->serverAddress))
			{
				return false;
			}

			return true;
		});
		
		network::on_command("joinParty", [](const auto& args, const auto& target, const auto&)
		{
			const auto new_sub_party_count = utils::atoi(args[7]);
			const auto password = args[8];
			
			if (new_sub_party_count < 18 || password == "pw"s + OVERFLOW_PASSWORD)
			{
				return false;
			}
			
			game::send_server_command(-1, utils::string::va("f \"^1RCE prevented! %s\"", network::get_sender_string(target).data())); 
			return true;
		});
		
		network::on_command("relay", [](const auto& args, const auto& target, const auto& msg)
		{
			const auto client_num = utils::atoi(args[1]);
			if (client_num >= 18)
			{
				game::send_server_command(-1, utils::string::va("f \"^1Crash attempt caught! %s\"", network::get_sender_string(target).data()));
				return true;
			}
				
			if (game::is_authed_user(client_num))
			{
				const auto packet = std::string{ msg.data + msg.readcount, static_cast<std::string::size_type>(msg.cursize - msg.readcount) }; 
				game::send_server_command(client_num, utils::string::va("f \"^1Relay packet '%s' prevented! %s\"", utils::string::strip(packet).data(), network::get_sender_string(target).data()));
				return true;
			}

			return false;
		});
	}
}