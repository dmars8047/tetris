#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <map>
#include <string>

#if __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "texture.hpp"


class AssetManager
{
private:
    SDL_Renderer *m_Renderer;
    std::map<std::string, Texture *> m_Textures;
    std::map<std::string, Texture *> m_FontTextures;
    std::map<std::string, Mix_Chunk *> m_SoundEffects;
    std::map<std::string, Mix_Music *> m_Music;
    std::map<std::string, TTF_Font *> m_Fonts;
    static void DestroyTexture(Texture *texture) { delete texture; };
    template <typename T, typename F>
    void clearAssets(std::map<std::string, T *> &assets, F cleanupFunction, const std::string &type);

public:
    AssetManager(SDL_Renderer *renderer);
    ~AssetManager();

    // Textures
    Texture *GetTexture(const std::string &identifier) const;
    bool LoadTexture(std::string textureId, std::string textureSource);

    Texture *GetFontTexture(const std::string &identifier) const;
    bool LoadFontTexture(std::string textureId, std::string content, SDL_Color color);

    // Fonts
    TTF_Font *GetFont(const std::string &fontId) const;
    bool LoadFont(const std::string &identifier, const std::string &source, int fontSize);

    // Sound Effects
    Mix_Chunk *GetSoundEffect(const std::string &identifier) const;
    bool LoadSoundEffect(const std::string &identifier, const std::string &source);

    // Music
    Mix_Music *GetMusic(const std::string &identifier) const;
    bool LoadMusic(const std::string &identifier, const std::string &source);
};

#endif