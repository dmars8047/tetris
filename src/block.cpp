#include "constants.hpp"
#include "block.hpp"

Block::Block()
{
    m_x = 0;
    m_y = 0;
}

Block::Block(int x, int y)
{
    m_x = x;
    m_y = y;
}

Block::~Block()
{
    // delete m_Rect;
};

void Block::Render(SDL_Renderer *renderer) const
{
    SDL_Rect rect = GetRenderRect();
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Block::GetRenderRect() const {
    SDL_Rect rect = SDL_Rect{x : m_x + 1, y : m_y + 1, w : BLOCK_SIZE - 1, h : BLOCK_SIZE - 1};
    return rect;
}

void Block::SetPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

int Block::GetPosition_X() const {
    return m_x;
}

int Block::GetPosition_Y() const {
    return m_y;
}