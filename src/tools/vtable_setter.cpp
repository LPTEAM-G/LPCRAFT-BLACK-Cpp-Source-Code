//Copyright (c) 2026 LPTEAM
#include "vtable_setter.hpp"
#include "tools/memory_page_guard.hpp"
#include <cstdint>
#include <cmath>

namespace tools
{
	vtable_setter::vtable_setter(
		vtable_setter::value_type vtable_address,
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
	varray((void**)vtable_address),
	ptr_count(ptr_count_in_vtable)
	{}

	vtable_setter::value_type& vtable_setter::operator[](unsigned long index) noexcept
	{
		return varray[index];
	}

	vtable_setter::iterator vtable_setter::begin() noexcept
	{
		return varray;
	}

	vtable_setter::iterator vtable_setter::end() noexcept
	{
		return varray + ptr_count;
	}

	vtable_setter::const_iterator vtable_setter::begin() const noexcept
	{
		return varray;
	}

	vtable_setter::const_iterator vtable_setter::end() const noexcept
	{
		return varray + ptr_count;
	}

	vtable_setter::~vtable_setter() noexcept
	{
		__builtin___clear_cache((char*)varray, (char*)((uintptr_t)varray + get_page_size()));
	}
}
