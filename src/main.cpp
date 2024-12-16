#include <iostream>
#include <random>

#if __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include "constants.hpp"
#include "assetmanager.hpp"
#include "gameplayscene.hpp"
#include "openingscene.hpp"
#include "gameoverscene.hpp"
#include "screenconfig.hpp"

SDL_Window *g_MainWindow = NULL;
SDL_Renderer *g_Renderer = NULL;
SDL_GameController *g_GameController = NULL;
AssetManager *g_AssetManager = NULL;

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
    {
        std::cout << "Warning: Best texture filtering not enabled!" << std::endl;
    }
    else if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    // Check for joysticks
    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: No joysticks connected!\n");
    }
    else
    {
        // Load joystick
        g_GameController = SDL_GameControllerOpen(0);

        if (g_GameController == NULL)
        {
            printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
        }
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    int scalingValue = 1;

    if (WINDOW_HEIGHT > displayMode.h)
    {
        scalingValue = 2;
    }

    g_MainWindow = SDL_CreateWindow(
        APP_NAME.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH / scalingValue,
        WINDOW_HEIGHT / scalingValue,
        SDL_WINDOW_SHOWN);

    if (g_MainWindow == NULL)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create vsynced renderer for window
    g_Renderer = SDL_CreateRenderer(g_MainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (g_Renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(g_Renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);

    // Initialize PNG loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Initialize TTF
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    return true;
}

void destroy_SDL()
{
    // Close game controller
    if (g_GameController != NULL)
    {
        SDL_GameControllerClose(g_GameController);
        g_GameController = NULL;
    }

    // Destroy window
    if (g_Renderer != NULL)
    {
        SDL_DestroyRenderer(g_Renderer);
    }

    if (g_MainWindow != NULL)
    {
        SDL_DestroyWindow(g_MainWindow);
    }

    // Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool loadSharedAssets(const ScreenConfig &screenConfig)
{
    g_AssetManager = new AssetManager(g_Renderer);

    // Fonts
    g_AssetManager->LoadFont(MAIN_FONT_ID, "./assets/fonts/PressStart2P-Regular.ttf", screenConfig.GetBlockSize());

    // Scoreboard numbers
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_0, "0", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_1, "1", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_2, "2", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_3, "3", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_4, "4", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_5, "5", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_6, "6", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_7, "7", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_8, "8", COLOR_WHITE);
    g_AssetManager->LoadFontTexture(SHARED_FONT_TEXTURE_9, "9", COLOR_WHITE);

    return true;
}

int main()
{
    if (!initSDL())
    {
        std::cout << "Failed to initialize SDL!" << std::endl;
        destroy_SDL();
        return 1;
    }

    ScreenConfig screenConfig;

    if (!loadSharedAssets(screenConfig))
    {
        std::cout << "Failed to load shared assets!" << std::endl;
        destroy_SDL();
        return 1;
    }

    // Initialize loop
    bool quit = false;
    SDL_Event e;
    Scene currentScene = Scene::Opening;
    OpeningScene *openingScene = new OpeningScene(
        *g_AssetManager, screenConfig.GetBlockSize(),
        screenConfig.GetViewPortWidth(),
        screenConfig.GetViewPortHeight());
    GamePlayScene *gameplayScene = new GamePlayScene(*g_AssetManager, screenConfig.GetBlockSize());
    GameOverScene *gameOverScene = new GameOverScene(*g_AssetManager, screenConfig.GetBlockSize());

    try
    {
        while (!quit)
        {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                }

                switch (currentScene)
                {
                case Scene::GamePlay:
                    gameplayScene->ParseInput(e);
                    break;
                case Scene::Opening:
                    openingScene->ParseInput(e);
                    break;
                case Scene::GameOver:
                    gameOverScene->ParseInput(e);
                    break;
                }
            }

            Scene nextScene = currentScene;

            switch (currentScene)
            {
            case Scene::GameOver:
                if (gameOverScene->RestartRequested())
                {
                    nextScene = Scene::GamePlay;
                    gameplayScene = new GamePlayScene(*g_AssetManager, screenConfig.GetBlockSize());
                    gameOverScene->AcknowledgeRestartRequest();
                }
                break;
            case Scene::GamePlay:
                gameplayScene->Update();
                if (gameplayScene->IsGameOver())
                {
                    gameOverScene->SetNumericValues(
                        gameplayScene->GetPoints(),
                        gameplayScene->GetLevels(),
                        gameplayScene->GetLinesCleared());

                    nextScene = Scene::GameOver;
                }
                break;
            case Scene::Opening:
                if (openingScene->IsReady())
                {
                    nextScene = Scene::GamePlay;
                }
                break;
            }

            // Clear screen
            SDL_SetRenderDrawColor(g_Renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);
            SDL_RenderClear(g_Renderer);

            switch (currentScene)
            {
            case Scene::GamePlay:
                gameplayScene->Render(g_Renderer);
                break;
            case Scene::Opening:
                openingScene->Render(g_Renderer);
                break;
            case Scene::GameOver:
                gameOverScene->Render(g_Renderer, screenConfig.GetViewPortWidth());
                break;
            }

            SDL_RenderPresent(g_Renderer);

            if (nextScene != currentScene)
                currentScene = nextScene;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Game Loop Error: " << e.what() << std::endl;
    }

    if (openingScene != NULL)
    {
        delete openingScene;
    }

    if (gameplayScene != NULL)
    {
        delete gameplayScene;
    }

    if (gameOverScene != NULL)
    {
        delete gameOverScene;
    }

    if (g_AssetManager != NULL)
    {
        delete g_AssetManager;
    }

    std::cout << "Quiting game loop..." << std::endl;

    destroy_SDL();
    return 0;
}