#include <string>

#include "numericdisplay.hpp"
#include "constants.hpp"

NumericDisplay::NumericDisplay()
{
    m_Texture_0 = nullptr;
    m_Texture_1 = nullptr;
    m_Texture_2 = nullptr;
    m_Texture_3 = nullptr;
    m_Texture_4 = nullptr;
    m_Texture_5 = nullptr;
    m_Texture_6 = nullptr;
    m_Texture_7 = nullptr;
    m_Texture_8 = nullptr;
    m_Texture_9 = nullptr;
    m_Font_Texture = nullptr;
}

NumericDisplay::NumericDisplay(
    AssetManager &assetManager,
    const std::string &titleTextureId,
    const std::string &title,
    float startX,
    float startY,
    int blockSize)
{
    m_startX = startX * blockSize;
    m_endX = m_startX + (blockSize * 6);
    m_startY = blockSize * startY;
    m_endY = m_startY + (blockSize * 2);
    m_value = 0;
    m_Texture_0 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_0);
    m_Texture_1 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_1);
    m_Texture_2 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_2);
    m_Texture_3 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_3);
    m_Texture_4 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_4);
    m_Texture_5 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_5);
    m_Texture_6 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_6);
    m_Texture_7 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_7);
    m_Texture_8 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_8);
    m_Texture_9 = assetManager.GetFontTexture(SHARED_FONT_TEXTURE_9);

    assetManager.LoadFontTexture(titleTextureId, title, COLOR_WHITE);
    m_Font_Texture = assetManager.GetFontTexture(titleTextureId);
}

void NumericDisplay::Render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Point borderPoints[] = {
        SDL_Point{x : m_startX, y : m_startY},
        SDL_Point{x : m_startX, y : m_endY},
        SDL_Point{x : m_endX, y : m_endY},
        SDL_Point{x : m_endX, y : m_startY},
        SDL_Point{x : m_startX, y : m_startY}};

    // Draw the board
    SDL_RenderDrawLines(renderer, borderPoints, 5);

    const double titleScaling = .75;
    const int scaledTitleWidth = static_cast<int>(m_Font_Texture->GetWidth() * titleScaling);
    const int scaledTitleHeight = static_cast<int>(m_Font_Texture->GetHeight() * titleScaling);

    int startX = m_startX + ((m_endX - m_startX) - (scaledTitleWidth)) / 2;

    SDL_Rect titleRect = SDL_Rect{startX, m_startY - m_Font_Texture->GetHeight() - 2, scaledTitleWidth, scaledTitleHeight};

    // Render to screen
    SDL_RenderCopy(renderer, m_Font_Texture->GetTexture(), NULL, &titleRect);

    // Convert m_value to string
    std::string linesStr = std::to_string(m_value);

    // Calculate the total width of the number to center it
    int totalWidth = 0;
    int totalHeight = 0;
    for (char digit : linesStr)
    {
        int digitValue = digit - '0';
        totalWidth += GetTextureForDigit(digitValue)->GetWidth();
        totalHeight = GetTextureForDigit(digitValue)->GetHeight();
    }

    // Starting X position to center the number in the box
    startX = m_startX + ((m_endX - m_startX) - totalWidth) / 2;

    int startY = m_startY + ((m_endY - m_startY) - totalHeight) / 2;

    // Render each digit
    int currentX = startX;
    for (char digit : linesStr)
    {
        int digitValue = digit - '0';
        Texture *digitTexture = GetTextureForDigit(digitValue);

        SDL_Rect digitRect = {currentX, startY, digitTexture->GetWidth(), digitTexture->GetHeight()};
        SDL_RenderCopy(renderer, digitTexture->GetTexture(), NULL, &digitRect);

        currentX += digitTexture->GetWidth(); // Move to the next digit position
    }
}

void NumericDisplay::SetValue(int num)
{
    m_value = num;
}

Texture *NumericDisplay::GetTextureForDigit(int digit) const
{
    switch (digit)
    {
    case 0:
        return m_Texture_0;
    case 1:
        return m_Texture_1;
    case 2:
        return m_Texture_2;
    case 3:
        return m_Texture_3;
    case 4:
        return m_Texture_4;
    case 5:
        return m_Texture_5;
    case 6:
        return m_Texture_6;
    case 7:
        return m_Texture_7;
    case 8:
        return m_Texture_8;
    case 9:
        return m_Texture_9;
    default:
        return nullptr;
    }
}