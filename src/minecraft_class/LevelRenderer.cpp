#include "LevelRenderer.hpp"
#include "tools.hpp"
#include <cstdint>
#include <dlfcn.h>
#include <string>
#include "mce/Mesh.hpp"
#include "mce/RenderContext.hpp"
#include "mce/RenderContextImmediate.hpp"

unsigned long LevelRenderer::lib_base = 0;

LevelRenderer::renderCloudsFuncType LevelRenderer::renderCloudsOrig = nullptr;

int sub_430D24(void** a1, void** a2, int a3);

bool LevelRenderer::should_not_render_clouds(LevelRenderer* this_ptr) noexcept
{
	return *(bool*)((int)this_ptr + 5528);
}

void LevelRenderer::renderClouds(LevelRenderer *this_ptr, float p)
{
	if (not should_not_render_clouds(this_ptr))
	{
		
		//renderCloudsImpl(this_ptr, p);
		renderCloudsOrig(this_ptr, p);
	}
}


void LevelRenderer::renderCloudsImpl(LevelRenderer *this_ptr, float p) noexcept
{
	using func = void(*)(LevelRenderer*);
	func f = (func)(lib_base + 0x495350 + 1);
	f(this_ptr);
}

void LevelRenderer::install(void* handler, unsigned long base) noexcept
{
	lib_base = base;
	void* target = dlsym(handler, "_ZN13LevelRenderer12renderCloudsEf");
	MSHook(target, renderClouds, renderCloudsOrig);
}
