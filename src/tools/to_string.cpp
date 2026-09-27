//Copyright (c) 2026 LPTEAM
#include "to_string.hpp"
#include <cstdio>
#include <string>

namespace tools
{
	std::string to_string(int value)
	{
		char buffer[32];
		int used_size =
			snprintf(buffer, sizeof(buffer), "%d", value);
		return std::string(buffer, used_size);
	}
}
