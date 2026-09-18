#include "Minecraft.hpp"
#include "minecraft_class/Level.hpp"
#include <cstdint>

Level* Minecraft::get_level() noexcept
{
	Level** level_result = *(Level***)((uintptr_t)this + 68);
	if (level_result != nullptr)
		return *level_result;
	return nullptr;
}
