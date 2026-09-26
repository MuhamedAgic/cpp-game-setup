#pragma once
#include <raylib.h>
#include <random>
#include <concepts>
#include <type_traits>

template<typename T> 
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T> 
T get_random_number(std::ranlux24_base& rng, T min, T max) {
    if constexpr (std::floating_point<T>) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(rng);
    }
    else {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }
}

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY);
bool get_random_chance(std::ranlux24_base& rng, float chance);