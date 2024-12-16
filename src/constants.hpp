#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>

const std::string APP_NAME = "Tetris";

const int WINDOW_WIDTH = 1216;
const int WINDOW_HEIGHT = 1408;

const int BLOCK_SIZE = 64;

// Background colors
const int BACKGROUND_RED = 17;
const int BACKGROUND_GREEN = 17;
const int BACKGROUND_BLUE = 17;
const int BACKGROUND_ALPHA = 255;

const std::string MAIN_FONT_ID = "main-font";

const std::string SHARED_FONT_TEXTURE_0 = "font-texture-number-0";
const std::string SHARED_FONT_TEXTURE_1 = "font-texture-number-1";
const std::string SHARED_FONT_TEXTURE_2 = "font-texture-number-2";
const std::string SHARED_FONT_TEXTURE_3 = "font-texture-number-3";
const std::string SHARED_FONT_TEXTURE_4 = "font-texture-number-4";
const std::string SHARED_FONT_TEXTURE_5 = "font-texture-number-5";
const std::string SHARED_FONT_TEXTURE_6 = "font-texture-number-6";
const std::string SHARED_FONT_TEXTURE_7 = "font-texture-number-7";
const std::string SHARED_FONT_TEXTURE_8 = "font-texture-number-8";
const std::string SHARED_FONT_TEXTURE_9 = "font-texture-number-9";

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

enum class Scene
{
    Opening,
    GamePlay,
    GameOver,
};

const SDL_Color COLOR_WHITE = SDL_Color{255, 255, 255, 255};
// Tetromino Colors
const SDL_Color COLOR_TETROMINO_T = SDL_Color{221, 10, 178, 255};
const SDL_Color COLOR_TETROMINO_S = SDL_Color{83, 218, 63, 255};
const SDL_Color COLOR_TETROMINO_Z = SDL_Color{253, 63, 89, 255};
const SDL_Color COLOR_TETROMINO_O = SDL_Color{254, 251, 52, 255};
const SDL_Color COLOR_TETROMINO_I = SDL_Color{1, 237, 250, 255};
const SDL_Color COLOR_TETROMINO_L = SDL_Color{255, 200, 46, 255};
const SDL_Color COLOR_TETROMINO_J = SDL_Color{0, 119, 211, 255};

#endif