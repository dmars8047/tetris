#include <iostream>

#include "assetmanager.hpp"
#include "constants.hpp"

AssetManager::AssetManager(SDL_Renderer *renderer)
{
    m_Renderer = renderer;
};

AssetManager::~AssetManager()
{
    clearAssets(m_FontTextures, DestroyTexture, "font-texture");
    clearAssets(m_Textures, DestroyTexture, "texture");
    clearAssets(m_Fonts, TTF_CloseFont, "font");
    clearAssets(m_SoundEffects, Mix_FreeChunk, "sound effect");
    clearAssets(m_Music, Mix_FreeMusic, "music");
    m_Renderer = nullptr;
}

template <typename T, typename F>
void AssetManager::clearAssets(std::map<std::string, T *> &assets, F cleanupFunction, const std::string &type)
{
    for (auto &[key, resource] : assets)
    {
        std::cout << "Disposing of " << type << ": " << key << std::endl;
        cleanupFunction(resource);
        resource = nullptr;
    }
    assets.clear();
}

// ********
// Textures
// ********

// Gets a texture by its ID.
Texture *AssetManager::GetTexture(const std::string &textureId) const
{
    return m_Textures.at(textureId);
}

bool AssetManager::LoadTexture(std::string textureId, std::string textureSource)
{
    try
    {
        if (m_Textures.count(textureId))
        {
            return true;
        }

        SDL_Surface *loadedSurface = IMG_Load(textureSource.c_str());

        // The final texture
        SDL_Texture *sdlTexture = NULL;

        // Load image at specified path
        if (loadedSurface == NULL)
        {
            std::cerr << "Unable to load image " << textureSource << " SDL_image Error: " << IMG_GetError() << std::endl;
            return false;
        }
        else
        {
            // Color key image
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

            // Create texture from surface pixels
            sdlTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);

            if (sdlTexture == NULL)
            {
                std::cerr << "Unable to create texture from " << textureSource << " SDL Error: " << SDL_GetError() << std::endl;
                return false;
            }

            std::cout << "Loaded texture: " << textureId << std::endl;

            Texture *texture = new Texture(sdlTexture, loadedSurface->w, loadedSurface->h);

            // Get rid of old loaded surface
            SDL_FreeSurface(loadedSurface);

            m_Textures.insert(std::pair<std::string, Texture *>(textureId, texture));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

Texture *AssetManager::GetFontTexture(const std::string &identifier) const
{
    return m_FontTextures.at(identifier);
}

// Loads a font texture.
bool AssetManager::LoadFontTexture(std::string textureId, std::string content, SDL_Color color)
{
    try
    {
        if (m_Textures.count(textureId))
        {
            return true;
        }

        // Render text surface
        SDL_Surface *textSurface = TTF_RenderText_Solid(GetFont(MAIN_FONT_ID), content.c_str(), color);

        if (textSurface == NULL)
        {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return false;
        }

        // The final texture
        SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

        if (sdlTexture == NULL)
        {
            std::cerr << "Unable to create font texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        std::cout << "Loaded texture: " << textureId << std::endl;

        Texture *texture = new Texture(sdlTexture, textSurface->w, textSurface->h);

        SDL_FreeSurface(textSurface);

        m_FontTextures.insert(std::pair<std::string, Texture *>(textureId, texture));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

// ********
// Fonts
// ********
TTF_Font *AssetManager::GetFont(const std::string &fontId) const
{
    return m_Fonts.at(fontId);
}

bool AssetManager::LoadFont(const std::string &identifier, const std::string &source, int fontSize)
{
    try
    {
        if (m_Fonts.count(identifier))
        {
            return true;
        }

        TTF_Font *font = TTF_OpenFont(source.c_str(), fontSize);

        if (font == NULL)
        {
            std::cerr << "Failed to load font: " << source << ". See error: " << TTF_GetError() << std::endl;
            return false;
        }

        m_Fonts.insert(std::pair<std::string, TTF_Font *>(identifier, font));

        std::cout << "Loaded Font: " << identifier << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

// ********
// SFX
// ********
Mix_Chunk *AssetManager::GetSoundEffect(const std::string &identifier) const
{
    return m_SoundEffects.at(identifier);
}

bool AssetManager::LoadSoundEffect(const std::string &identifier, const std::string &source)
{
    try
    {
        if (m_SoundEffects.count(identifier))
        {
            Mix_FreeChunk(m_SoundEffects.at(identifier));
            m_SoundEffects.erase(identifier);
        }

        Mix_Chunk *sfxAsset = Mix_LoadWAV(source.c_str());

        if (sfxAsset == NULL)
        {
            std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        m_SoundEffects.insert(std::pair<std::string, Mix_Chunk *>(identifier, sfxAsset));

        std::cout << "Sound Effect asset: '" << identifier << "' has been loaded." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

// ********
// Music
// ********
Mix_Music *AssetManager::GetMusic(const std::string &identifier) const
{
    return m_Music.at(identifier);
}

bool AssetManager::LoadMusic(const std::string &identifier, const std::string &source)
{
    try
    {
        if (m_Music.count(identifier))
        {
            return true;
        }

        Mix_Music *musicAsset = Mix_LoadMUS(source.c_str());

        if (musicAsset == NULL)
        {
            std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        m_Music.insert(std::pair<std::string, Mix_Music *>(identifier, musicAsset));

        std::cout << "Music asset: '" << identifier << "' has been loaded." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}