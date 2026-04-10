#pragma once

#include <raylib.h>

struct AssetManager {
	Texture2D m_texture = {};
	Texture2D m_textures = {};
	Texture2D m_frame = {};

	void loadAll();
};