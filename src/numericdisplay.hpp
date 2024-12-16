#ifndef NUMERICDISPLAY_HPP
#define NUMERICDISPLAY_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "assetmanager.hpp"
#include "texture.hpp"

class NumericDisplay
{
private:
    int m_startX;
    int m_endX;
    int m_startY;
    int m_endY;
    int m_value;
    Texture *m_Texture_0;
    Texture *m_Texture_1;
    Texture *m_Texture_2;
    Texture *m_Texture_3;
    Texture *m_Texture_4;
    Texture *m_Texture_5;
    Texture *m_Texture_6;
    Texture *m_Texture_7;
    Texture *m_Texture_8;
    Texture *m_Texture_9;
    Texture *m_Font_Texture;
    Texture *GetTextureForDigit(int digit) const;

public:
    NumericDisplay();
    NumericDisplay(
        AssetManager &assetManager,
        const std::string &titleTextureId,
        const std::string &title,
        float startX,
        float startY,
        int blockSize);
    void Render(SDL_Renderer *renderer) const;
    void SetValue(int num);
};

#endif
