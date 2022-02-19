#include "dependencies/std_include.hpp"
#include "network.hpp"

namespace network
{
	auto cl_dispatch_connectionless_packet_original = reinterpret_cast<decltype(&cl_dispatch_connectionless_packet)>(0x004C6B52);

	namespace
	{
		std::unordered_map<std::string, callback>& get_callbacks()
		{
			static std::unordered_map<std::string, callback> callbacks{};
			return callbacks;
		}

		std::string get_oob_string(const command::args& args)
		{
			const auto oob_string = utils::string::to_lower(args[0]);
			if (oob_string.length() > 1 && (oob_string[0] == '0' || oob_string[0] == '1' || oob_string[0] == '2'))
			{
				return oob_string.substr(1);
			}

			return oob_string;
		}

		bool handle_command(const command::args& args, const game::netadr_t& from, game::msg_t& msg)
		{
			const auto oob_string = get_oob_string(args);
			const auto& callbacks = get_callbacks();
			const auto handler = callbacks.find(oob_string);

			if (handler == callbacks.end())
			{
				return false;
			}

			const auto msg_backup = msg;
			const auto callback = handler->second(args, from, msg);

			if (msg.readcount != msg_backup.readcount)
				msg = msg_backup;

			return callback;
		}

		bool __cdecl callback_cl_dispatch_connectionless_packet(game::netadr_t* from, game::msg_t* msg)
		{
			if (const command::args args{}; args.size() > 0)
			{
				return handle_command(args, *from, *msg);
			}

			return false;
		}
	}

	std::string get_sender_string(const game::netadr_t& from)
	{
		const auto party = game::party_data();
		const auto client_num = game::Party_FindMember(party, from);

		if (client_num < 0)
		{
			return utils::string::va("%s", from.to_string().data());
		}

		const auto member = party->partyMembers[client_num];
		return utils::string::va("'%s' (%llu) %s", member.gamertag, member.player, from.to_string().data());
	}

	void on_command(const std::string& command, const callback& callback)
	{
		get_callbacks()[utils::string::to_lower(command)] = callback;
	}

	__declspec(naked) void cl_dispatch_connectionless_packet()
	{
		static game::netadr_t* from;
		static game::msg_t* msg;

		__asm
		{
			lea eax, [esp + 0xC54];
			mov from, eax;
			mov msg, ebp;

			pushad;
			push msg;
			push from;
			call callback_cl_dispatch_connectionless_packet;
			add esp, 8;
			test al, al;
			popad;

			jz fix;

			push 0x004C7715;
			retn;
		fix:
			jmp cl_dispatch_connectionless_packet_original;
		}
	}

	void initialize()
	{
		utils::hook::detour(&cl_dispatch_connectionless_packet_original, &cl_dispatch_connectionless_packet);
	}
}