#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <gameMain.h>

#include "Block.h"
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

		// Block selector
		ImGui::ShowDemoWindow();

		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		if (ImGui::TreeNode("Block selector")) {
			display_block_selector(io);
			ImGui::TreePop();
		}


		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();


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