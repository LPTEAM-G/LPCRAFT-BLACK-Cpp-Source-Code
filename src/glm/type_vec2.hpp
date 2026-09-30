//Copyright (c) 2026 LPTEAM
#pragma once

namespace glm
{
	namespace detail
	{
		template<typename T>
		struct tvec2
		{
			using value_type = T;

			value_type x;
			value_type y;

			tvec2()noexcept: x(), y() {}
			
			tvec2(value_type value) noexcept:
				x(value),
				y(value)
			{}

			tvec2(value_type _x, value_type _y) noexcept:
				x(_x),
				y(_y)
			{}
			
			tvec2(const tvec2& other) noexcept:
				x(other.x),
				y(other.y)
			{}
		};
	}

	using vec2 = detail::tvec2<float>;
	using dvec2 = detail::tvec2<double>;
	using ivec2 = detail::tvec2<int>;
	using uvec2 = detail::tvec2<unsigned int>;
	using bvec2 = detail::tvec2<bool>;
}
