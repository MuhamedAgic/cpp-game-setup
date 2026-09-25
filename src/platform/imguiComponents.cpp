#include <raylib.h>
#include "imguiComponents.h"
#include "../gameLayer/block.h"
#include "../gameLayer/helpers.h"
#include <iostream>

// TODO select block make thick border and make block usable
void display_block_selector(
    ImGuiIO& io, 
    const AssetManager& assetManager,
    BlockType& selectedBlockType
) {
    const Texture2D& texture = assetManager.m_textures;

    ImTextureID texture_id = reinterpret_cast<ImTextureID>(
            static_cast<uintptr_t>(texture.id)
    );

    const int columns = texture.width / Block::blockSizePx;

    for (int i = 0; i < Block::blockTypes.size(); ++i)
    {
        ImGui::PushID(i);

        const int atlasX = i % columns;
        const int atlasY = i / columns;

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
        )) {
            selectedBlockType = Block::blockTypes.at(i);
        }
        
        // if (i % 10 != 9) {
        //     ImGui::SameLine();
        // }
        ImGui::PopID();

        // Draw selection border
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
    }

}


