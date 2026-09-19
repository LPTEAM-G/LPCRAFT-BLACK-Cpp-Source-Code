//Copyright (c) 2026 LPTEAM
#pragma once

class ScreenChooser
{
public:
	using pushHudScreenType = int(*)(ScreenChooser*);
	static pushHudScreenType pushHudScreenOrig;

	//控制Hud的Json UI部分是否被推入
	static int push_hud_screen(ScreenChooser* this_ptr);

	static void install() noexcept;
};

