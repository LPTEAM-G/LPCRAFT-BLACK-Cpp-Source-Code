#ifndef TOOLS_MEMORY_PAGE_GUARD_HPP
#define TOOLS_MEMORY_PAGE_GUARD_HPP

#include <bits/sysconf.h>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>

namespace tools
{
	using protect_enum = int;
	
	namespace protect_type
	{
		constexpr protect_enum r = PROT_READ;
		constexpr protect_enum w = PROT_WRITE;
		constexpr protect_enum x = PROT_EXEC;
		constexpr protect_enum rw = r | w;
		constexpr protect_enum rx = r | x;
		constexpr protect_enum wx = w | x;
		constexpr protect_enum rwx = r | w | x;
	}

	inline static unsigned long get_page_size() noexcept;

	inline static void* cal_start_address(void* target_address_in_a_page) noexcept
	{
		return (void*)((uintptr_t)target_address_in_a_page & ~(get_page_size() - 1));
	}

	inline static unsigned long get_page_size() noexcept
	{
		return sysconf(_SC_PAGESIZE);
	}
		
	template<protect_enum before, protect_enum after>
	class memory_page_guard
	{
	private:
		void* start_addr;
		unsigned long page_count;
		unsigned long page_size;

	public:
		memory_page_guard(
			void* target_address_in_a_page,
			unsigned long changed_page_count = 1
		) noexcept:
		start_addr(nullptr),
		page_count(changed_page_count),
		page_size(get_page_size())
		{
			if (page_count == 0) return;
			start_addr = cal_start_address(target_address_in_a_page);
			mprotect(
				start_addr,
				page_size * page_count,
				after
			);
		}

		~memory_page_guard() noexcept
		{
			if (page_count == 0) return;
			mprotect(
				start_addr,
				page_size * page_count,
				before
			);
		}
		
		memory_page_guard(const memory_page_guard&) = delete;
		memory_page_guard(memory_page_guard&&) = delete;
		memory_page_guard& operator=(const memory_page_guard&) = delete;
		memory_page_guard& operator=(memory_page_guard&&) = delete;
	};

	template<protect_enum after>
	using text_section_guard = memory_page_guard<protect_type::rx, after>;
	using text_section_writable_guard = text_section_guard<protect_type::rwx>;

	template<protect_enum after>
	using vtable_area_guard = memory_page_guard<protect_type::r, after>;
	using vtable_area_writable_guard = vtable_area_guard<protect_type::rw>;
}

#endif
