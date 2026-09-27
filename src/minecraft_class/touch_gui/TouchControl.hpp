//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/render_context/InputRenderContext.hpp"

class TouchControl
{
private:
	void** vtable;
	
public:
	void render_virtual(InputRenderContext& context);
};
