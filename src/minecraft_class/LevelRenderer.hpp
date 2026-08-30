//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_LEVELRENDERER_HPP
#define MINECRAFT_CLASS_LEVELRENDERER_HPP

class LevelRenderer
{
private:

	enum layer_index
	{
		slime_blocks = 6,
		water = 7,
	};
	
public:
	using renderCloudsType = void(*)(LevelRenderer*, float);
	using renderChunksType = void(*)(LevelRenderer*, layer_index, float, bool);

	static renderCloudsType renderCloudsOrig;
	static renderChunksType renderChunksOrig;

	static void renderClouds(LevelRenderer* this_ptr, float);
	static void renderChunks(LevelRenderer* this_ptr, layer_index layer, float a3, bool flag);
	static void install() noexcept;
};

#endif
