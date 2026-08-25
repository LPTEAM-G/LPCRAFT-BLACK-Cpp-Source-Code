#ifndef MINECRAFT_CLASS_LEVELRENDERER_HPP
#define MINECRAFT_CLASS_LEVELRENDERER_HPP

class LevelRenderer
{
private:
	static unsigned long lib_base;
	
public:
	using renderCloudsFuncType = void(*)(LevelRenderer*, float);
	static renderCloudsFuncType renderCloudsOrig;

	static bool should_not_render_clouds(LevelRenderer* this_ptr) noexcept;
	static void renderClouds(LevelRenderer* this_ptr, float);
	static void renderCloudsImpl(LevelRenderer* this_ptr, float) noexcept;
	static void install(void* handler, unsigned long base) noexcept;
};

#endif
