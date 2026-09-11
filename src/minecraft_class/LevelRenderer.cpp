//Copyright (c) 2026 LPTEAM
#include "LevelRenderer.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Vec3.hpp"
#include <cstdint>

float LevelRenderer::increased_clouds_height = 5.0f;

LevelRenderer::render_level_type LevelRenderer::render_level_orig = nullptr;
LevelRenderer::renderCloudsType LevelRenderer::renderCloudsOrig = nullptr;
LevelRenderer::renderChunksType LevelRenderer::renderChunksOrig = nullptr;

LevelRenderer* LevelRenderer::render_level(LevelRenderer* this_ptr, Entity* entity, FrustumCuller* fc1, FrustumCuller* fc2, float f1, float f2)
{
	render_level_orig(this_ptr, entity, fc1, fc2, f1, f2);
	//可能启用的延后渲染
	renderClouds(this_ptr, f2);
	return this_ptr;
}

void LevelRenderer::renderClouds(LevelRenderer *this_ptr, float time)
{
	static bool should_enable_after_rendering = false;
	//提高云层渲染高度
	this_ptr->get_player_camera_pos().y -= increased_clouds_height;
	float camera_y = this_ptr->get_player_camera_pos().y;

	//此时云层开始修改深度范围
	//为不再使云遮挡其它半透明像素
	//这里研究了按条件的延后渲染模式
	if (camera_y >= 129.0f)
	{
		if (should_enable_after_rendering)
		{
			should_enable_after_rendering = false;
			renderCloudsOrig(this_ptr, time);
		}
		else
			should_enable_after_rendering = true;
	}
	else
	{
		should_enable_after_rendering = false;
		renderCloudsOrig(this_ptr, time);
	}
	
	this_ptr->get_player_camera_pos().y += increased_clouds_height;
}

void LevelRenderer::renderChunks(LevelRenderer* this_ptr, layer_index layer, float a3, bool flag)
{
	renderChunksOrig(this_ptr, layer, a3, flag);
}

Vec3& LevelRenderer::get_player_camera_pos() noexcept
{
	return *(Vec3*)(((uintptr_t)this + 7080));
}

void LevelRenderer::install() noexcept
{
	//_ZN13LevelRenderer11renderLevelER6EntityR13FrustumCullerS3_ff
	void* render_level_target = minecraft_app::get_lib_thumb_function_ptr(0x49BDB8);
	MSHook(render_level_target, render_level, render_level_orig);
	
	//_ZN13LevelRenderer12renderCloudsEf
	void* renderCloudsTarget = minecraft_app::get_lib_thumb_function_ptr(0x495838);
	MSHook(renderCloudsTarget, renderClouds, renderCloudsOrig);
	
	//_ZN13LevelRenderer12renderChunksE12TerrainLayerfb
	void* renderChunksTarget = minecraft_app::get_lib_thumb_function_ptr(0x445130);
	MSHook(renderChunksTarget, renderChunks, renderChunksOrig);
}
