#pragma once 
#include <array>
#include <magic_enum/magic_enum.hpp>

enum class BlockType {
	AIR,
	DIRTGRASS,
	STONE,
	GRASS,
	SAND,
	SANDRUBY,
	HARDSAND,
	WOOD,
	STONECOAL,
	REDDIRT,
	WOODLOG,
	GRASSBLOCK,
	BRONZEORE,
	SILVERORE,
	GOLDORE,
	BRONZEBLOCK,
	SOLVERBLOCK,
	GOLDBLOCK,
	BRICKBLOCK,
	SNOWBLOCK,
	BLUEBLOCK,
	RUBY,
	PLATFORM,
	REDPLATFORM,
	GLASS,
	OVEN,
	PAINTING,
	TREE,
	ICEBLOCKWITHBLUERUBY,
	BLUERUBY

};

using BlockTypes = std::array<BlockType, magic_enum::enum_count<BlockType>()>;

struct Block {
	constexpr static BlockTypes blockTypes = magic_enum::enum_values<BlockType>();
	BlockType type;
};

