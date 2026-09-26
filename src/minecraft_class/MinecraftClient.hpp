//Copyright (c) 2026 LPTEAM
#pragma once

#include <memory>
#include <string>
#include <vector>
#include "mce/TextureGroup.hpp"
#include "minecraft_class/Font.hpp"
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

	using vector_screen = std::vector<std::shared_ptr<AbstractScreen>>;

	std::string& get_mcpe_dirname() noexcept;
	std::string& get_worlds_dirname() noexcept;
	std::string& get_final_worlds_dir_path() noexcept;
	int get_screen_width() noexcept;
	Font* get_font() noexcept;
	vector_screen& get_screen_stack() noexcept;
	mce::TextureGroup* get_texture_group() noexcept;
	
	Minecraft* get_server() noexcept;

	static void install() noexcept;
};
