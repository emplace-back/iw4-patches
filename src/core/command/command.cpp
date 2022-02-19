#include "dependencies/std_include.hpp"
#include "command.hpp"

namespace command
{
	namespace
	{
		std::unordered_map<std::string, callback>& get_callbacks()
		{
			static std::unordered_map<std::string, callback> callbacks{};
			return callbacks;
		}

		bool handle_command(const game::client_t& client)
		{
			const command::args_sv args{};
			
			if (args.size() <= 0) 
				return false;
			
			const auto command = utils::string::to_lower(args[0]);
			const auto& callbacks = get_callbacks();
			const auto handler = callbacks.find(command);

			if (handler == callbacks.end())
			{
				return false;
			}

			return handler->second(args, client);
		}

		void __cdecl client_command(ClientNum_t clientNum)
		{
			const auto& client = game::svs_client->clients[clientNum];
			if (!handle_command(client))
			{
				return reinterpret_cast<decltype(&client_command)>(0x00526280)(clientNum);
			}
		}
	}
	
	const char* args::get(const size_t index) const noexcept
	{
		return game::Cmd_Argv(index);
	}

	size_t args::size() const noexcept
	{
		return game::cmd_argc[*game::cmd_id];
	}

	std::string args::join(const size_t index) const noexcept
	{
		auto result = ""s;

		for (auto i = index; i != this->size(); ++i)
		{
			if (i > index)
			{
				result.append(" ");
			}

			result.append(this->get(i));
		}

		return result;
	}

	const char* args_sv::get(const size_t index) const noexcept
	{
		return game::SV_Cmd_Argv(index);
	}

	size_t args_sv::size() const noexcept
	{
		return game::sv_cmd_argc[*game::sv_cmd_id];
	}

	std::string args_sv::join(const size_t index) const noexcept
	{
		auto result = ""s;

		for (auto i = index; i != this->size(); ++i)
		{
			if (i > index)
			{
				result.append(" ");
			}

			result.append(this->get(i));
		}

		return result;
	}

	void on_command(const std::string& command, const callback& callback)
	{
		get_callbacks()[utils::string::to_lower(command)] = callback;
	}

	void initialize()
	{
		utils::hook::call(0x00586C2A, &client_command);

		command::on_command("buildstatus", [](const auto&, const auto& client)
		{
			game::send_server_command(game::get_client_num(&client) , utils::string::va("f \"^2Loaded: ^7(%s %s)\"", __DATE__, __TIME__));
			return true;
		});
	}
}