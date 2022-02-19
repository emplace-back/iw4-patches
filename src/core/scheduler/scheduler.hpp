#pragma once
#include "dependencies/std_include.hpp"

namespace scheduler
{
	struct task
	{
		std::function<bool()> handler{};
		std::chrono::milliseconds interval{};
		std::chrono::high_resolution_clock::time_point last_call{};
	};
	
	enum pipeline
	{
		main,
		server,
		count,
	};

	using task_list = std::vector<task>; 
	static const bool cond_continue = false;
	static const bool cond_end = true;
	
	void __cdecl main_frame();
	void __cdecl server_frame();
	
	void schedule(const std::function<bool()>& callback, pipeline type = pipeline::main, std::chrono::milliseconds delay = 0ms);
	void loop(const std::function<void()>& callback, pipeline type = pipeline::main, std::chrono::milliseconds delay = 0ms);
	void once(const std::function<void()>& callback, pipeline type = pipeline::main, std::chrono::milliseconds delay = 0ms);
	void initialize();
}