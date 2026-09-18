#ifndef TOOLS_MEMORY_PRINTER_HPP
#define TOOLS_MEMORY_PRINTER_HPP

#include <cstdint>

namespace tools
{
	void memory_printer(const void* address, uintptr_t bytes) noexcept;
}

#endif
