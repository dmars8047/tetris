#include <iostream>

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "constants.hpp"
#include "tetromino.hpp"
#include "block.hpp"

Tetromino::Tetromino(TetrominoType type, int blockSize)
{
    m_BlockSize = blockSize;
    m_type = type;
    m_rotation = TetrominoRotation::Zero;
    m_IsLanded = false;

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

    m_Blocks = GetInitialBlocks(m_type);
}

void Tetromino::Render(SDL_Renderer *renderer) const
{
    if (m_IsLanded)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);

    SDL_Rect rect_0 = m_Blocks.at(0).GetRenderRect();
    SDL_Rect rect_1 = m_Blocks.at(1).GetRenderRect();
    SDL_Rect rect_2 = m_Blocks.at(2).GetRenderRect();
    SDL_Rect rect_3 = m_Blocks.at(3).GetRenderRect();

    SDL_Rect rects[4] = {rect_0, rect_1, rect_2, rect_3};

    SDL_RenderFillRects(renderer, rects, 4);
}

void Tetromino::Rotate(const Board &board)
{
    // Block 0 is always the keystone block
    int keystonePosition_X = m_Blocks.at(0).GetPosition_X();
    int keystonePosition_Y = m_Blocks.at(0).GetPosition_Y();

    SDL_Point point_0;
    SDL_Point point_1;
    SDL_Point point_2;
    SDL_Point point_3;

    switch (m_type)
    {
    case TetrominoType::I:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {x : keystonePosition_X, y : keystonePosition_Y + (m_BlockSize)};
            point_1 = {x : keystonePosition_X, y : keystonePosition_Y - (m_BlockSize)};
            point_2 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_3 = {x : keystonePosition_X, y : keystonePosition_Y + (m_BlockSize * 2)};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {x : keystonePosition_X - (m_BlockSize), y : keystonePosition_Y};
            point_1 = {x : keystonePosition_X - (m_BlockSize * 2), y : keystonePosition_Y};
            point_2 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_3 = {x : keystonePosition_X + (m_BlockSize), y : keystonePosition_Y};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {x : keystonePosition_X, y : keystonePosition_Y - (m_BlockSize)};
            point_1 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_2 = {x : keystonePosition_X, y : keystonePosition_Y + (m_BlockSize)};
            point_3 = {x : keystonePosition_X, y : keystonePosition_Y - (m_BlockSize * 2)};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {x : keystonePosition_X + (m_BlockSize), y : keystonePosition_Y};
            point_1 = {x : keystonePosition_X - m_BlockSize, y : keystonePosition_Y};
            point_2 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_3 = {x : keystonePosition_X + (m_BlockSize * 2), y : keystonePosition_Y};
            break;
        }

        break;
    case TetrominoType::O:
        point_0 = {x : m_Blocks.at(0).GetPosition_X(), y : m_Blocks.at(0).GetPosition_Y()};
        point_1 = {x : m_Blocks.at(1).GetPosition_X(), y : m_Blocks.at(1).GetPosition_Y()};
        point_2 = {x : m_Blocks.at(2).GetPosition_X(), y : m_Blocks.at(2).GetPosition_Y()};
        point_3 = {x : m_Blocks.at(3).GetPosition_X(), y : m_Blocks.at(3).GetPosition_Y()};
        break;
    case TetrominoType::J:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_1 = {x : keystonePosition_X, y : keystonePosition_Y - m_BlockSize};
            point_2 = {x : keystonePosition_X, y : keystonePosition_Y + m_BlockSize};
            point_3 = {x : keystonePosition_X + m_BlockSize, y : keystonePosition_Y - m_BlockSize};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X - m_BlockSize, keystonePosition_Y - m_BlockSize};
            break;
        }
        break;
    case TetrominoType::L:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X - m_BlockSize, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y - m_BlockSize};
            point_3 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y - m_BlockSize};
            break;
        }
        break;
    case TetrominoType::T:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_2 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            break;
        }
        break;
    case TetrominoType::S:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {x : keystonePosition_X, y : keystonePosition_Y};
            point_1 = {x : keystonePosition_X, y : keystonePosition_Y + m_BlockSize};
            point_2 = {x : keystonePosition_X + m_BlockSize, y : keystonePosition_Y};
            point_3 = {x : keystonePosition_X - m_BlockSize, y : keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X - m_BlockSize, keystonePosition_Y - m_BlockSize};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y - m_BlockSize};
            break;
        }
        break;
    case TetrominoType::Z:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y - m_BlockSize};
            point_2 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            break;
        case TetrominoRotation::Ninety:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X + m_BlockSize, keystonePosition_Y + m_BlockSize};
            break;
        case TetrominoRotation::OneEighty:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X - m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y + m_BlockSize};
            point_3 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            break;
        case TetrominoRotation::TwoSeventy:
            point_0 = {keystonePosition_X, keystonePosition_Y};
            point_1 = {keystonePosition_X + m_BlockSize, keystonePosition_Y};
            point_2 = {keystonePosition_X - m_BlockSize, keystonePosition_Y - m_BlockSize};
            point_3 = {keystonePosition_X, keystonePosition_Y - m_BlockSize};
            break;
        }
        break;
    }

    if (board.IsColliding(point_0.x, point_0.y) ||
        board.IsColliding(point_1.x, point_1.y) ||
        board.IsColliding(point_2.x, point_2.y) ||
        board.IsColliding(point_3.x, point_3.y))
    {
        return;
    }

    // Apply points
    m_Blocks.at(0).SetPosition(point_0.x, point_0.y);
    m_Blocks.at(1).SetPosition(point_1.x, point_1.y);
    m_Blocks.at(2).SetPosition(point_2.x, point_2.y);
    m_Blocks.at(3).SetPosition(point_3.x, point_3.y);

    switch (m_rotation)
    {
    case TetrominoRotation::Zero:
        m_rotation = TetrominoRotation::Ninety;
        break;
    case TetrominoRotation::Ninety:
        m_rotation = TetrominoRotation::OneEighty;
        break;
    case TetrominoRotation::OneEighty:
        m_rotation = TetrominoRotation::TwoSeventy;
        break;
    case TetrominoRotation::TwoSeventy:
        m_rotation = TetrominoRotation::Zero;
        break;
    }
}

