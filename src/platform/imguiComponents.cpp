#include "imguiComponents.h"
#include "../gameLayer/block.h"

void display_block_selector(ImGuiIO& io) {
	ImTextureID block_tex_id = io.Fonts->TexID;
	float block_tex_w = (float)io.Fonts->TexWidth;
	float block_tex_h = (float)io.Fonts->TexHeight;

	for (int i = 0; i < Block::blockTypes.size(); i++)
	{
		// UV coordinates are often (0.0f, 0.0f) and (1.0f, 1.0f) to display an entire textures.
		// Here are trying to display only a 32x32 pixels area of the texture, hence the UV computation.
		// Read about UV coordinates here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
		ImGui::PushID(i);
		if (i > 0) {
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(i - 1.0f, i - 1.0f));
		}
		ImVec2 size = ImVec2(32.0f, 32.0f);                         // Size of the image we want to make visible
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
		ImVec2 uv1 = ImVec2(32.0f / block_tex_w, 32.0f / block_tex_h);    // UV coordinates for (32,32) in our texture
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
		if (ImGui::ImageButton("", block_tex_id, size, uv0, uv1, bg_col, tint_col)) {
			// block selected
			//pressed_count += 1;
		}
		if (i > 0) {
			ImGui::PopStyleVar();
		}
		ImGui::PopID();
	}
}