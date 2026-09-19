//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/Material.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"

class Block
{
public:
	static Block** get_block_table() noexcept;
	Material* get_material() noexcept;
	TextureUVCoordinateSet* get_texture_virtual(signed char face) noexcept;
};

