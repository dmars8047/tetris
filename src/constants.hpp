#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

const std::string APP_NAME = "Tetris";

const int SCALING_VALUE = 2;

const int WINDOW_WIDTH = 768 / SCALING_VALUE;
const int WINDOW_HEIGHT = 1408 / SCALING_VALUE;

const int BLOCK_SIZE = 64 / SCALING_VALUE;

// Background colors
const int BACKGROUND_RED = 17;
const int BACKGROUND_GREEN = 17;
const int BACKGROUND_BLUE = 17;
const int BACKGROUND_ALPHA = 255;

enum class TetrominoType
{
    I,
    O,
    T,
    L,
    J,
    S,
    Z
};

enum class TetrominoRotation
{
    Zero,
    Ninety,
    OneEighty,
    TwoSeventy,
};

#endif