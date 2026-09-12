//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_APP_HPP
#define MINECRAFT_APP_HPP

#include <cstdint>

class minecraft_app
{
private:
	static void get_game_lib_handler() noexcept;
	static void get_game_lib_base() noexcept;

public:
	static void* game_lib_handler;
	static unsigned long game_lib_base;

	static void init() noexcept;
	static void* get_lib_thumb_function_ptr(uintptr_t offset) noexcept;
	static void* get_lib_vtable_address(uintptr_t offset) noexcept;

	template<typename T>
	static T* get_lib_global_variable_ptr(uintptr_t offset) noexcept
	{
		return (T*)(game_lib_base + offset);
	}
};

#endif
