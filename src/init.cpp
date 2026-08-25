#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/BlockTessellator.hpp"
#include "minecraft_class/LevelRenderer.hpp"
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "minecraft_class/blocks/LiquidBlock.hpp"
#include "xHook/xhook.h"
#include <cstdio>
#include <dlfcn.h>
#include <jni.h>
#include <android/log.h>
#include <cstring>
#include <string>
#include <unistd.h>

#define LOG_TAG "LPTEAM"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//保存游戏库的句柄
void* game_lib_handler = nullptr;
//保存游戏库的基址
unsigned long game_lib_base = 0;

void* get_game_lib_handler() noexcept;
unsigned long get_game_lib_base() noexcept;

//修改游戏的path
void change_game_path(unsigned base) noexcept;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
	game_lib_handler = get_game_lib_handler();
	game_lib_base = get_game_lib_base();

	change_game_path(game_lib_base);
	
	BlockTessellator::install(game_lib_handler, game_lib_base);
	GrassBlock::install(game_lib_handler);
	LiquidBlock::install(game_lib_handler);
	LevelRenderer::install(game_lib_handler, game_lib_base);

	//安装完所有Hook后启动XHook
	xhook_refresh(0);
	
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

void change_game_path(unsigned base) noexcept
{
	std::string& path = AppPlatform::HOME_PATH(base);
	path = "/minecraft-clients/lpcraft-black/";
}
