#pragma once
#include "dependencies/std_include.hpp"

namespace utils::string
{
	template <size_t Buffers, size_t MinBufferSize>
	class va_provider final
	{
	public:
		static_assert(Buffers != 0 && MinBufferSize != 0, "Buffers and MinBufferSize mustn't be 0");

		va_provider() : current_buffer_(0)
		{
		}

		char* get(const char* format, const va_list ap)
		{
			++this->current_buffer_ %= ARRAYSIZE(this->string_pool_);
			auto entry = &this->string_pool_[this->current_buffer_];

			if (!entry->size || !entry->buffer)
			{
				throw std::runtime_error("String pool not initialized");
			}

			while (true)
			{
				const auto res = vsnprintf_s(entry->buffer, entry->size, _TRUNCATE, format, ap);
				if (res > 0) break;
				if (res == 0) return nullptr;

				entry->double_size();
			}

			return entry->buffer;
		}

	private:
		class entry final
		{
		public:
			explicit entry(const size_t _size = MinBufferSize) : size(_size), buffer(nullptr)
			{
				if (this->size < MinBufferSize) this->size = MinBufferSize;
				this->allocate();
			}

			~entry()
			{
				if (this->buffer) memory::get_allocator()->free(this->buffer);
				this->size = 0;
				this->buffer = nullptr;
			}

			void allocate()
			{
				if (this->buffer) memory::get_allocator()->free(this->buffer);
				this->buffer = memory::get_allocator()->allocate_array<char>(this->size + 1);
			}

			void double_size()
			{
				this->size *= 2;
				this->allocate();
			}

			size_t size;
			char* buffer;
		};

		size_t current_buffer_;
		entry string_pool_[Buffers];
	};

	std::string get_filtered_name(const std::string & string, const bool strip = true);
	std::string join(const std::vector<std::string>& args, const std::size_t index = 1);
	std::string dump_hex(const std::string & data, const std::string & separator = "");
	std::string va(const char* fmt, ...);
	std::vector<std::string> split(const std::string & text, const char delimiter);
	std::string replace_all(std::string str, const std::string& search, const std::string& replace);
	bool begins_with(const std::string & text, const std::string & substring);
	bool contains(const std::string &sentence, const std::string &word);
	bool ends_with(const std::string & text, const std::string & substring);
	std::string to_lower(std::string text);
	std::string to_upper(std::string text);
	std::string reverse_words(std::string_view s);
	std::string strip(const std::string& string);
}