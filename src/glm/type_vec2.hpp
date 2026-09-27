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
		};
	}

	using vec2 = detail::tvec2<float>;
	using dvec2 = detail::tvec2<double>;
	using ivec2 = detail::tvec2<int>;
	using uvec2 = detail::tvec2<unsigned int>;
	using bvec2 = detail::tvec2<bool>;
}