void Tetromino::MoveDown(Board &board)
{
    SDL_Point point_0 = {x : m_Blocks.at(0).GetPosition_X(), y : m_Blocks.at(0).GetPosition_Y() + m_BlockSize};
    SDL_Point point_1 = {x : m_Blocks.at(1).GetPosition_X(), y : m_Blocks.at(1).GetPosition_Y() + m_BlockSize};
    SDL_Point point_2 = {x : m_Blocks.at(2).GetPosition_X(), y : m_Blocks.at(2).GetPosition_Y() + m_BlockSize};
    SDL_Point point_3 = {x : m_Blocks.at(3).GetPosition_X(), y : m_Blocks.at(3).GetPosition_Y() + m_BlockSize};

    if (board.IsColliding(point_0.x, point_0.y) ||
        board.IsColliding(point_1.x, point_1.y) ||
        board.IsColliding(point_2.x, point_2.y) ||
        board.IsColliding(point_3.x, point_3.y))
    {
        for (auto block : m_Blocks)
        {
            board.AddBlock(block);
        }

        m_IsLanded = true;
    }

    m_Blocks.at(0).SetPosition(point_0.x, point_0.y);
    m_Blocks.at(1).SetPosition(point_1.x, point_1.y);
    m_Blocks.at(2).SetPosition(point_2.x, point_2.y);
    m_Blocks.at(3).SetPosition(point_3.x, point_3.y);
}

bool Tetromino::DetectCollision(const Board &board) const
{
    for (auto &block : m_Blocks)
    {
        if (board.IsColliding(block.GetPosition_X(), block.GetPosition_Y()))
        {
            return true;
        }
    }

    return false;
}

bool Tetromino::GetIsLanded() const
{
    return m_IsLanded;
}

