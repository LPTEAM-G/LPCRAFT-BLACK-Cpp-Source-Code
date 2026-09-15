//Copyright (c) 2026 LPTEAM
#ifndef TOOLS_MAKING_CRASH_HPP
#define TOOLS_MAKING_CRASH_HPP

namespace tools
{
	inline void making_crash() noexcept
	{
		using crash_func_type = void(*)();
		crash_func_type crash_func = nullptr;
		crash_func();
	}
}

#endif
