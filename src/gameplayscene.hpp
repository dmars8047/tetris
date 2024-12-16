#ifndef GAMEPLAYSCENE_HPP
#define GAMEPLAYSCENE_HPP

#include <random>

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "timer.hpp"
#include "tetromino.hpp"
#include "preview.hpp"
#include "numericdisplay.hpp"
#include "board.hpp"
#include "assetmanager.hpp"

class GamePlayScene
{
public:
    GamePlayScene(AssetManager &assetManager, int blockSize);
    ~GamePlayScene();
    void ParseInput(SDL_Event &e);
    void Render(SDL_Renderer *renderer) const;
    void Update();
    bool IsGameOver() const;
    int GetLevels() const;
    int GetLinesCleared() const;
    int GetPoints() const;

private:
    // Random num gen
    std::random_device m_Dev;
    std::mt19937 m_Rng;
    std::uniform_int_distribution<std::mt19937::result_type> m_Dist7;
    Timer m_Timer;

    bool m_GameStarted;
    int m_BlockSize;

    const int m_MaxRotationDelta = 100;
    int m_RotationalDelta;

    const int m_MaxMovementDelta = 100;
    int m_DownwardMovementMultiplier;
    int m_MovementDelta;

    int m_RoundDelta;
    int m_RoundMax;

    int m_LinesCleared;
    int m_Level;
    int m_Points;
    int m_SoftDrops;

    bool m_IsGameOver;

    SDL_Keycode m_LastUsedKey;

    Tetromino *m_Tetromino;
    Preview *m_Preview;
    Board *m_Board;
    NumericDisplay *m_LinesDisplay;
    NumericDisplay *m_PointsDisplay;
    NumericDisplay *m_LevelDisplay;
    Mix_Music *m_Music;

    TetrominoType GetRandomTetrominoType(TetrominoType previous);
};

#endif