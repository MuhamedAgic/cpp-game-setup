#include <raylib.h>
#include "imguiComponents.h"
#include "../gameLayer/block.h"
#include "../gameLayer/helpers.h"
#include <iostream>

void display_block_selector(
    ImGuiIO& io,
    const AssetManager& assetManager,
    BlockType& selectedBlockType
) {
    const Texture2D& texture = assetManager.m_textures;

    ImTextureID texture_id = reinterpret_cast<ImTextureID>(
        static_cast<uintptr_t>(texture.id)
    );

    // Columns in the texture atlas
    const int atlasColumns = texture.width / Block::blockSizePx;

    // Actual ImGui button width
    const float padding = ImGui::GetStyle().FramePadding.x;
    const float buttonWidth = static_cast<float>(Block::blockSizePx) + padding * 2.0f;
    const float spacing = ImGui::GetStyle().ItemSpacing.x;
    const float availableWidth = ImGui::GetContentRegionAvail().x;
    const int uiColumns = std::max(1, static_cast<int>((availableWidth + spacing) / (buttonWidth + spacing)));

    for (int i = 0; i < Block::blockTypes.size(); ++i)
    {
        ImGui::PushID(i);

        const int atlasX = i % atlasColumns;
        const int atlasY = i / atlasColumns;

        Rectangle source = getTextureAtlas(
            atlasX,
            atlasY,
            Block::blockSizePx,
            Block::blockSizePx
        );

        ImVec2 uv0(
            source.x / texture.width,
            source.y / texture.height
        );

        ImVec2 uv1(
            (source.x + source.width) / texture.width,
            (source.y + source.height) / texture.height
        );

        ImVec2 size(
            static_cast<float>(Block::blockSizePx),
            static_cast<float>(Block::blockSizePx)
        );

        if (ImGui::ImageButton(
            "##block",
            texture_id,
            size,
            uv0,
            uv1,
            ImVec4(0, 0, 0, 0),
            ImVec4(1, 1, 1, 1)
        ))
        {
            selectedBlockType = Block::blockTypes.at(i);
        }

        // Draw selection border immediately after the button
        if (selectedBlockType == Block::blockTypes.at(i))
        {
            ImVec2 min = ImGui::GetItemRectMin();
            ImVec2 max = ImGui::GetItemRectMax();

            ImGui::GetWindowDrawList()->AddRect(
                ImVec2(min.x - 2.0f, min.y - 2.0f),
                ImVec2(max.x + 2.0f, max.y + 2.0f),
                IM_COL32(255, 220, 50, 255),
                0.0f,
                0,
                3.0f
            );
        }

        ImGui::PopID();

        if (i % uiColumns != uiColumns - 1)
        {
            ImGui::SameLine();
        }
    }
}
