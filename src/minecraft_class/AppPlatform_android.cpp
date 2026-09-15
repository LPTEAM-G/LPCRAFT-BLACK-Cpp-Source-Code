//Copyright (c) 2026 LPTEAM
#include "AppPlatform_android.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include "tools/vtable_setter.hpp"
#include <cstdint>
#include <string>

std::string& AppPlatform_android::get_user_data_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 140);
}

bool AppPlatform_android::use_centered_gui(AppPlatform_android* this_ptr) noexcept
{
	return Options::opt_vars::use_centered_gui;
}

void AppPlatform_android::install() noexcept
{
	auto* global_instance = AppPlatform::get_instance_as_android_derived();
	tools::vtable_setter setter
	{
		*(void**)global_instance,
		86
	};
	setter[59] = (void*)&use_centered_gui;
}
