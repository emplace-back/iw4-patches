#pragma once
#include "dependencies/std_include.hpp"

namespace utils::hook
{
	enum class instructions
	{ 
		call = 0xE8, 
		jump = 0xE9,
		retn = 0xC3,
		mov_al_1_ret = 0xC301B0,
		xor_eax_eax_ret = 0xC3C033,
		nop = 0x90,
	};

	void return_value(void * place, bool value);
	
	void jump(void* pointer, void* data);
	void jump(size_t pointer, void* data);
	void jump(size_t pointer, size_t data);
	
	void call(void* pointer, void* data);
	void call(size_t pointer, void* data);
	void call(size_t pointer, size_t data);
	
	std::uintptr_t vtable(std::uintptr_t _interface, std::uintptr_t hook, std::uint32_t index);
	void detour(void** original, void* func);
	void nop(void* place, size_t length = 5);
	void redirect_jmp(void* address, void* target_func);

	inline void write_string(char* place, const std::string& string)
	{
		DWORD old_protect;
		VirtualProtect(place, sizeof(place), PAGE_EXECUTE_READWRITE, &old_protect);
		
		std::strncpy(place, string.data(), string.size());
		place[string.size()] = 0;

		VirtualProtect(place, sizeof(place), old_protect, &old_protect);
		FlushInstructionCache(GetCurrentProcess(), place, sizeof(place));
	}
	
	inline void return_value(const std::size_t place, bool value)
	{
		return_value(reinterpret_cast<void*>(place), value);
	}

	inline void detour(void* original, void* func)
	{
		detour(reinterpret_cast<void**>(original), func);
	}

	inline std::uintptr_t vtable(void* _interface, void* hook, std::uint32_t index)
	{
		return vtable(reinterpret_cast<std::uintptr_t>(_interface), reinterpret_cast<std::uint32_t>(hook), index);
	}

	inline void nop(const std::size_t place, size_t length = 5)
	{
		nop(reinterpret_cast<void*>(place), length);
	}

	template <typename T>
	static void set(void* place, T value)
	{
		DWORD old_protect;
		VirtualProtect(place, sizeof(T), PAGE_EXECUTE_READWRITE, &old_protect);

		*static_cast<T*>(place) = value;

		VirtualProtect(place, sizeof(T), old_protect, &old_protect);
		FlushInstructionCache(GetCurrentProcess(), place, sizeof(T));
	}

	template <typename T>
	static void set(const size_t place, T value)
	{
		return set<T>(reinterpret_cast<void*>(place), value);
	}

	static void retn(const std::size_t place)
	{
		return set<std::uint8_t>(reinterpret_cast<void*>(place), static_cast<std::uint8_t>(instructions::retn));
	}

	static void retn(const void* place)
	{
		return retn(reinterpret_cast<size_t>(place));
	}
}