void Tetromino::MoveRight(const Board &board)
{
    SDL_Point point_0 = {x : m_Blocks.at(0).GetPosition_X() + m_BlockSize, y : m_Blocks.at(0).GetPosition_Y()};
    SDL_Point point_1 = {x : m_Blocks.at(1).GetPosition_X() + m_BlockSize, y : m_Blocks.at(1).GetPosition_Y()};
    SDL_Point point_2 = {x : m_Blocks.at(2).GetPosition_X() + m_BlockSize, y : m_Blocks.at(2).GetPosition_Y()};
    SDL_Point point_3 = {x : m_Blocks.at(3).GetPosition_X() + m_BlockSize, y : m_Blocks.at(3).GetPosition_Y()};

    if (board.IsColliding(point_0.x, point_0.y) ||
        board.IsColliding(point_1.x, point_1.y) ||
        board.IsColliding(point_2.x, point_2.y) ||
        board.IsColliding(point_3.x, point_3.y))
    {
        return;
    }

    m_Blocks.at(0).SetPosition(point_0.x, point_0.y);
    m_Blocks.at(1).SetPosition(point_1.x, point_1.y);
    m_Blocks.at(2).SetPosition(point_2.x, point_2.y);
    m_Blocks.at(3).SetPosition(point_3.x, point_3.y);
}

void Tetromino::MoveLeft(const Board &board)
{
    SDL_Point point_0 = {x : m_Blocks.at(0).GetPosition_X() - m_BlockSize, y : m_Blocks.at(0).GetPosition_Y()};
    SDL_Point point_1 = {x : m_Blocks.at(1).GetPosition_X() - m_BlockSize, y : m_Blocks.at(1).GetPosition_Y()};
    SDL_Point point_2 = {x : m_Blocks.at(2).GetPosition_X() - m_BlockSize, y : m_Blocks.at(2).GetPosition_Y()};
    SDL_Point point_3 = {x : m_Blocks.at(3).GetPosition_X() - m_BlockSize, y : m_Blocks.at(3).GetPosition_Y()};

    if (board.IsColliding(point_0.x, point_0.y) ||
        board.IsColliding(point_1.x, point_1.y) ||
        board.IsColliding(point_2.x, point_2.y) ||
        board.IsColliding(point_3.x, point_3.y))
    {
        return;
    }

    m_Blocks.at(0).SetPosition(point_0.x, point_0.y);
    m_Blocks.at(1).SetPosition(point_1.x, point_1.y);
    m_Blocks.at(2).SetPosition(point_2.x, point_2.y);
    m_Blocks.at(3).SetPosition(point_3.x, point_3.y);
}

// Assuming rotation is always Zero
std::array<Block, 4> Tetromino::GetInitialBlocks(TetrominoType type)
{
    std::array<Block, 4> blocks;

    switch (type)
    {
    case TetrominoType::I:
        blocks[0] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        blocks[1] = Block(m_BlockSize * 4, m_BlockSize * 2, m_BlockSize);
        blocks[2] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 7, m_BlockSize * 2, m_BlockSize);
        break;
    case TetrominoType::O:
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize, m_BlockSize);
        blocks[1] = Block(m_BlockSize * 6, m_BlockSize, m_BlockSize);
        blocks[2] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        break;
    case TetrominoType::J:
        blocks[2] = Block(m_BlockSize * 4, m_BlockSize, m_BlockSize);
        blocks[1] = Block(m_BlockSize * 4, m_BlockSize * 2, m_BlockSize);
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        break;
    case TetrominoType::L:
        blocks[2] = Block(m_BlockSize * 6, m_BlockSize, m_BlockSize);
        blocks[1] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 4, m_BlockSize * 2, m_BlockSize);
        break;
    case TetrominoType::T:
        blocks[1] = Block(m_BlockSize * 5, m_BlockSize, m_BlockSize);
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[2] = Block(m_BlockSize * 4, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        break;
    case TetrominoType::S:
        blocks[1] = Block(m_BlockSize * 5, m_BlockSize, m_BlockSize);
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[2] = Block(m_BlockSize * 4, m_BlockSize * 2, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 6, m_BlockSize, m_BlockSize);
        break;
    case TetrominoType::Z:
        blocks[1] = Block(m_BlockSize * 5, m_BlockSize, m_BlockSize);
        blocks[0] = Block(m_BlockSize * 5, m_BlockSize * 2, m_BlockSize);
        blocks[2] = Block(m_BlockSize * 4, m_BlockSize, m_BlockSize);
        blocks[3] = Block(m_BlockSize * 6, m_BlockSize * 2, m_BlockSize);
        break;
    }

    for (Block &block : blocks)
    {
        block.SetColor(m_Color.r, m_Color.g, m_Color.b);
    }

    return blocks;
}
