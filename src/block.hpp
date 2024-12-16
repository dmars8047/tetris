#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Block
{
public:
    Block();
    Block(int x, int y, int size);
    SDL_Rect GetRenderRect() const;
    void Render(SDL_Renderer *renderer) const;
    void SetPosition(int x, int y);
    void SetColor(Uint8 r, Uint8 g, Uint8 b);
    int GetPosition_X() const;
    int GetPosition_Y() const;

private:
    int m_x;
    int m_y;
    int m_size;
    int m_r;
    int m_g;
    int m_b;
};

#endif