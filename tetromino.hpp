#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>

#include "block.hpp"
#include "constants.hpp"

class Tetromino {
    public:
        Tetromino(TetrominoType type);
        void Render(SDL_Renderer *renderer);
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void Rotate();
    private:
        std::array<Block, 4> m_Blocks;
        TetrominoType m_type;
        TetrominoRotation m_rotation;
        std::array<Block, 4> GetInitialBlocks(TetrominoType type);
};

#endif