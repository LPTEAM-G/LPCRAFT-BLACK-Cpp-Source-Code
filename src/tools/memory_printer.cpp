//Copyright (c) 2026 LPTEAM
#include "memory_printer.hpp"
#include "log_lib.hpp"
#include <sstream>

namespace tools
{
	void memory_printer(const void* address, uintptr_t bytes) noexcept
	{
		std::ostringstream oss;
		uintptr_t addr = (uintptr_t)address;
		for (int byte = 0; byte < bytes; ++byte)
		{
			unsigned char* b = (unsigned char*)(addr + byte);
			int i = *b;
			oss << std::hex << i << " ";
		}
		LOGI("%s", oss.str().c_str());
	}
}
