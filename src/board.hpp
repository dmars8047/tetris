#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "block.hpp"

class Board
{
public:
    Board();
    bool IsColliding(int x, int y) const;
    void AddBlock(Block block);
    void Render(SDL_Renderer *g_Renderer) const;
private:
    int m_Min_X;
    int m_Max_X;
    int m_Min_Y;
    int m_Max_Y;
    std::vector<Block> m_Blocks;
};

#endif