#include "dependencies/std_include.hpp"
#include "string.hpp"

namespace utils::string
{
	std::string get_filtered_name(const std::string& string, const bool strip)
	{
		const std::pair<std::string, std::string> chat_filters[] =
		{
			{"(?:[1il]nurf[4a]c[3e])|(?:s[il1]d[4a]z)|(?:v[0o]rtex)|(?:r[0o]si[3e])", "retard"},
			{"k *k *k\\b", "BLM"},
			{"hurensohn", "I'm a dumb german."},
			{"f[a4@e]g(?:g[0oi1]t)?\\b", "heterosexual"},
			{"tr[4a]nny", "heterosexual"},
			{"gay|homo", "heterosexual"},
			{"ugly", "cute"},
			{"(?:k *y *s)|(?:kill|hang|off|shoot|suicide)\\s+your*\\s*self", "Have a great day."},
			{"(?:n[|',.\\-_ ]*)(?:[i1l!][|',.\\-_ ]*)+(?:g[|',.\\-_ ]*){2,}(?:[3e][|',.\\-_ ]*)+r+", "niceguy"},
			{"n[il1]g+[^h]*\\b", "niceguy"},
			{"n16{2,}3r", "niceguy"},
			{"t[0o]by", "niceguy"},
			{"kn[e3]{2,}g+[3e]+[a4]*r", "niceguy"},
			{"fuck you", "I love you."},
			{"n[1li]gg[e3]rb[0o]t", "skidbot"},
			{"\\w+ (?:dad\\s*|mommy\\s*|father\\s*|m[0uo]m\\s*|nan\\s*|mother\\s*)+", "I have family problems."},
			{"[cs]heat|h[a4]ck|h[a4]x", "legit"},
			{"lifeless|(?:get a life)", "I have no life."},
			{"alt[ \\+]escape", "Stay in the game."},
			{"ctrl[ \\+]+alt[ \\+]del", "Stay in the game."},
			{"shift[ \\+]tab", "Stay in the game."},
			{"hate", "love"},
			{"report", "reward"},
		};

		std::string result{ strip ? utils::string::strip(string) : string };

		for (const auto&[regex, replace] : chat_filters)
		{
			result = std::regex_replace(result, std::regex{ regex, std::regex_constants::icase }, replace);
		}

		return result;
	}
	
	std::string join(const std::vector<std::string>& args, const std::size_t index)
	{
		auto result = ""s;

		for (auto i = index; i < args.size(); ++i)
		{
			if (i > index)
			{
				result.append(" ");
			}

			result.append(args[i]);
		}

		return result;
	}

	std::string dump_hex(const std::string& data, const std::string& separator)
	{
		auto result = ""s;

		for (size_t i = 0; i < data.size(); ++i)
		{
			if (i > 0)
			{
				result.append(separator);
			}

			result.append(va("%02X", data[i] & 0xFF));
		}

		return result;
	}
	
	std::string va(const char* fmt, ...)
	{
		static thread_local va_provider<8, 256> provider;

		va_list ap;
		va_start(ap, fmt);

		const auto* result = provider.get(fmt, ap);

		va_end(ap);
		return result;
	}

	std::vector<std::string> split(const std::string& text, const char delimiter)
	{
		std::stringstream ss(text);
		std::string item;
		std::vector<std::string> elems;

		while (std::getline(ss, item, delimiter))
		{
			elems.emplace_back(item);
		}

		return elems;
	}

	std::string replace_all(std::string str, const std::string& from, const std::string& to)
	{
		if (from.empty())
		{
			return str;
		}
		
		std::string::size_type start_pos = 0;

		while ((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}

		return str;
	}

	bool begins_with(const std::string& text, const std::string& substring)
	{
		return text.find(substring) == 0;
	}

	bool contains(const std::string &text, const std::string &substring)
	{
		return text.find(substring) != std::string::npos;
	}

	bool ends_with(const std::string& text, const std::string& substring)
	{
		if (substring.size() > text.size()) return false;
		return std::equal(substring.rbegin(), substring.rend(), text.rbegin());
	}

	std::string to_lower(std::string text)
	{
		std::transform(text.begin(), text.end(), text.begin(), [](const auto& input) { return static_cast<char>(std::tolower(input)); });
		return text;
	}

	std::string to_upper(std::string text)
	{
		std::transform(text.begin(), text.end(), text.begin(), [](const auto& input) { return static_cast<char>(std::toupper(input)); });
		return text;
	}

	std::string reverse_words(std::string_view s)
	{
		std::string result;
		result.reserve(s.size());

		while (!s.empty())
		{
			const auto i = s.rfind(' ');
			result.append(s.begin() + i + 1, s.end());

			if (i == std::string_view::npos) break;

			s = s.substr(0, i);
		}

		return result;
	}

	std::string strip(const std::string& string)
	{
		const auto result = game::I_CleanStr(string.data());
		return result;
	}
}