#include "dependencies/std_include.hpp"
#include "exception.hpp"

namespace exception
{
	LONG __stdcall exception_filter(const LPEXCEPTION_POINTERS ex)
	{
		const auto addr = ex->ExceptionRecord->ExceptionAddress;
		const auto code = ex->ExceptionRecord->ExceptionCode;

		if (code != STATUS_INTEGER_OVERFLOW
			&& code != STATUS_FLOAT_OVERFLOW
			&& code != STATUS_SINGLE_STEP)
		{
			auto error = "Termination due to a stack overflow."s;
			if (code != EXCEPTION_STACK_OVERFLOW)
			{
				error = utils::string::va("Exception: 0x%08X at 0x%08X", code, addr);
			}

			game::Com_Error(game::ERR_DROP, error.data());
		}

		return EXCEPTION_CONTINUE_SEARCH;
	}

	LPTOP_LEVEL_EXCEPTION_FILTER __stdcall set_unhandled_exception_filter(LPTOP_LEVEL_EXCEPTION_FILTER)
	{
		return &exception_filter;
	}
	
	void initialize()
	{
		SetUnhandledExceptionFilter(exception_filter);
		utils::hook::jump(&SetUnhandledExceptionFilter, &set_unhandled_exception_filter);
	}
}