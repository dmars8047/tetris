#ifndef PREVIEW_HPP
#define PREVIEW_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "constants.hpp"

class Preview {
    public:
        Preview(TetrominoType type, int blockSize);
        void Render(SDL_Renderer *renderer) const;
        TetrominoType GetType() const;
    private:
        TetrominoType m_type;
        int m_startX;
        int m_endX;
        int m_startY;
        int m_endY;
        SDL_Color m_Color;
        SDL_Rect m_Rects[4];
};

#endif