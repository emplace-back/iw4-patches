#include "dependencies/std_include.hpp"
#include "security.hpp"

namespace security
{
	auto rb_draw_stretch_pic_rotate_original = reinterpret_cast<decltype(&rb_draw_stretch_pic_rotate)>(0x00438CF0);
	auto sv_drop_client_original = reinterpret_cast<decltype(&sv_drop_client)>(0x00585E30);
	
	void __cdecl sv_update_server_commands_to_client(game::client_t* client, game::msg_t* msg)
	{
		if (client->reliableAcknowledge < 0)
		{
			game::for_each_authed_client(18, [=](const auto& index)
			{
				game::send_server_command(index, 
					utils::string::va("f \"Freeze attempt caught! from %s\"", network::get_sender_string(client->header.netchan.remoteAddress).data()));
			});
		}

		return reinterpret_cast<void(*)(game::client_t*, game::msg_t*, int)>(0x0058F400)(client, msg, 0x20000);
	}
	
	void __cdecl net_defer_packet_to_client(game::netadr_t *net_from, game::msg_t *net_message)
	{
		if (net_message->cursize < 0 || net_message->cursize > 1404)
		{
			game::for_each_authed_client(18, [=](const auto& index)
			{
				game::send_server_command(index, utils::string::va("f \"Exploit attempt caught! from %s\"", network::get_sender_string(*net_from).data()));
			});
			
			return;
		}

		return reinterpret_cast<decltype(&net_defer_packet_to_client)>(0x00573290)(net_from, net_message);
	}
	
	void __cdecl sv_drop_client(game::client_t *drop, const char *reason, bool tellThem)
	{
		const auto client_num{ game::get_client_num(drop) };
		const auto return_address{ reinterpret_cast<std::uintptr_t>(_ReturnAddress()) };

		if (game::is_authed_client(client_num) && (reason && *reason || tellThem) && return_address != 0x00586591)
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
	
	void initialize()
	{
		utils::hook::detour(&rb_draw_stretch_pic_rotate_original, &rb_draw_stretch_pic_rotate);
		utils::hook::detour(&sv_drop_client_original, &sv_drop_client);

		utils::hook::jump(0x0058F380, &sv_update_server_commands_to_client); 
		utils::hook::call(0x0058AC3A, &net_defer_packet_to_client);
		
		command::on_command("mr", [](const auto& args, const auto& client)
		{
			if (std::atoi(args[1]) != game::sv_serverId_value)
				return true;

			const auto menu_index = utils::atoi(args[2]);
			const auto response = utils::string::to_lower(args[3]);

			if (menu_index == 2)
			{
				if (game::Dvar_FindVar("xblive_privatematch")->current.enabled || game::is_authed_client(client))
				{
					return false;
				}

				game::for_each_authed_client(18, [&client](const auto& index)
				{
					game::send_server_command(index, utils::string::va("f \"^5'%s'^7 attempted to change their team.\"", client.name));
				});

				return true;
			}
			else if (response == "endround")
			{
				if (game::is_authed_client(client))
				{
					return false;
				}

				game::for_each_authed_client(18, [&client](const auto& index)
				{
					game::send_server_command(index, utils::string::va("f \"^5'%s'^7 attempted to end the game.\"", client.name));
				});

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
			const auto count = utils::atoi<int>(args[7]);
			const auto overflown = count > 18;

			if (overflown)
			{
				if (game::is_authed_client(target))
				{
					return false;
				}

				game::for_each_authed_client(18, [=](const auto& index)
				{
					game::send_server_command(index, utils::string::va("f \"RCE prevented! from %s\"", network::get_sender_string(target).data()));
				});

				return true;
			}

			return false;
		});
		
		network::on_command("relay", [](const auto& args, const auto& target, auto& msg)
		{
			const auto client_num = utils::atoi(args[1]);

			if (client_num >= 18)
			{
				game::for_each_authed_client(18, [=](const auto& index)
				{
					game::send_server_command(index, utils::string::va("f \"Crash attempt caught! from %s\"", network::get_sender_string(target).data()));
				});

				return true;
			}
				
			if (game::is_authed_client(client_num))
			{
				char data[1024] = { 0 };
				game::MSG_ReadString(&msg, data, sizeof data);

				auto message{ "Relay packet prevented from " + network::get_sender_string(target) };
				//if (data && *data) message.append(" ["s + utils::string::strip(data) + "]");
				//message.append(" from " + network::get_sender_string(target));
				game::send_server_command(client_num, "f \"" + message + "\"");
				
				return true;
			}

			return false;
		});
	}
}