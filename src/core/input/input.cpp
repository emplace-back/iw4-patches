#include "dependencies/std_include.hpp"
#include "input.hpp"

namespace input
{
	WNDPROC wndproc;

	bool should_ignore_msg(UINT msg)
	{
		switch (msg)
		{
		case WM_CLOSE:
		case WM_QUIT:
		case WM_DESTROY:
			return true;
		default:
			return false;
		}
	}

	long __stdcall wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (should_ignore_msg(msg))
		{
			return true;
		}

		return CallWindowProcA(wndproc, hwnd, msg, wparam, lparam);
	}

	void initialize(HWND hwnd)
	{
		wndproc = WNDPROC(SetWindowLongPtr(hwnd, GWLP_WNDPROC, LONG_PTR(wnd_proc)));
	}
}