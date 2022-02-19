#pragma once

namespace command
{
	class args final
	{
	public:
		const char* get(const size_t index) const noexcept;
		size_t size() const noexcept;
		std::string join(const size_t index = 0) const noexcept;

		const char* operator[](const int index) const
		{
			return this->get(index);
		}
	};

	class args_sv final
	{
	public:
		const char* get(const size_t index) const noexcept;
		size_t size() const noexcept;
		std::string join(const size_t index = 0) const noexcept;

		const char* operator[](const size_t index) const
		{
			return this->get(index);
		}

	};

	using callback = std::function<bool(const args_sv&, const game::client_t&)>;
	void on_command(const std::string& command, const callback& callback);
	void initialize();
}
