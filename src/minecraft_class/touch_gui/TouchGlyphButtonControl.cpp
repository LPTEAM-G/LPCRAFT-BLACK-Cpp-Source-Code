//Copyright (c) 2026 LPTEAM
#include "TouchGlyphButtonControl.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include <cstring>
#include <memory>
#include "minecraft_class/touch_gui/ButtonColors.hpp"

TouchGlyphButtonControl::constructor_type TouchGlyphButtonControl::constructor_orig = nullptr;

TouchGlyphButtonControl* TouchGlyphButtonControl::constructor(
	TouchGlyphButtonControl* this_ptr,
	std::function<RectangleArea ()> rect_getter,
	std::function<bool()> func,
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
	struct small_button_rect
	{
		float width;
		float height;
		float center_x;
	};
	static std::shared_ptr<small_button_rect> rect_ptr = std::make_shared<small_button_rect>();
	static float screen_width = 0.0f;
	screen_width = MinecraftClient::instance->get_screen_width();

	//UI的构造函数有时会突然在MinecraftClient之前构造
	//所以这里必须判空
	if (str == "button.chat" and MinecraftClient::instance != nullptr)
	{
		RectangleArea rect = rect_getter();
		float button_width = rect.x_end - rect.x_start;
		float button_height = rect.y_end - rect.y_start;

		rect_ptr->width = button_width;
		rect_ptr->height = button_height;
		rect_ptr->center_x = (screen_width - rect_ptr->width) / 2;

		//按值捕获, 防止出作用域后访问空指针
		rect_getter = [=]() -> RectangleArea
		{
			//此物同时决定了视觉位置和触摸位置
			return RectangleArea
			{
				.x_start = rect_ptr->center_x,
				.x_end = rect_ptr->center_x + rect_ptr->width,
				.y_start = 0.0f,
				.y_end = rect_ptr->height
			};
		};
	}
	//在安卓端它的RectangleArea被设定为全0
	//这里让其重新可以绘制, 并居于聊天按钮右侧
	else if (str == "button.pause" and MinecraftClient::instance != nullptr)
	{
		rect_getter = [=]() -> RectangleArea
		{
			
			return RectangleArea
			{
				.x_start = rect_ptr->center_x + rect_ptr->width,
				.x_end = rect_ptr->center_x + rect_ptr->width * 2,
				.y_start = 0.0f,
				.y_end = rect_ptr->height
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
