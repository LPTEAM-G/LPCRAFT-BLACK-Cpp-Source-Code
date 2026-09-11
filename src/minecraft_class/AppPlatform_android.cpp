//Copyright (c) 2026 LPTEAM
#include "AppPlatform_android.hpp"
#include <cstdint>
#include <string>

std::string& AppPlatform_android::get_user_data_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 140);
}
