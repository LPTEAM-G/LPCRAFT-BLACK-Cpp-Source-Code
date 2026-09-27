//Copyright (c) 2026 LPTEAM
#include "TouchControlSet.hpp"
#include "minecraft_class/GuiData.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"
#include <cstdint>
#include <string>

void TouchControlSet::render(InputRenderContext& context) noexcept
{
	
	MinecraftInputRenderContext* ctx = (MinecraftInputRenderContext*)&context;

	std::string str = MinecraftClient::instance->get_local_player_position_text();
	RectangleArea rect = ctx->get_scaled_text_area(str, 0, 74 * GuiData::get_gui_scale());
	ctx->draw_square(rect, {0, 0, 0, 0.5});
	ctx->draw_text(str, 0, 74 * GuiData::get_gui_scale(), {1,1,1,1});

	vector_controls& controls = get_controls();
	for (auto& control : controls)
	{
		control->render_virtual(context);
	}
}

TouchControlSet::vector_controls& TouchControlSet::get_controls() noexcept
{
	return *(vector_controls*)((uintptr_t)this + 12);
}
