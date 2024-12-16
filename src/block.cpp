#include "constants.hpp"
#include "block.hpp"

Block::Block()
{
    m_x = 0;
    m_y = 0;
    m_r = 255;
    m_b = 255;
    m_g = 255;
    m_size = BLOCK_SIZE;
}

Block::Block(int x, int y, int size)
{
    m_x = x;
    m_y = y;
    m_r = 255;
    m_b = 255;
    m_g = 255;
    m_size = size;
}

void Block::Render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, m_r, m_g, m_b, 255);
    SDL_Rect rect = GetRenderRect();
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Block::GetRenderRect() const
{
    SDL_Rect rect = SDL_Rect{x : m_x + 1, y : m_y + 1, w : m_size - 1, h : m_size - 1};
    return rect;
}

void Block::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Block::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}

int Block::GetPosition_X() const
{
    return m_x;
}

int Block::GetPosition_Y() const
{
    return m_y;
}