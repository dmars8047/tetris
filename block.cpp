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

void Block::Render(SDL_Renderer *renderer)
{
    SDL_Rect rect = GetRenderRect();
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Block::GetRenderRect() {
    SDL_Rect rect = SDL_Rect{x : m_x + 1, y : m_y + 1, w : 63, h : 63};
    return rect;
}

void Block::MoveRight()
{
    m_x += 64;
}

void Block::MoveLeft()
{
    m_x -= 64;
}

void Block::MoveUp()
{
    m_y -= 64;
}

void Block::MoveDown()
{
    m_y += 64;
}

void Block::SetPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

int Block::GetPosition_X() {
    return m_x;
}

int Block::GetPosition_Y() {
    return m_y;
}