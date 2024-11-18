#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

class Block {
    public:
        Block();
        Block(int x, int y);
        ~Block();
        SDL_Rect GetRenderRect();
        void Render(SDL_Renderer *g_Renderer);
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void SetPosition(int x, int y);
        int GetPosition_X();
        int GetPosition_Y();
    private:
        int m_x;
        int m_y;
};

#endif