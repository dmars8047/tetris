#include <algorithm>
#include <unordered_map>

#include "board.hpp"
#include "constants.hpp"

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

Board::Board(int blockSize)
{
    m_Min_X = 0;
    m_Min_Y = 0;
    m_Max_X = blockSize * 11;
    m_Max_Y = blockSize * 21;
    m_BlockSize = blockSize;
}

bool Board::IsColliding(int x, int y) const
{
    // Check the dimensions of the board
    if (x <= m_Min_X || x >= m_Max_X || y <= m_Min_Y || y >= m_Max_Y)
    {
        return true;
    }

    for (auto block : m_Blocks)
    {
        if (block.GetPosition_X() == x && block.GetPosition_Y() == y)
        {
            return true;
        }
    }

    return false;
}

void Board::AddBlock(Block block)
{
    m_Blocks.emplace_back(block);
}

void Board::Render(SDL_Renderer *renderer) const
{
    // Draw the grid
    SDL_SetRenderDrawColor(renderer, 51, 51, 51, 0);

    // Draw vertical grid lines
    for (int x = m_BlockSize * 2; x < m_Max_X; x += m_BlockSize)
    {
        SDL_RenderDrawLine(renderer, x, m_BlockSize, x, m_Max_Y);
    }

    // Draw horizontal grid lines
    for (int y = m_BlockSize * 2; y < m_Max_Y; y += m_BlockSize)
    {
        SDL_RenderDrawLine(renderer, m_BlockSize, y, m_Max_X, y);
    }

    // Draw the border of the board
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    SDL_Point boardPoints[] = {
        SDL_Point{x : m_BlockSize, y : m_BlockSize},
        SDL_Point{x : m_BlockSize, y : m_Max_Y},
        SDL_Point{x : m_Max_X, y : m_Max_Y},
        SDL_Point{x : m_Max_X, y : m_BlockSize},
        SDL_Point{x : m_BlockSize, y : m_BlockSize}};

    // Draw the board
    SDL_RenderDrawLines(renderer, boardPoints, 5);

    // Render Blocks
    for (auto &block : m_Blocks)
    {
        block.Render(renderer);
    }
}

int Board::ClearCompletedRows()
{
    // Create a map to count the blocks in each row
    std::unordered_map<int, int> rowCount;

    // Count the number of blocks in each row
    for (const Block &block : m_Blocks)
    {
        rowCount[block.GetPosition_Y()]++;
    }

    // Collect all rows with exactly 10 blocks
    std::vector<int> fullRows;
    for (const auto &[row, count] : rowCount)
    {
        if (count == 10)
        {
            fullRows.push_back(row);
        }
    }

    // Sort the rows in descending order
    std::sort(fullRows.begin(), fullRows.end());

    // Remove full rows and adjust rows above
    for (int row : fullRows)
    {
        // Remove all blocks in the current row
        m_Blocks.erase(
            std::remove_if(m_Blocks.begin(), m_Blocks.end(),
                           [row](const Block &block)
                           { return block.GetPosition_Y() == row; }),
            m_Blocks.end());

        // Lower the row value of all blocks above the removed row
        for (auto &block : m_Blocks)
        {
            if (block.GetPosition_Y() < row)
            {
                block.SetPosition(block.GetPosition_X(), block.GetPosition_Y() + m_BlockSize);
            }
        }
    }

    return fullRows.size();
}
