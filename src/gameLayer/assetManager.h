#pragma once

#include <raylib.h>
#include <magic_enum/magic_enum.hpp>



struct AssetManager {

	Texture2D m_texture = {};
	Texture2D m_textures = {};
	Texture2D m_frame = {};

	void loadAll();
};