#include "gameoverscene.hpp"
#include "constants.hpp"

GameOverScene::GameOverScene(AssetManager &assetManager, int blockSize)
{
    m_LinesDisplay = NumericDisplay(assetManager, "line-display-title", "Lines", 6.5, 7, blockSize);
    m_PointsDisplay = NumericDisplay(assetManager, "points-display-title", "Points", 6.5, 11, blockSize);
    m_LevelDisplay = NumericDisplay(assetManager, "level-display-title", "Level", 6.5, 15, blockSize);
    m_Restart = false;
    m_BlockSize = blockSize;

    assetManager.LoadFontTexture("game-over", "Game Over", COLOR_TETROMINO_Z);
    m_GameOverTexture = assetManager.GetFontTexture("game-over");
}

void GameOverScene::SetNumericValues(int points, int level, int cleared)
{
    m_PointsDisplay.SetValue(points);
    m_LevelDisplay.SetValue(level);
    m_LinesDisplay.SetValue(cleared);
}

void GameOverScene::ParseInput(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDL_KeyCode::SDLK_RETURN:
            m_Restart = true;
            break;
        }
    }
}

void GameOverScene::Render(SDL_Renderer *renderer, int viewportWidth) const
{
    int startX = viewportWidth / 2 - (m_GameOverTexture->GetWidth() / 2);
    int startY = m_BlockSize * 3;

    SDL_Rect gameOverRect;
    gameOverRect.x = startX;
    gameOverRect.y = startY;
    gameOverRect.w = m_GameOverTexture->GetWidth();
    gameOverRect.h = m_GameOverTexture->GetHeight();

    SDL_RenderCopy(renderer, m_GameOverTexture->GetTexture(), NULL, &gameOverRect);

    m_LinesDisplay.Render(renderer);
    m_PointsDisplay.Render(renderer);
    m_LevelDisplay.Render(renderer);
}

bool GameOverScene::RestartRequested() const
{
    return m_Restart;
}

void GameOverScene::AcknowledgeRestartRequest()
{
    m_Restart = false;
}
