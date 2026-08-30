//Copyright (c) 2026 LPTEAM
#include "init.hpp"
#include "glsl.hpp"
#include "log_lib.hpp"
#include "minecraft_class/AmbientOcclusionCalculator.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/BlockTessellator.hpp"
#include "minecraft_class/LevelRenderer.hpp"
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "minecraft_class/blocks/LiquidBlock.hpp"
#include <cstdio>
#include <dlfcn.h>
#include <jni.h>
#include <cstring>
#include <string>
#include <unistd.h>

//保存游戏库的句柄
void* minecraft_app::game_lib_handler = nullptr;
//保存游戏库的基址
unsigned long minecraft_app::game_lib_base = 0;

void* get_game_lib_handler() noexcept;
unsigned long get_game_lib_base() noexcept;

//修改游戏的path
void change_game_path() noexcept;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
	LOGI("Shared Library liblpteam.so Loaded");
	minecraft_app::game_lib_handler = get_game_lib_handler();
	minecraft_app::game_lib_base = get_game_lib_base();

	change_game_path();
	
	glsl::install();
	BlockSource::install();
	AmbientOcclusionCalculator::install();
	BlockTessellator::install();
	GrassBlock::install();
	LiquidBlock::install();
	LevelRenderer::install();
	
	return JNI_VERSION_1_6;
}

void* get_game_lib_handler() noexcept
{
	void* handler = dlopen("libminecraftpe.so", RTLD_NOW);
	return handler;
}

unsigned long get_game_lib_base() noexcept
{
	unsigned long base = 0;
	FILE *fp = fopen("/proc/self/maps", "r");
	char line[256];
	while (fgets(line, sizeof(line), fp)) {
		if (strstr(line, "libminecraftpe.so")) {
			sscanf(line, "%lx", &base);
			break;
		}
	}
	fclose(fp);
	return base;
}

void change_game_path() noexcept
{
	std::string& path = AppPlatform::get_home_path();
	path = "/minecraft-clients/lpcraft-black/";
}
