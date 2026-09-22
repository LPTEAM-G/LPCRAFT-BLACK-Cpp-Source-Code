//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>

class AppPlatform_android
{
public:
	static AppPlatform_android* get_instance() noexcept;
	static bool use_centered_gui(AppPlatform_android* this_ptr) noexcept;
	std::string& get_user_data_path() noexcept;
	
	static void install() noexcept;
};
