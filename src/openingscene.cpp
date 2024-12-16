#include <iostream>

#include "openingscene.hpp"
#include "constants.hpp"

OpeningScene::OpeningScene(AssetManager &assetManager, int blockSize, int viewportWidth, int viewportHeight)
{
    m_BlockSize = blockSize;
    m_ViewportWidth = viewportWidth;
    m_ViewportHeight = viewportHeight;

    const std::string enterMessageTextureID = "font-texture-opening-press-enter";
    assetManager.LoadFontTexture(enterMessageTextureID, "-- Press Enter -- ", COLOR_WHITE);
    m_PressEnterTexture = assetManager.GetFontTexture(enterMessageTextureID);

    m_Ready = false;

    int logoStartX = (viewportWidth / 2) - (m_BlockSize * 8);
    int logoStartY = (viewportHeight / 2) - (m_BlockSize * 8);
    int logoEndX = (viewportWidth / 2) + (m_BlockSize * 8);
    int logoEndY = (viewportHeight / 2) + (m_BlockSize * 2);

    m_LogoBorderPoints[0] = SDL_Point{x : logoStartX, y : logoStartY};
    m_LogoBorderPoints[1] = SDL_Point{x : logoStartX, y : logoEndY - (m_BlockSize * 4)};
    m_LogoBorderPoints[2] = SDL_Point{x : logoStartX + (m_BlockSize * 4) + (m_BlockSize / 2), y : logoEndY - (m_BlockSize * 4)};
    m_LogoBorderPoints[3] = SDL_Point{x : logoStartX + (m_BlockSize * 4) + (m_BlockSize / 2), y : logoEndY};
    m_LogoBorderPoints[4] = SDL_Point{x : logoEndX - (m_BlockSize * 4 + (m_BlockSize / 2)), y : logoEndY};
    m_LogoBorderPoints[5] = SDL_Point{x : logoEndX - (m_BlockSize * 4 + (m_BlockSize / 2)), y : logoEndY - (m_BlockSize * 4)};
    m_LogoBorderPoints[6] = SDL_Point{x : logoEndX, y : logoEndY - (m_BlockSize * 4)};
    m_LogoBorderPoints[7] = SDL_Point{x : logoEndX, y : logoStartY};
    m_LogoBorderPoints[8] = SDL_Point{x : logoStartX, y : logoStartY};

    // T
    SDL_Rect t_rect_1 = {logoStartX + m_BlockSize, logoStartY + m_BlockSize, m_BlockSize * 2 + (m_BlockSize / 2), m_BlockSize};

    SDL_Rect t_rect_2 = {
        t_rect_1.x + (t_rect_1.w - m_BlockSize) / 2, // Center t_rect_2 horizontally within t_rect_1
        t_rect_1.y + m_BlockSize,                    // Directly below t_rect_1
        m_BlockSize,                                 // Width of t_rect_2
        m_BlockSize * 3                              // Height of t_rect_2
    };

    m_t1_Rects[0] = t_rect_1;
    m_t1_Rects[1] = t_rect_2;

    // E
    SDL_Rect e_rect_1 = {t_rect_1.x + t_rect_1.w + 4, logoStartY + m_BlockSize, m_BlockSize * 2 + (m_BlockSize / 2), m_BlockSize};
    SDL_Rect e_rect_2 = {e_rect_1.x, e_rect_1.y + m_BlockSize, m_BlockSize, m_BlockSize * 3};
    SDL_Rect e_rect_3 = {e_rect_1.x + m_BlockSize, e_rect_1.y + m_BlockSize + (m_BlockSize / 2), m_BlockSize, m_BlockSize};
    SDL_Rect e_rect_4 = {e_rect_1.x + m_BlockSize, e_rect_1.y + (m_BlockSize * 3), m_BlockSize + (m_BlockSize / 2), m_BlockSize};

    m_e_Rects[0] = e_rect_1;
    m_e_Rects[1] = e_rect_2;
    m_e_Rects[2] = e_rect_3;
    m_e_Rects[3] = e_rect_4;

    // T
    SDL_Rect t2_rect_1 = {e_rect_1.x + e_rect_1.w + 4, logoStartY + m_BlockSize, m_BlockSize * 2 + (m_BlockSize / 2), m_BlockSize};

    // Now define the second rectangle
    SDL_Rect t2_rect_2 = {
        t2_rect_1.x + (t2_rect_1.w - m_BlockSize) / 2, // Center t_rect_2 horizontally within t_rect_1
        t2_rect_1.y + m_BlockSize,                     // Directly below t_rect_1
        m_BlockSize,                                   // Width of t_rect_2
        m_BlockSize * 3                                // Height of t_rect_2
    };

    // R
    m_t2_Rects[0] = t2_rect_1;
    m_t2_Rects[1] = t2_rect_2;

    SDL_Rect r_rect_1 = {t2_rect_1.x + t2_rect_1.w + 4, t_rect_1.y, m_BlockSize * 2 + (m_BlockSize / 2), m_BlockSize};
    SDL_Rect r_rect_2 = {r_rect_1.x, r_rect_1.y + m_BlockSize, m_BlockSize, m_BlockSize * 3};
    SDL_Rect r_rect_3 = {r_rect_2.x + m_BlockSize + (m_BlockSize / 2), r_rect_1.y + m_BlockSize, m_BlockSize, m_BlockSize};
    SDL_Rect r_rect_4 = {r_rect_2.x + m_BlockSize + (m_BlockSize / 2), r_rect_3.y + r_rect_3.h + (m_BlockSize / 2), m_BlockSize, m_BlockSize + (m_BlockSize / 2)};
    SDL_Rect r_rect_5 = {r_rect_2.x + m_BlockSize, r_rect_2.y + m_BlockSize, m_BlockSize, m_BlockSize};

    m_r_Rects[0] = r_rect_1;
    m_r_Rects[1] = r_rect_2;
    m_r_Rects[2] = r_rect_3;
    m_r_Rects[3] = r_rect_4;
    m_r_Rects[4] = r_rect_5;

    // I
    m_i_Rect = {r_rect_1.x + r_rect_1.w + 6, t_rect_1.y, m_BlockSize, m_BlockSize * 4};

    // S
    int sWidth = (logoEndX - m_BlockSize) - (m_i_Rect.x + m_i_Rect.w + 6);
    SDL_Rect s_rect_1 = {m_i_Rect.x + m_i_Rect.w + 6, t_rect_1.y, sWidth, m_BlockSize};
    SDL_Rect s_rect_2 = {s_rect_1.x, s_rect_1.y + m_BlockSize, sWidth - m_BlockSize, m_BlockSize + (m_BlockSize / 2)};
    SDL_Rect s_rect_3 = {logoEndX - m_BlockSize - m_BlockSize, s_rect_1.y + m_BlockSize * 2, m_BlockSize, m_BlockSize};
    SDL_Rect s_rect_4 = {s_rect_1.x, s_rect_1.y + m_BlockSize * 3, sWidth, m_BlockSize};
    SDL_Rect s_rects[] = {s_rect_1, s_rect_2, s_rect_3, s_rect_4};

    m_s_Rects[0] = s_rect_1;
    m_s_Rects[1] = s_rect_2;
    m_s_Rects[2] = s_rect_3;
    m_s_Rects[3] = s_rect_4;

    // Enter prompt
    const std::string enterTextureId = "opening-press-enter";

    assetManager.LoadFontTexture(enterTextureId, "-- Press Enter --", COLOR_WHITE);
    m_EnterTexture = assetManager.GetFontTexture(enterTextureId);
}

