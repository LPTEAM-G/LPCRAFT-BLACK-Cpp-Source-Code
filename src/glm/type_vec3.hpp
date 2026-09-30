//Copyright (c) 2026 LPTEAM
#pragma once

namespace glm
{
	namespace detail
	{
		template<typename T>
		struct tvec3
		{
			using value_type = T;

			value_type x;
			value_type y;
			value_type z;

			tvec3()noexcept: x(), y(), z() {}
			
			tvec3(value_type value) noexcept:
				x(value),
				y(value),
				z(value)
			{}

			tvec3(value_type _x, value_type _y, value_type _z) noexcept:
				x(_x),
				y(_y),
				z(_z)
			{}
			
			tvec3(const tvec3& other) noexcept:
				x(other.x),
				y(other.y),
				z(other.z)
			{}
		};
	}

	using vec3 = detail::tvec3<float>;
	using dvec3 = detail::tvec3<double>;
	using ivec3 = detail::tvec3<int>;
	using uvec3 = detail::tvec3<unsigned int>;
	using bvec3 = detail::tvec3<bool>;
}
