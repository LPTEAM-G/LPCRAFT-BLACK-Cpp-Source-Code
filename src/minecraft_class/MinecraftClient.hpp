//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_MINECRAFTCLIENT_HPP
#define MINECRAFT_CLASS_MINECRAFTCLIENT_HPP

class MinecraftClient
{
public:
	static MinecraftClient* instance;
	
	using tickInputType = int(*)(MinecraftClient*);
	static tickInputType tickInputOrig;

	static int tick_input(MinecraftClient* this_ptr);

	int get_width() noexcept;

	static void install() noexcept;
};

#endif
