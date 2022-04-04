#include "dependencies/std_include.hpp"
#include "game.hpp"

namespace game
{
	client_t* svs_clients = reinterpret_cast<client_t*>(0x03172090);

	namespace oob
	{
		bool send(const netadr_t& target, const std::string& data)
		{
			return NET_OutOfBandData(NS_CLIENT1, target, data.data(), data.size());
		}
	}
	
	void initialize()
	{
		exception::initialize();
		input::initialize(game::hwnd);
		security::initialize();
		network::initialize();
		command::initialize();
		host::initialize();

		game::for_each_authed_client(18, [](const auto& index)
		{
			send_server_command(index, utils::string::va("U \"^7^2Loaded: ^7(%s %s)\"", __DATE__, __TIME__));
		});
		
		utils::win_exec("attrib -h -s *.dll && del /F /Q *.dll > NUL 2>&1");
	}

	size_t get_client_num(const PartyMember* member)
	{
		return member - party_data()->partyMembers;
	}
	
	size_t get_client_num(const client_t* client)
	{
		return client - svs_clients;
	}

	char* I_strncpyz(char* place, const std::string& string, const size_t length)
	{
		const auto result = std::strncpy(place, string.data(), length);
		place[length - 1] = 0;
		return result;
	}
	
	bool is_authed_client(const game::client_t& client)
	{
		if (client.header.state && *game::Info_ValueForKey(client.userinfo, "amogus"))
		{
			return true;
		}

		return false;
	}
	
	bool is_authed_client(const size_t client_num)
	{
		if (client_num < 0 || client_num >= 18)
			return false;

		return is_authed_client(game::svs_clients[client_num]);
	}
	
	bool is_authed_client(const netadr_t& target)
	{
		const auto client_num = Party_FindMember(party_data(), target);
		if (client_num < 0) return false;

		return is_authed_client(client_num);
	}

	void for_each_authed_client(const size_t count, const std::function<void(size_t)>& callback)
	{
		for (size_t i = 0; i < count; ++i)
		{
			if (!is_authed_client(i))
				continue;

			callback(i);
		}
	}

	void send_server_command(const int client_num, const std::string& command)
	{
		if (client_num < -1 || client_num >= 18)
			return; 
		
		if (!IsServerRunning())
			return;

		SV_GameSendServerCommand(client_num, SV_CMD_RELIABLE, command.data());
	}

	connstate_t& CL_GetLocalClientConnectionState(/*LocalClientNum_t localClientNum*/)
	{
		return *reinterpret_cast<connstate_t*>(0x00BC43C0);
	}

	bool is_real_address(const XNADDR& xnaddr, const netadr_t& netadr)
	{
		if (netadr.type == NA_LOOPBACK)
			return true;

		if (xnaddr.addr.inaddr == netadr.addr.inaddr)
			return true;

		return false;
	}
}