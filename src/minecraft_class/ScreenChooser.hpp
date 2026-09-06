//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SCREENCHOOSER_HPP
#define MINECRAFT_CLASS_SCREENCHOOSER_HPP

class ScreenChooser
{
public:
	using pushHudScreenType = int(*)(ScreenChooser*);
	static pushHudScreenType pushHudScreenOrig;

	//控制Hud的Json UI部分是否显示
	static int push_hud_screen(ScreenChooser* this_ptr);

	static void install() noexcept;
};

#endif
