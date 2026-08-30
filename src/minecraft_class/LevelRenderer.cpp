//Copyright (c) 2026 LPTEAM
#include "LevelRenderer.hpp"
#include "hook_macro.hpp"
#include "init.hpp"
#include <dlfcn.h>

LevelRenderer::renderCloudsType LevelRenderer::renderCloudsOrig = nullptr;
LevelRenderer::renderChunksType LevelRenderer::renderChunksOrig = nullptr;

void LevelRenderer::renderClouds(LevelRenderer *this_ptr, float time)
{
	renderCloudsOrig(this_ptr, time);
}

void LevelRenderer::renderChunks(LevelRenderer* this_ptr, layer_index layer, float a3, bool flag)
{
	renderChunksOrig(this_ptr, layer, a3, flag);
}

void LevelRenderer::install() noexcept
{
	void* renderCloudsTarget = dlsym(minecraft_app::game_lib_handler, "_ZN13LevelRenderer12renderCloudsEf");
	MSHook(renderCloudsTarget, renderClouds, renderCloudsOrig);
	void* renderChunksTarget = dlsym(minecraft_app::game_lib_handler, "_ZN13LevelRenderer12renderChunksE12TerrainLayerfb");
	MSHook(renderChunksTarget, renderChunks, renderChunksOrig);
}
