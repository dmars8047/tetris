#ifndef GAMEOVERSCENE_HPP
#define GAMEOVERSCENE_HPP

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "numericdisplay.hpp"

class GameOverScene
{
public:
    GameOverScene(AssetManager &assetManager, int blockSize);
    void SetNumericValues(int points, int level, int cleared);
    void ParseInput(SDL_Event &e);
    void Render(SDL_Renderer *renderer, int viewportWidth) const;
    bool RestartRequested() const;
    void AcknowledgeRestartRequest();

private:
    bool m_Restart;
    int m_BlockSize;
    NumericDisplay m_LinesDisplay;
    NumericDisplay m_PointsDisplay;
    NumericDisplay m_LevelDisplay;
    Texture *m_GameOverTexture;
    
};

#endif