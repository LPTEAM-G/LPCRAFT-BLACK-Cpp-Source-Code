//Copyright (c) 2026 LPTEAM
#include "memory_page_writable_guard.hpp"
#include <asm-generic/mman-common.h>
#include <bits/sysconf.h>
#include <cstdint>
#include <sys/mman.h>

namespace tools
{
	memory_page_writable_guard::memory_page_writable_guard(
		void* address_in_a_page,
		unsigned long changed_page_count) noexcept:
		page_count(changed_page_count)
	{
		if (page_count == 0) return;
		page_size = sysconf(_SC_PAGESIZE);
		start_addr = (void*)((uintptr_t)address_in_a_page & ~(page_size - 1));
		mprotect(
			start_addr,
			page_size * page_count,
			PROT_EXEC | PROT_READ | PROT_WRITE
		);
	}

	memory_page_writable_guard::~memory_page_writable_guard() noexcept
	{
		if (page_count == 0) return;
		mprotect(
			start_addr,
			page_size * page_count,
			PROT_EXEC | PROT_READ
		);
	}
}
