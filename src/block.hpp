#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>

#if __APPLE__
#include <SDL.h>
#elif
#include <SDL2/SDL.h>
#endif

class Block
{
public:
    Block();
    Block(int x, int y);
    ~Block();
    SDL_Rect GetRenderRect() const;
    void Render(SDL_Renderer *g_Renderer) const;
    void SetPosition(int x, int y);
    int GetPosition_X() const;
    int GetPosition_Y() const;

private:
    int m_x;
    int m_y;
};

#endif