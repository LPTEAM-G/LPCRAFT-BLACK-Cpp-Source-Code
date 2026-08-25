#include "AppPlatform.hpp"
#include <string>

std::string& AppPlatform::HOME_PATH(unsigned long base) noexcept
{
	return *(std::string*)(base + 0x0075f23c);
}
