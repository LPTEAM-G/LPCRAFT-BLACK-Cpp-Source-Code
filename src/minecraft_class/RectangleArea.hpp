//Copyright (c) 2026 LPTEAM
#pragma once

struct RectangleArea
{
	float x_start;
	float x_end;
	float y_start;
	float y_end;

	RectangleArea() noexcept = default;
	RectangleArea(const RectangleArea&) noexcept = default;
	RectangleArea(float xs, float ys, float xe, float ye) noexcept;

	void resize_around_center(float new_width, float new_hegiht) noexcept;
	RectangleArea scale(float factor) const noexcept;
	bool is_empty() const noexcept;
	float center_x() const noexcept;
	float center_y() const noexcept;
	
};
