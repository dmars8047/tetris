#include <iostream>
#include <random>

#if __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#elif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include "timer.hpp"
#include "constants.hpp"
#include "block.hpp"
#include "board.hpp"
#include "tetromino.hpp"

SDL_Window *g_MainWindow = NULL;
SDL_Renderer *g_Renderer = NULL;
SDL_GameController *g_GameController = NULL;

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

    g_MainWindow = SDL_CreateWindow(APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

int main()
{
    if (!initSDL())
    {
        std::cout << "Failed to initialize window!" << std::endl;
        destroy_SDL();
        return 1;
    }

    // Initialize loop
    bool quit = false;
    SDL_Event e;
    Timer timer = Timer();
    int roundDelta = 0;
    int roundMax = 1000;

    // Random number generation
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist7(0, 6);
    int typeNum = dist7(rng);

    int rotationDelta = 100;
    int movementDelta = 100;

    Board *p_Board = new Board();
    Tetromino *p_Tetromino = new Tetromino((TetrominoType)typeNum);

    try
    {
        while (!quit)
        {
            timer.StartNewFrame();

            if (p_Tetromino->GetIsLanded())
            {
                int typeNum = dist7(rng);
                p_Tetromino = new Tetromino((TetrominoType)typeNum);
                roundDelta = 0;
            }

            if (roundDelta >= roundMax)
            {
                p_Tetromino->MoveDown(p_Board);
                roundDelta = 0;
            }

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
                    case SDLK_UP:
                        if (rotationDelta >= 100)
                        {
                            p_Tetromino->Rotate(p_Board);
                            rotationDelta = 0;
                        }
                        break;
                    case SDLK_DOWN:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveDown(p_Board);

                            if (!p_Tetromino->GetIsLanded())
                            {
                                roundDelta = 0;
                            }

                            movementDelta = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveRight(p_Board);
                            movementDelta = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveLeft(p_Board);
                            movementDelta = 0;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            // Clear screen
            SDL_SetRenderDrawColor(g_Renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);
            SDL_RenderClear(g_Renderer);

            p_Board->Render(g_Renderer);

            SDL_SetRenderDrawColor(g_Renderer, 0, 255, 0, BACKGROUND_ALPHA);

            p_Tetromino->Render(g_Renderer);

            SDL_RenderPresent(g_Renderer);
            roundDelta += timer.GetDeltaMilliSeconds();

            if (rotationDelta < 100)
            {
                rotationDelta += timer.GetDeltaMilliSeconds();
            }

            if (movementDelta < 100)
            {
                movementDelta += timer.GetDeltaMilliSeconds();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Game Loop Error: " << e.what() << std::endl;
    }

    if (p_Tetromino != NULL)
    {
        delete p_Tetromino;
    }

    if (p_Board != NULL)
    {
        delete p_Board;
    }

    std::cout << "Quiting game loop..." << std::endl;

    destroy_SDL();
    return 0;
}