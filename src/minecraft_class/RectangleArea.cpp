//Copyright (c) 2026 LPTEAM
#include "RectangleArea.hpp"

float RectangleArea::center_x() noexcept
{
	return (x_start + x_end) * 0.5f;
}

float RectangleArea::center_y() noexcept
{
	return (y_start + y_end) * 0.5f;
}
