#include "dependencies/std_include.hpp"
#include "misc.hpp"

namespace misc
{
	auto client_user_info_changed_original = reinterpret_cast<decltype(&client_user_info_changed)>(0x0051F16F); 
	auto party_write_member_info_original = reinterpret_cast<decltype(&party_write_member_info)>(0x004D76D0);
	auto g_say_original = reinterpret_cast<decltype(&g_say)>(0x005261F3);

	void __cdecl callback_g_say(game::gentity_s* ent, char* message)
	{
		const auto filtered_name = utils::string::get_filtered_name(message);
		if (!game::is_authed_client(ent->s.number))
		{
			game::I_strncpyz(message, filtered_name, 150);
		}
	}

	__declspec(naked) void g_say()
	{
		__asm
		{
			pushad;
			push eax;
			push edi;
			call callback_g_say;
			add esp, 8;
			popad;

			jmp g_say_original;
		}
	}

	void __cdecl callback_party_write_member_info(game::PartyMember* member)
	{
		const auto client_num = game::get_client_num(member);
		const auto netadr = game::party_data()->session->dyn.users[client_num].addr;

		if (!game::is_real_address(member->xnaddr, netadr))
		{
			member->xnaddr.addr.inaddr = netadr.addr.inaddr;
			member->xnaddr.addr.port = htons(netadr.addr.port);
		}

		const auto filtered_name = utils::string::get_filtered_name(member->gamertag);
		game::I_strncpyz(member->gamertag, filtered_name.empty() ? "UnnamedPlayer" : filtered_name, 32);
	}

	__declspec(naked) void party_write_member_info()
	{
		__asm
		{
			pushad;
			push esi;
			call callback_party_write_member_info;
			pop esi;
			popad;

			jmp party_write_member_info_original;
		}
	}

	void __cdecl callback_client_user_info_changed(size_t client_num)
	{
		const auto client = &game::svs_clients[client_num];
		const auto name = game::Info_ValueForKey(client->userinfo, "name");

		if (!game::is_authed_client(client_num) && *name)
		{
			game::Info_SetValueForKey(client->userinfo, "name", utils::string::get_filtered_name(name).data());
		}
	}

	__declspec(naked) void client_user_info_changed()
	{
		__asm
		{
			pushad;
			push edi;
			call callback_client_user_info_changed;
			pop edi;
			popad;

			jmp client_user_info_changed_original;
		}
	}

	void* __cdecl menus_open_by_name(const void* dc, const char* menu)
	{
		const auto ignore_strings =
		{
			"leavelobbywarning"s,
			"popup_leavegame"s,
		};

		const auto result = std::any_of(ignore_strings.begin(), ignore_strings.end(), [=](const auto& str) { return str == menu; });

		if (!result)
		{
			return reinterpret_cast<decltype(&menus_open_by_name)>(0x005A3110)(dc, menu);
		}

		return nullptr;
	}
	
	void initialize()
	{
		utils::hook::detour(&g_say_original, &g_say); 
		utils::hook::detour(&party_write_member_info_original, &party_write_member_info);
		utils::hook::detour(&client_user_info_changed_original, &client_user_info_changed);

		utils::hook::call(0x005AE22F, &menus_open_by_name);
		
		scheduler::once(game::initialize, scheduler::pipeline::main);

		utils::hook::retn(0x0056A2D0); // Com_Quit_f
		utils::hook::retn(&ExitProcess);
		utils::hook::retn(&TerminateProcess);
	}
}