#include "vtable_setter.hpp"
#include "tools/memory_page_guard.hpp"
#include <cstdint>
#include <cmath>

namespace tools
{
	vtable_setter::vtable_setter(
		void* vtable_address,
		unsigned long ptr_count_in_vtable
	) noexcept:
	guard(
		vtable_address,
		[=]() -> unsigned long
		{
			void* page_start = cal_start_address(vtable_address);
			void* end_address =
				(void*)((uintptr_t)vtable_address + ptr_count_in_vtable * sizeof(void*));
			uintptr_t bytes = (uintptr_t)end_address - (uintptr_t)page_start;
			uintptr_t page_size = get_page_size();
			unsigned long page_count = (bytes + page_size - 1) / page_size;
			return page_count;
		}()
	),
	address(vtable_address),
	ptr_count(ptr_count_in_vtable)
	{}

	void vtable_setter::set_at(unsigned long index, void* ptr) noexcept
	{
		if (index >= ptr_count) return;
		((void**)address)[index] = ptr;
	}
}
