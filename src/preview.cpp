#include "preview.hpp"

Preview::Preview(TetrominoType type, int blockSize)
{
    m_type = type;
    m_startX = blockSize * 12;
    m_endX = blockSize * 18;
    m_startY = blockSize;
    m_endY = blockSize * 5;

    switch (m_type)
    {
    case TetrominoType::S:
        m_Color = COLOR_TETROMINO_S;
        break;
    case TetrominoType::O:
        m_Color = COLOR_TETROMINO_O;
        break;
    case TetrominoType::I:
        m_Color = COLOR_TETROMINO_I;
        break;
    case TetrominoType::T:
        m_Color = COLOR_TETROMINO_T;
        break;
    case TetrominoType::L:
        m_Color = COLOR_TETROMINO_L;
        break;
    case TetrominoType::Z:
        m_Color = COLOR_TETROMINO_Z;
        break;
    case TetrominoType::J:
        m_Color = COLOR_TETROMINO_J;
        break;
    }

    const int renderWH = blockSize - 1;

    SDL_Rect rect_0 = {x : 0, y : 0, w : renderWH, h : renderWH};
    SDL_Rect rect_1 = {x : 0, y : 0, w : renderWH, h : renderWH};
    SDL_Rect rect_2 = {x : 0, y : 0, w : renderWH, h : renderWH};
    SDL_Rect rect_3 = {x : 0, y : 0, w : renderWH, h : renderWH};

    const int halfY = m_startY + (blockSize + (blockSize / 2));
    const int halfX = m_startX + (blockSize + (blockSize / 2));

    switch (m_type)
    {
    case TetrominoType::I:
        rect_0.x = m_startX + (blockSize) + 1;
        rect_0.y = halfY + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_1.x + blockSize;
        rect_2.y = rect_0.y;
        rect_3.x = rect_2.x + blockSize;
        rect_3.y = rect_0.y;
        break;
    case TetrominoType::O:
        rect_0.x = m_startX + (blockSize * 2) + 1;
        rect_0.y = m_startY + blockSize + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_0.x;
        rect_2.y = rect_0.y + blockSize;
        rect_3.x = rect_0.x + blockSize;
        rect_3.y = rect_0.y + blockSize;
        break;
    case TetrominoType::J:
        rect_0.x = halfX + 1;
        rect_0.y = m_startY + blockSize + 1;
        rect_1.x = rect_0.x;
        rect_1.y = rect_0.y + blockSize;
        rect_2.x = rect_1.x + blockSize;
        rect_2.y = rect_1.y;
        rect_3.x = rect_2.x + blockSize;
        rect_3.y = rect_2.y;
        break;
    case TetrominoType::L:
        rect_0.x = halfX + 1;
        rect_0.y = m_startY + (blockSize * 2) + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_1.x + blockSize;
        rect_2.y = rect_1.y;
        rect_3.x = rect_2.x;
        rect_3.y = rect_2.y - blockSize;
        break;
    case TetrominoType::T:
        rect_0.x = halfX + 1;
        rect_0.y = m_startY + (blockSize * 2) + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_1.x + blockSize;
        rect_2.y = rect_1.y;
        rect_3.x = rect_0.x + blockSize;
        rect_3.y = rect_2.y - blockSize;
        break;
    case TetrominoType::S:
        rect_0.x = halfX + 1;
        rect_0.y = m_startY + (blockSize * 2) + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_1.x;
        rect_2.y = rect_1.y - blockSize;
        rect_3.x = rect_2.x + blockSize;
        rect_3.y = rect_2.y;
        break;
    case TetrominoType::Z:
        rect_0.x = halfX + 1;
        rect_0.y = m_startY + (blockSize) + 1;
        rect_1.x = rect_0.x + blockSize;
        rect_1.y = rect_0.y;
        rect_2.x = rect_1.x;
        rect_2.y = rect_1.y + blockSize;
        rect_3.x = rect_2.x + blockSize;
        rect_3.y = rect_2.y;
        break;
    }

    m_Rects[0] = rect_0;
    m_Rects[1] = rect_1;
    m_Rects[2] = rect_2;
    m_Rects[3] = rect_3;
}

void Preview::Render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Point borderPoints[] = {
        SDL_Point{x : m_startX, y : m_startY},
        SDL_Point{x : m_startX, y : m_endY},
        SDL_Point{x : m_endX, y : m_endY},
        SDL_Point{x : m_endX, y : m_startY},
        SDL_Point{x : m_startX, y : m_startY}};

    // Draw the board
    SDL_RenderDrawLines(renderer, borderPoints, 5);

    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);

    SDL_RenderFillRects(renderer, m_Rects, 4);
}

TetrominoType Preview::GetType() const
{
    return m_type;
}
