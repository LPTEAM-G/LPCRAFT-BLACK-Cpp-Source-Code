//Copyright (c) 2026 LPTEAM
#pragma once

namespace tools
{
	inline void making_crash() noexcept
	{
		using crash_func_type = void(*)();
		crash_func_type crash_func = nullptr;
		crash_func();
	}
}
