#pragma once 

#include <imgui.h>
#include "../gameLayer/assetManager.h"
#include "../gameLayer/block.h"

void display_block_selector(
    ImGuiIO& io, 
    const AssetManager& assetManager, 
    BlockType& selectedBlockType
);