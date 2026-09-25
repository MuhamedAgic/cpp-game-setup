#include <raylib.h>
#include <asserts.h>
#include <cmath>
#include <magic_enum/magic_enum.hpp>

#include "game.h"
#include "gameMain.h"
#include "block.h"
#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"
#include "../platform/imguiComponents.h"


bool initGame()
{
	game.assetManager.loadAll();

	game.data.gameMap.create(30, 10);

	for (int y = 0; y < game.data.gameMap.m_h; y++) {
		for (int x = 0; x < game.data.gameMap.m_w; x++) {
			auto& block = game.data.gameMap.getBlockUnsafe(x, y);

			float s = (std::sin(x) + 1.f) / 2.f;

			if (game.data.gameMap.m_h - (game.data.gameMap.m_h * 0.3 * s) - game.data.gameMap.m_h * 0.5 < y){
				game.data.gameMap.getBlockUnsafe(x, y).type = BlockType::DIRTGRASS;
			}else {
				game.data.gameMap.getBlockUnsafe(x, y).type = BlockType::AIR;
			}
		}
	}

	game.data.gameMap.getBlockUnsafe(0, 0).type = BlockType::DIRTGRASS;
	game.data.gameMap.getBlockUnsafe(1, 1).type = BlockType::GRASS;
	game.data.gameMap.getBlockUnsafe(2, 2).type = BlockType::GOLDBLOCK;
	game.data.gameMap.getBlockUnsafe(3, 3).type = BlockType::GLASS;
	game.data.gameMap.getBlockUnsafe(4, 4).type = BlockType::PLATFORM;

	game.data.camera.target = { 0, 0 }; // world space centre of view
	game.data.camera.rotation = 0.0f;
	game.data.camera.zoom = 100.0f;

	
	return true;
}

void processKeyPress(GameData& gameData, float deltaTime) {
	// 7 blocks per seconds here because block is 1 px
	if (IsKeyDown(KEY_A)) { gameData.camera.target.x -= 7 * deltaTime; }
	if (IsKeyDown(KEY_D)) { gameData.camera.target.x += 7 * deltaTime; }
	if (IsKeyDown(KEY_W)) { gameData.camera.target.y -= 7 * deltaTime; }
	if (IsKeyDown(KEY_S)) { gameData.camera.target.y += 7 * deltaTime; }
}

bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { 
		deltaTime = 1 / 5.f; 
	}

	ClearBackground({ 75, 75, 150, 255 });

	BeginMode2D(game.data.camera);

	Rectangle textureUV;
	int block_wh = 32;

	processKeyPress(game.data, deltaTime);

	// Block selector
	ImGuiIO &io = ImGui::GetIO();
	if (ImGui::Begin("Block selector")) {
		display_block_selector(io, game.assetManager, game.data.current_block_type);
	}
	ImGui::End();
	
	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), game.data.camera);
	int mouseBlockXPos = static_cast<int>(worldPos.x);
	int mouseBlockYPos = static_cast<int>(worldPos.y);

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		auto block = game.data.gameMap.getBlockSafe(mouseBlockXPos, mouseBlockYPos);
		if (block) {
			*block = {};
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		auto block = game.data.gameMap.getBlockSafe(mouseBlockXPos, mouseBlockYPos);
		if (block) {
			block->type = game.data.current_block_type;
		}
	}

	for (int y = 0; y < game.data.gameMap.m_h; y++) {
		for (int x = 0; x < game.data.gameMap.m_w; x++) {
			auto& block = game.data.gameMap.getBlockUnsafe(x, y);

			if (block.type != BlockType::AIR) {
				float size = 1;
				float posX = x * size;
				float posY = y * size;

				// one block step in the texture atlas
				textureUV.width = 32;
				textureUV.height = 32;

				textureUV.x = static_cast<int>(block.type) * textureUV.width;
				textureUV.y = 0; // 0 is the first row in the texture atlas here

				DrawTexturePro(
					game.assetManager.m_textures,
					getTextureAtlas(static_cast<int>(block.type), 0, block_wh, block_wh), // source
					{ static_cast<float>(x), static_cast<float>(y), size, size }, // dest
					{}, // origin top left corner
					0, // rotation
					WHITE // tint
				);
			}
		}
	}

	DrawTexturePro(
		game.assetManager.m_frame,
		getTextureAtlas(0, 0, static_cast<float>(game.assetManager.m_frame.width), static_cast<float>(game.assetManager.m_frame.height)), // source
		{ static_cast<float>(mouseBlockXPos), static_cast<float>(mouseBlockYPos), 1, 1 }, // dest
		{0, 0}, // origin top left corner
		0, // rotation
		WHITE // tint
	);

	EndMode2D();

	return true;
}

void closeGame()
{
}
