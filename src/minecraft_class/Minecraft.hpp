#ifndef MINECRAFT_CLASS_MINECRAFT_HPP
#define MINECRAFT_CLASS_MINECRAFT_HPP

#include "minecraft_class/Level.hpp"

class Minecraft
{
public:
	Level* get_level() noexcept;
};

#endif
