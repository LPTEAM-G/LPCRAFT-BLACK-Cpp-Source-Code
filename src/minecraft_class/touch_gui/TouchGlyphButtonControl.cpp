//Copyright (c) 2026 LPTEAM
#include "TouchGlyphButtonControl.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include <cstring>

TouchGlyphButtonControl::constructor_type TouchGlyphButtonControl::constructor_orig = nullptr;

TouchGlyphButtonControl* TouchGlyphButtonControl::constructor(
	TouchGlyphButtonControl* this_ptr,
	std::function<RectangleArea ()> rect_getter,
	std::function<bool ()> func,
	short p_s1,
	const ButtonColors* color,
	int uv_x,
	int uv_y,
	int uv_width,
	int uv_height,
	bool p_b1,
	int p_i5,
	float p_f1,
	std::string str,
	bool p_b2
)
{
	//UI的构造函数有时会突然在MinecraftClient之前构造
	//所以这里必须判空
	if (str == "button.chat" and MinecraftClient::instance != nullptr)
	{
		RectangleArea rect = rect_getter();
		float button_width = rect.x_end - rect.x_start;
		float button_height = rect.y_end - rect.y_start;
		float screen_width = MinecraftClient::instance->get_width();
		float center_x_start = (screen_width - button_width) / 2;
		//按值捕获, 防止出作用域后访问空指针
		rect_getter = [=]() -> RectangleArea
		{
			//此物同时决定了视觉位置和触摸位置
			return RectangleArea
			{
				.x_start = center_x_start,
				.x_end = center_x_start + button_width,
				.y_start = 0,
				.y_end = button_height
			};
		};
	}
	
	constructor_orig(
		this_ptr,
		std::move(rect_getter),
		std::move(func),
		p_s1,
		color,
		uv_x, uv_y, uv_width, uv_height,
		p_b1,
		p_i5,
		p_f1,
		std::move(str),
		p_b2
);

	return this_ptr;
}

void TouchGlyphButtonControl::install() noexcept
{
	//_ZN23TouchGlyphButtonControlC2ESt8functionIF13RectangleAreavEES0_IFbvEEsRK12ButtonColorsiiiibifSsb
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x2B2A70);
	MSHook(constructor_target, constructor, constructor_orig);
}
