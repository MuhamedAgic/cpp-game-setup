
#include "GameMap.h"
#include "asserts.h"

void GameMap::create(int w, int h) {
	reset();

	m_mapData.resize(w * h);

	m_w = w;
	m_h = h;

	for (auto& entity : m_mapData) {
		entity = {};
	}

}


void GameMap::reset() {
	*this = {};
}

bool GameMap::isWithinBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < m_w && y < m_h;
}



Block& GameMap::getBlockUnsafe(int x, int y) {
	permaAssertCommentDevelopement(m_mapData.size() == m_w * m_h, "Map data not initialized");
	permaAssertCommentDevelopement(isWithinBounds(x, y), "getBlockUnsafe out of bounds error");
	return m_mapData[x + y * m_w]; // 1d to 2d array trick
}


Block* GameMap::getBlockSafe(int x, int y) {
	permaAssertCommentDevelopement(m_mapData.size() == m_w * m_h, "Map data not initialized");
	if (!isWithinBounds(x, y)) {
		return nullptr;
	}
	return &m_mapData[x + y * m_w]; // 1d to 2d array trick
}