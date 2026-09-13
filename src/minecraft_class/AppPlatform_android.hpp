//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_APPPLATFORM_ANDROID_HPP
#define MINECRAFT_CLASS_APPPLATFORM_ANDROID_HPP

#include <string>

class AppPlatform_android
{
public:
	static bool use_centered_gui(AppPlatform_android* this_ptr) noexcept;
	std::string& get_user_data_path() noexcept;
	
	static void install() noexcept;
};

#endif
