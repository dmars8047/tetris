#include "texture.hpp"

Texture::Texture(SDL_Texture *texture, int w, int h)
{
    m_Texture = texture;
    m_w = w;
    m_h = h;
};

Texture::~Texture()
{
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
}

int Texture::GetWidth() const
{
    return m_w;
}

int Texture::GetHeight() const
{
    return m_h;
}

SDL_Texture *Texture::GetTexture() const
{
    return m_Texture;
}
