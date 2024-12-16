#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "block.hpp"

class Board
{
public:
    Board(int blockSize);
    bool IsColliding(int x, int y) const;
    void AddBlock(Block block);
    void Render(SDL_Renderer *renderer) const;
    int ClearCompletedRows();
private:
    int m_Min_X;
    int m_Max_X;
    int m_Min_Y;
    int m_Max_Y;
    int m_BlockSize;
    std::vector<Block> m_Blocks;
};

#endif