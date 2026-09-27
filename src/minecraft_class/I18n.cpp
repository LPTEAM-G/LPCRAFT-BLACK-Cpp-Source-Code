//Copyright (c) 2026 LPTEAM
#include "I18n.hpp"
#include "minecraft_app.hpp"
#include <string>
#include <vector>

std::string I18n::get(const std::string& key, const std::vector<std::string>& args)
{
	using get_type = void(*)(std::string*, const std::string*, const std::vector<std::string>*);
	get_type get_orig = (get_type)minecraft_app::get_lib_thumb_function_ptr(0x47D9EC);
	std::string sret;
	get_orig(&sret, &key, &args);
	return sret;
}
