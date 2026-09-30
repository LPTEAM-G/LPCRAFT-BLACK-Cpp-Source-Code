//Copyright (c) 2026 LPTEAM
#pragma once

#include "glm/type_vec3.hpp"
#include "minecraft_class/Entity.hpp"
#include "minecraft_class/FrustumCuller.hpp"

class LevelRenderer
{
private:

	enum layer_index
	{
		slime_blocks = 6,
		water = 7,
	};
	
public:
	static float increased_clouds_height;

	using render_level_type =
		LevelRenderer*(*)(
		LevelRenderer*,
		Entity*,
		FrustumCuller*,
		FrustumCuller*,
		float,
		float
	);
	using renderCloudsType = void(*)(LevelRenderer*, float);
	using renderChunksType = void(*)(LevelRenderer*, layer_index, float, bool);

	static render_level_type render_level_orig;
	static renderCloudsType renderCloudsOrig;

	static LevelRenderer* render_level(
		LevelRenderer* this_ptr,
		Entity* entity,
		FrustumCuller* fc1,
		FrustumCuller* fc2,
		float f1,
		float f2
	);
	static void renderClouds(LevelRenderer* this_ptr, float);

	glm::vec3& get_player_camera_pos() noexcept;

	static void install() noexcept;
};
