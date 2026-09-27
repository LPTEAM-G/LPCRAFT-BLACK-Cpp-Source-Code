//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/touch_gui/TouchControl.hpp"
#include <memory>
#include <vector>

class TouchControlSet
{
public:
	using vector_controls = std::vector<std::unique_ptr<TouchControl>>;
	
	void render(InputRenderContext& context) noexcept;
	vector_controls& get_controls() noexcept;
};
