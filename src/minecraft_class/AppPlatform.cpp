#include "AppPlatform.hpp"
#include <string>

std::string& AppPlatform::get_home_path(unsigned long base) noexcept
{
	return *(std::string*)(base + 0x0075f23c);
}
