#pragma once

#include <vector>
#include "block.h"

struct GameMap {
	int m_w;
	int m_h;

	std::vector<Block> m_mapData;

	void create(int w, int h);
	void reset();

	bool isWithinBounds(int x, int y);

	Block& getBlockUnsafe(int x, int y);
	Block* getBlockSafe(int x, int y);



};

