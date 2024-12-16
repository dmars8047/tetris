#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Texture
{
public:
    Texture(SDL_Texture *texture, int w, int h);
    ~Texture();
    int GetWidth() const;
    int GetHeight() const;
    SDL_Texture *GetTexture() const;

private:
    int m_w;
    int m_h;
    SDL_Texture *m_Texture;
};

#endif