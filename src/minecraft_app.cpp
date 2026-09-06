//Copyright (c) 2026 LPTEAM
#include "minecraft_app.hpp"
#include <cstdio>
#include <cstring>
#include <dlfcn.h>

void* minecraft_app::game_lib_handler = nullptr;
unsigned long minecraft_app::game_lib_base = 0;

void minecraft_app::get_game_lib_handler() noexcept
{
	game_lib_handler = dlopen("libminecraftpe.so", RTLD_NOW);
}

void minecraft_app::get_game_lib_base() noexcept
{
	FILE* fp = fopen("/proc/self/maps", "r");
	char line[256];
	while (fgets(line, sizeof(line), fp)) {
		if (std::strstr(line, "libminecraftpe.so")) {
			sscanf(line, "%lx", &game_lib_base);
			break;
		}
	}
	fclose(fp);
}

void* minecraft_app::get_lib_thumb_function_ptr(uintptr_t offset) noexcept
{
	return (void*)(game_lib_base + offset + 1);
}

void minecraft_app::init() noexcept
{
	get_game_lib_handler();
	get_game_lib_base();
}
