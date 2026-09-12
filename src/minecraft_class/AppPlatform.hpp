//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_APPPLATFORM_HPP
#define MINECRAFT_CLASS_APPPLATFORM_HPP

#include <string>

//向前声明
class AppPlatform_android;

class AppPlatform
{
private:
	static void change_game_home_path() noexcept;
	
public:
	static AppPlatform* get_instance_as_base() noexcept;
	static AppPlatform_android* get_instance_as_android_derived() noexcept;
	static bool use_centered_gui() noexcept;
	static std::string& home_path() noexcept;
	static void install() noexcept;
};

#endif
