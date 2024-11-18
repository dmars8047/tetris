#include <iostream>

#include "constants.hpp"
#include "tetromino.hpp"
#include "block.hpp"

Tetromino::Tetromino(TetrominoType type)
{
    m_type = type;
    m_rotation = TetrominoRotation::Zero;
    m_Blocks = GetInitialBlocks(m_type);
}

void Tetromino::Render(SDL_Renderer *renderer)
{
    SDL_Rect rect_0 = m_Blocks.at(0).GetRenderRect();
    SDL_Rect rect_1 = m_Blocks.at(1).GetRenderRect();
    SDL_Rect rect_2 = m_Blocks.at(2).GetRenderRect();
    SDL_Rect rect_3 = m_Blocks.at(3).GetRenderRect();

    SDL_Rect rects[4] = {rect_0, rect_1, rect_2, rect_3};

    SDL_RenderFillRects(renderer, rects, 4);
}

void Tetromino::Rotate()
{
    // Block 0 is always the keystone block
    int keystonePosition_X = m_Blocks.at(0).GetPosition_X();
    int keystonePosition_Y = m_Blocks.at(0).GetPosition_Y();

    switch (m_type)
    {
    case TetrominoType::I:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y - (BLOCK_SIZE));
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y + (BLOCK_SIZE));
            m_Blocks.at(3).SetPosition(keystonePosition_X, keystonePosition_Y + (BLOCK_SIZE * 2));
            break;
        case TetrominoRotation::Ninety:
            m_Blocks.at(0).SetPosition(keystonePosition_X - (BLOCK_SIZE), keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X - (BLOCK_SIZE * 2), keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(3).SetPosition(keystonePosition_X + (BLOCK_SIZE), keystonePosition_Y);
            break;
        case TetrominoRotation::OneEighty:
            m_Blocks.at(3).SetPosition(keystonePosition_X, keystonePosition_Y - (BLOCK_SIZE * 2));
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y - (BLOCK_SIZE));
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y + (BLOCK_SIZE));
            break;
        case TetrominoRotation::TwoSeventy:
            m_Blocks.at(1).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(0).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(3).SetPosition(keystonePosition_X + (BLOCK_SIZE * 2), keystonePosition_Y);
            break;
        }

        break;
    case TetrominoType::O:
        break;
    case TetrominoType::J:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            break;
        case TetrominoRotation::Ninety:
            break;
        case TetrominoRotation::OneEighty:
            break;
        case TetrominoRotation::TwoSeventy:
            break;
        }
        break;
    case TetrominoType::L:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            break;
        case TetrominoRotation::Ninety:
            break;
        case TetrominoRotation::OneEighty:
            break;
        case TetrominoRotation::TwoSeventy:
            break;
        }
        break;
    case TetrominoType::T:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y - BLOCK_SIZE);
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            break;
        case TetrominoRotation::Ninety:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(2).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(3).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            break;
        case TetrominoRotation::OneEighty:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y - BLOCK_SIZE);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            break;
        case TetrominoRotation::TwoSeventy:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X, keystonePosition_Y - BLOCK_SIZE);
            m_Blocks.at(2).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(3).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            break;
        }
        break;
    case TetrominoType::S:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            break;
        case TetrominoRotation::Ninety:
            break;
        case TetrominoRotation::OneEighty:
            break;
        case TetrominoRotation::TwoSeventy:
            break;
        }
        break;
    case TetrominoType::Z:
        switch (m_rotation)
        {
        case TetrominoRotation::Zero:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y - BLOCK_SIZE);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            break;
        case TetrominoRotation::Ninety:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y + BLOCK_SIZE);
            break;
        case TetrominoRotation::OneEighty:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y + BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X, keystonePosition_Y - BLOCK_SIZE);
            break;
        case TetrominoRotation::TwoSeventy:
            m_Blocks.at(0).SetPosition(keystonePosition_X, keystonePosition_Y);
            m_Blocks.at(1).SetPosition(keystonePosition_X + BLOCK_SIZE, keystonePosition_Y);
            m_Blocks.at(2).SetPosition(keystonePosition_X - BLOCK_SIZE, keystonePosition_Y - BLOCK_SIZE);
            m_Blocks.at(3).SetPosition(keystonePosition_X, keystonePosition_Y - BLOCK_SIZE);
            break;
        }
        break;
    }

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

void Tetromino::MoveDown()
{
    for (int i = 0; i < 4; i++)
    {
        m_Blocks.at(i).MoveDown();
    }
}

void Tetromino::MoveUp()
{
    for (int i = 0; i < 4; i++)
    {
        m_Blocks.at(i).MoveUp();
    }
}

void Tetromino::MoveRight()
{
    for (int i = 0; i < 4; i++)
    {
        m_Blocks.at(i).MoveRight();
    }
}

void Tetromino::MoveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        m_Blocks.at(i).MoveLeft();
    }
}

// Assuming rotation is always Zero
std::array<Block, 4> Tetromino::GetInitialBlocks(TetrominoType type)
{
    std::array<Block, 4> blocks;

    switch (type)
    {
    case TetrominoType::I:
        blocks[0] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 2);
        blocks[1] = Block(BLOCK_SIZE * 4, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[3] = Block(BLOCK_SIZE * 7, BLOCK_SIZE * 2);
        break;
    case TetrominoType::O:
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[1] = Block(BLOCK_SIZE * 6, BLOCK_SIZE);
        blocks[2] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[3] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 2);
        break;
    case TetrominoType::J:
        blocks[0] = Block(BLOCK_SIZE * 6, BLOCK_SIZE);
        blocks[1] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 3);
        blocks[3] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 3);
        break;
    case TetrominoType::L:
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[1] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 3);
        blocks[3] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 3);
        break;
    case TetrominoType::T:
        blocks[1] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 4, BLOCK_SIZE * 2);
        blocks[3] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 2);
        break;
    case TetrominoType::S:
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[1] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 4, BLOCK_SIZE * 2);
        blocks[3] = Block(BLOCK_SIZE * 6, BLOCK_SIZE);
        break;
    case TetrominoType::Z:
        blocks[1] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 4, BLOCK_SIZE);
        blocks[3] = Block(BLOCK_SIZE * 6, BLOCK_SIZE * 2);
        break;
    default:
        blocks[0] = Block(BLOCK_SIZE * 5, BLOCK_SIZE);
        blocks[1] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
        blocks[2] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 3);
        blocks[3] = Block(BLOCK_SIZE * 5, BLOCK_SIZE * 4);
        break;
    }

    return blocks;
}
