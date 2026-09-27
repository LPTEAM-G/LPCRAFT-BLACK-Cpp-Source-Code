//Copyright (c) 2026 LPTEAM
#pragma once

#include "mce/MaterialPtr.hpp"

class ScreenRenderer
{
public:
	ScreenRenderer() noexcept;

	static mce::MaterialPtr* get_screen_material(int index) noexcept;
};
