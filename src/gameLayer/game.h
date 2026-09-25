#pragma once

#include "gameData.h"

struct Game {
	GameData data;
	AssetManager assetManager;
};

extern Game game;