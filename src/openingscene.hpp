#ifndef OPENINGSCENE_HPP
#define OPENINGSCENE_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "assetmanager.hpp"

class OpeningScene
{
public:
    OpeningScene(AssetManager &assetManager, int blockSize, int viewportWidth, int viewportHeight);
    void ParseInput(SDL_Event &e);
    void Render(SDL_Renderer *renderer) const;
    bool IsReady();

private:
    bool m_Ready;
    int m_BlockSize;
    int m_ViewportWidth;
    int m_ViewportHeight;
    Texture *m_LogoTexture;
    Texture *m_PressEnterTexture;
    SDL_Point m_LogoBorderPoints[9];
    SDL_Rect m_t1_Rects[2];
    SDL_Rect m_e_Rects[4];
    SDL_Rect m_t2_Rects[2];
    SDL_Rect m_r_Rects[5];
    SDL_Rect m_i_Rect;
    SDL_Rect m_s_Rects[4];
    Texture *m_EnterTexture;
};

#endif