void OpeningScene::ParseInput(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDL_KeyCode::SDLK_RETURN:
            m_Ready = true;
            break;
        }
    }
}

void OpeningScene::Render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);

    // Draw the board
    SDL_RenderDrawLines(renderer, m_LogoBorderPoints, 9);

    // T
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_Z.r, COLOR_TETROMINO_Z.g, COLOR_TETROMINO_Z.b, COLOR_TETROMINO_Z.a);
    SDL_RenderFillRects(renderer, m_t1_Rects, 2);

    // E
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_L.r, COLOR_TETROMINO_L.g, COLOR_TETROMINO_L.b, COLOR_TETROMINO_L.a);
    SDL_RenderFillRects(renderer, m_e_Rects, 4);

    // T
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_O.r, COLOR_TETROMINO_O.g, COLOR_TETROMINO_O.b, COLOR_TETROMINO_O.a);
    SDL_RenderFillRects(renderer, m_t2_Rects, 2);

    // R
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_T.r, COLOR_TETROMINO_T.g, COLOR_TETROMINO_T.b, COLOR_TETROMINO_T.a);
    SDL_RenderFillRects(renderer, m_r_Rects, 5);

    // I
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_S.r, COLOR_TETROMINO_S.g, COLOR_TETROMINO_S.b, COLOR_TETROMINO_S.a);
    SDL_RenderFillRect(renderer, &m_i_Rect);

    // S
    SDL_SetRenderDrawColor(renderer, COLOR_TETROMINO_I.r, COLOR_TETROMINO_I.g, COLOR_TETROMINO_I.b, COLOR_TETROMINO_I.a);
    SDL_RenderFillRects(renderer, m_s_Rects, 4);

    const float titleScaling = .75;
    const int scaledEnterTextureWidth = static_cast<int>(m_EnterTexture->GetWidth() * titleScaling);
    const int scaledEnterTextureHeight = static_cast<int>(m_EnterTexture->GetHeight() * titleScaling);

    int startX = m_ViewportWidth / 2 - (scaledEnterTextureWidth / 2);
    int startY = m_ViewportWidth / 2 + scaledEnterTextureHeight + (m_BlockSize * 4);

    SDL_Rect enterRect = SDL_Rect{x : startX, y : startY, w : scaledEnterTextureWidth, h : scaledEnterTextureHeight};

    // Render to screen
    SDL_RenderCopy(renderer, m_EnterTexture->GetTexture(), NULL, &enterRect);
}

bool OpeningScene::IsReady()
{
    if (m_Ready)
    {
        std::cout << "PLAYER READY!\n";
    }

    return m_Ready;
}
