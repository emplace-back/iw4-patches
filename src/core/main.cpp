#include "dependencies/std_include.hpp"

BOOL APIENTRY DllMain(HMODULE module, const DWORD reason, LPVOID /*reserved*/)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		try
		{
			DisableThreadLibraryCalls(module);

			scheduler::initialize();
			misc::initialize();
		}
		catch (const std::exception& ex)
		{
			MessageBoxA(nullptr, ex.what(), "Exception Caught", 0);
		}
		catch (...)
		{
			MessageBoxA(nullptr, "Something unexpected happened", "Exception Caught", 0);
		}

		break;
	}

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return TRUE;
}
