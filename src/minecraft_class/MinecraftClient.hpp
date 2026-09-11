//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_MINECRAFTCLIENT_HPP
#define MINECRAFT_CLASS_MINECRAFTCLIENT_HPP

#include <string>
class MinecraftClient
{
public:
	static MinecraftClient* instance;

	using constructor_type = void(*)(MinecraftClient*, int, char**);
	static constructor_type constructor_orig;
	using tickInputType = int(*)(MinecraftClient*);
	static tickInputType tickInputOrig;

	static void constructor(MinecraftClient* this_ptr, int, char**);
	static int tick_input(MinecraftClient* this_ptr);

	std::string& get_mcpe_dirname() noexcept;
	std::string& get_worlds_dirname() noexcept;
	std::string& get_final_worlds_dir_path() noexcept;
	int get_screen_width() noexcept;

	static void install() noexcept;
};

#endif
