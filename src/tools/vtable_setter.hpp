#ifndef TOOLS_VTABLE_SETTER_HPP
#define TOOLS_VTABLE_SETTER_HPP

#include "tools/memory_page_guard.hpp"

namespace tools
{
	class vtable_setter
	{
	public:
		using value_type = void*;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		
	private:
		vtable_area_writable_guard guard;
		void** varray;
		unsigned long ptr_count;

	public:
		vtable_setter(
			value_type vtable_address,
			unsigned long ptr_count_in_vtable
		) noexcept;

		value_type& operator[](unsigned long index) noexcept;

		iterator begin() noexcept;
		iterator end() noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;

		~vtable_setter() noexcept;
	};
}

#endif
