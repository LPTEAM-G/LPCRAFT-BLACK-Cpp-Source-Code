#include "AbstractScreen.hpp"
#include <string>

std::string AbstractScreen::get_screen_name_virtual() const
{
	using func_type = void(*)(std::string*, const AbstractScreen*);
	void** vtable = *((void***)this);
	func_type func = (func_type)(vtable[48]);
	std::string sret;
	func(&sret, this);
	return sret;
}
