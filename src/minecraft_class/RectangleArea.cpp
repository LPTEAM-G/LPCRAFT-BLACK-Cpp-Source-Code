//Copyright (c) 2026 LPTEAM
#include "RectangleArea.hpp"
#include <cfloat>

RectangleArea::RectangleArea(float xs, float ys, float xe, float ye) noexcept:
	x_start(xs),
	x_end(xe),
	y_start(ys),
	y_end(ye)
{}

void RectangleArea::resize_around_center(float new_width, float new_height) noexcept
{
	float cx = center_x();
	float cy = center_y();
	*this = RectangleArea(
		cx - new_width  * 0.5f,
		cy - new_height * 0.5f,
		cx + new_width  * 0.5f,
		cy + new_height * 0.5f
	);
}

RectangleArea RectangleArea::scale(float factor) const noexcept
{
	RectangleArea result = *this;
	result.resize_around_center(
		(x_end - x_start) * factor,
		(y_end - y_start) * factor
	);
	return result;
}

bool RectangleArea::is_empty() const noexcept
{
	return (x_end - x_start) * (y_end - y_start) < FLT_EPSILON;
}

float RectangleArea::center_x() const noexcept
{
	return (x_start + x_end) * 0.5f;
}

float RectangleArea::center_y() const noexcept
{
	return (y_start + y_end) * 0.5f;
}
