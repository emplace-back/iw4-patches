#include "dependencies/std_include.hpp"
#include "hook.hpp"

namespace utils::hook
{
	void detour(void** original, void* func)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(original, func);
		DetourTransactionCommit();
	}

	void redirect_jmp(void* address, void* target_func)
	{
		char* ptr = static_cast<char*>(address) + 2;
		int operand = reinterpret_cast<int>(target_func) - (reinterpret_cast<int>(address) + 6);
		set<int>(ptr, operand);
	}

	void nop(void* place, size_t length)
	{
		DWORD old_protection{ 0 };
		VirtualProtect(place, length, PAGE_EXECUTE_READWRITE, &old_protection);

		std::memset(place, static_cast<std::uint8_t>(instructions::nop), length);

		VirtualProtect(place, length, old_protection, &old_protection);
		FlushInstructionCache(GetCurrentProcess(), place, length);
	}

	void return_value(void* place, bool value)
	{
		return set(place, value ? instructions::mov_al_1_ret : instructions::xor_eax_eax_ret);
	}

	void jump(void* pointer, void* data)
	{
		auto* patch_pointer = PBYTE(pointer);
		set<std::uint8_t>(patch_pointer, std::uint8_t(instructions::jump));
		set<std::uint32_t>(patch_pointer + 1, std::uint32_t(size_t(data) - (size_t(pointer) + 5)));
	}

	void jump(const size_t pointer, void* data)
	{
		return jump(reinterpret_cast<void*>(pointer), data);
	}

	void jump(const size_t pointer, const size_t data)
	{
		return jump(pointer, reinterpret_cast<void*>(data));
	}

	void call(void* pointer, void* data)
	{
		auto* patch_pointer = PBYTE(pointer);
		set<std::uint8_t>(patch_pointer, std::uint8_t(instructions::call));
		set<std::uint32_t>(patch_pointer + 1, std::uint32_t(size_t(data) - (size_t(pointer) + 5)));
	}

	void call(const size_t pointer, void* data)
	{
		return call(reinterpret_cast<void*>(pointer), data);
	}

	void call(const size_t pointer, const size_t data)
	{
		return call(pointer, reinterpret_cast<void*>(data));
	}

	std::uintptr_t vtable(std::uintptr_t _interface, std::uintptr_t hook, std::uint32_t index)
	{
		auto v_table = reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(_interface));
		std::uint32_t backup = 0;

		MEMORY_BASIC_INFORMATION mbi;

		VirtualQuery(reinterpret_cast<void*>(v_table), &mbi, sizeof MEMORY_BASIC_INFORMATION);
		VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

		backup = v_table[index];
		v_table[index] = hook;

		VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

		return backup;
	}
}