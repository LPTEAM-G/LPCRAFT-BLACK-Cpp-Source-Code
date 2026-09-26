//Copyright (c) 2026 LPTEAM
#pragma once

struct RectangleArea
{
	float x_start;
	float x_end;
	float y_start;
	float y_end;

	float center_x() noexcept;
	float center_y() noexcept;
};
