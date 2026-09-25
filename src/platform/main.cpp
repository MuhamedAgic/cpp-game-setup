#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include "../gameLayer/game.h"
#include "gameMain.h"
#include "block.h"
#include "imguiComponents.h"


int main(void) {

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE); // no log output to the console by raylib
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1500, 1000, "window name");
	SetExitKey(KEY_NULL); // Disable Esc from closing window
	SetTargetFPS(240);

#pragma region imgui
	rlImGuiSetup(true);

	bool show_demo_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO &io = ImGui::GetIO(); 
	(void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;       // Enable gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 2;


#pragma endregion


	if (!initGame()) {
		return 0;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

	#pragma region imgui
		rlImGuiBegin();

		//docking stuff
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

		ImGui::ShowDemoWindow();

		// Block selector
		if (ImGui::TreeNode("Block selector")) {
			display_block_selector(io, game.assetManager);
			ImGui::TreePop();
		}


	#pragma endregion

		if (!updateGame()) {
			CloseWindow();
		}

	#pragma region imgui
		rlImGuiEnd();

	#pragma endregion

		EndDrawing();
	}

	CloseWindow();

	closeGame();

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion


	return 0;
}