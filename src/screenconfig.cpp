#include <iostream>

#include "screenconfig.hpp"
#include "constants.hpp"

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

ScreenConfig::ScreenConfig()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    int scalingValue = 1;

    if (WINDOW_HEIGHT > displayMode.h)
    {
        scalingValue = 2;
    }

    std::cout << "Scaling Value: " << scalingValue << "\n";

    m_BlockSize = BLOCK_SIZE / scalingValue;
    m_ViewPortHeight = WINDOW_HEIGHT / scalingValue;
    m_ViewPortWidth = WINDOW_WIDTH / scalingValue;
}

int ScreenConfig::GetBlockSize() const
{
    return m_BlockSize;
}

int ScreenConfig::GetViewPortHeight() const
{
    return m_ViewPortHeight;
}

int ScreenConfig::GetViewPortWidth() const
{
    return m_ViewPortWidth;
}
