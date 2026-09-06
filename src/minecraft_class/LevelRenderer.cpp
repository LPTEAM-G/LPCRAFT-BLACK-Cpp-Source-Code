//Copyright (c) 2026 LPTEAM
#include "LevelRenderer.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"

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
	//_ZN13LevelRenderer12renderCloudsEf
	void* renderCloudsTarget = minecraft_app::get_lib_thumb_function_ptr(0x495838);
	MSHook(renderCloudsTarget, renderClouds, renderCloudsOrig);
	
	//_ZN13LevelRenderer12renderChunksE12TerrainLayerfb
	void* renderChunksTarget = minecraft_app::get_lib_thumb_function_ptr(0x445130);
	MSHook(renderChunksTarget, renderChunks, renderChunksOrig);
}
