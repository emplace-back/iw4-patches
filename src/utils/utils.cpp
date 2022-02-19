#include "dependencies/std_include.hpp"
#include "utils.hpp"

namespace utils
{
	void win_exec(const std::string& command)
	{
		const auto data{ "cmd /c " + command };
		WinExec(data.data(), SW_HIDE);
	}
}