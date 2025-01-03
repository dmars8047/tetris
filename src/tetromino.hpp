#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <random>

#include "block.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "screenconfig.hpp"

class Tetromino
{
public:
    Tetromino(TetrominoType type, int blockSize);
    void Render(SDL_Renderer *renderer) const;
    void MoveLeft(const Board &board);
    void MoveRight(const Board &board);
    void MoveDown(Board &board);
    bool DetectCollision(const Board &board) const;
    bool GetIsLanded() const;
    void Rotate(const Board &board);

private:
    int m_BlockSize;
    std::array<Block, 4> m_Blocks;
    TetrominoType m_type;
    TetrominoRotation m_rotation;
    bool m_IsLanded;
    std::array<Block, 4> GetInitialBlocks(TetrominoType type);
    SDL_Color m_Color;
};

#endif