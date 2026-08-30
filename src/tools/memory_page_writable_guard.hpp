//Copyright (c) 2026 LPTEAM
#ifndef TOOLS_MEMORY_PAGE_WRITABLE_GUARD_HPP
#define TOOLS_MEMORY_PAGE_WRITABLE_GUARD_HPP

namespace tools
{
	//使用之前请先保证目标地址所在的内存页的原权限为
	//PROT_EXEC | PROT_READ, 否则行为未定义, 甚至可能出现错误
	class memory_page_writable_guard
	{
	private:
		void* start_addr;
		unsigned long page_count;
		unsigned long page_size;

	public:
		memory_page_writable_guard(
			void* target_address_in_a_page,
			unsigned long changed_page_count = 1) noexcept;

		~memory_page_writable_guard() noexcept;
	};
}

#endif
