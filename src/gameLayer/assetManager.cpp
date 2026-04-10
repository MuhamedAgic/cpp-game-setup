#include "assetManager.h"


void AssetManager::loadAll() {
	m_texture = LoadTexture(RESOURCES_PATH "dirt.png");
	m_textures = LoadTexture(RESOURCES_PATH "textures.png");
	m_frame = LoadTexture(RESOURCES_PATH "frame.png");
}