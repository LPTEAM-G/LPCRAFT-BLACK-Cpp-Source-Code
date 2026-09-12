#ifndef TOOLS_VTABLE_SETTER_HPP
#define TOOLS_VTABLE_SETTER_HPP

#include "tools/memory_page_guard.hpp"

namespace tools
{
	class vtable_setter
	{
	private:
		vtable_area_writable_guard guard;
		void* address;
		unsigned long ptr_count;

	public:
		vtable_setter(
			void* vtable_address,
			unsigned long ptr_count_in_vtable
		) noexcept;

		void set_at(unsigned long index, void* ptr) noexcept;

		~vtable_setter() noexcept = default;
	};
}

#endif
