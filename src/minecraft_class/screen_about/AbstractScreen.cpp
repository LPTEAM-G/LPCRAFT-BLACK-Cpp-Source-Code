//Copyright (c) 2026 LPTEAM
#include "AbstractScreen.hpp"
#include <string>

std::string AbstractScreen::get_screen_name_virtual() const noexcept
{
	using get_screen_name_virtual_type = void(*)(std::string*, const AbstractScreen*);
	void** vtable = *((void***)this);
	get_screen_name_virtual_type get_screen_name_virtual_orig = (get_screen_name_virtual_type)(vtable[48]);
	std::string sret;
	get_screen_name_virtual_orig(&sret, this);
	return sret;
}
