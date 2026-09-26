
#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY) {
	return Rectangle{
		static_cast<float>(x) * cellSizePixelsX,
		static_cast<float>(y) * cellSizePixelsY,
		static_cast<float>(cellSizePixelsX),
		static_cast<float>(cellSizePixelsY)
	};
}

bool get_random_chance(std::ranlux24_base& rng, float chance) {
	auto dice = get_random_number<float>(rng, 0.0, 1.0);
	return dice <= chance;
}