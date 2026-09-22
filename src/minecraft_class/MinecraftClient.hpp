//Copyright (c) 2026 LPTEAM
#pragma once

#include <memory>
#include <string>
#include <vector>
#include "minecraft_class/screen_about/AbstractScreen.hpp"
#include "minecraft_class/Minecraft.hpp"

class MinecraftClient
{
private:
	struct pushed_screen_list_type
	{
		bool hud_screen = false;
	};
	
public:
	static MinecraftClient* instance;
	static pushed_screen_list_type pushed_screen_list;

	using constructor_type = void(*)(MinecraftClient*, int, char**);
	static constructor_type constructor_orig;

	using tickInputType = int(*)(MinecraftClient*);
	static tickInputType tickInputOrig;

	using push_screen_type = void(*)(MinecraftClient*, std::shared_ptr<AbstractScreen>, bool);
	static push_screen_type push_screen_orig;
	static void push_screen_impl(
		MinecraftClient* this_ptr,
		std::shared_ptr<AbstractScreen> screen,
		bool immediate
	);

	using _pop_screen_type = void(*)(MinecraftClient*);
	static _pop_screen_type _pop_screen_orig;
	static void _pop_screen_impl(MinecraftClient* this_ptr);
	
	static void constructor(MinecraftClient* this_ptr, int, char**);
	static int tick_input_impl(MinecraftClient* this_ptr);

	using vector_screen = std::vector<std::shared_ptr<AbstractScreen>>;

	std::string& get_mcpe_dirname() noexcept;
	std::string& get_worlds_dirname() noexcept;
	std::string& get_final_worlds_dir_path() noexcept;
	int get_screen_width() noexcept;
	vector_screen& get_screen_stack() noexcept;
	
	Minecraft* get_server() noexcept;

	static void install() noexcept;
};
