#ifndef MINECRAFT_CLASS_APPPLATFORM_HPP
#define MINECRAFT_CLASS_APPPLATFORM_HPP

#include <string>

class AppPlatform
{
public:
	static std::string& HOME_PATH(unsigned long base) noexcept;
};

#endif
