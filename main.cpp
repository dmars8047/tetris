#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "timer.hpp"
#include "constants.hpp"
#include "block.hpp"
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

void drawBoard()
{
    // Draw the grid
    SDL_SetRenderDrawColor(g_Renderer, 51, 51, 51, 0);

    // Draw vertical grid lines
    for (int x = BLOCK_SIZE * 2; x < WINDOW_WIDTH - (BLOCK_SIZE); x += BLOCK_SIZE)
    {
        SDL_RenderDrawLine(g_Renderer, x, BLOCK_SIZE, x, WINDOW_HEIGHT - BLOCK_SIZE);
    }

    // Draw horizontal grid lines
    for (int y = BLOCK_SIZE * 2; y < WINDOW_HEIGHT - (BLOCK_SIZE); y += BLOCK_SIZE)
    {
        SDL_RenderDrawLine(g_Renderer, BLOCK_SIZE, y, WINDOW_WIDTH - BLOCK_SIZE, y);
    }

    // Draw the border of the board
    SDL_SetRenderDrawColor(g_Renderer, 255, 255, 255, 0);

    SDL_Point boardPoints[] = {
        SDL_Point{x : BLOCK_SIZE, y : BLOCK_SIZE},
        SDL_Point{x : BLOCK_SIZE, y : WINDOW_HEIGHT - BLOCK_SIZE},
        SDL_Point{x : WINDOW_WIDTH - BLOCK_SIZE, y : WINDOW_HEIGHT - BLOCK_SIZE},
        SDL_Point{x : WINDOW_WIDTH - BLOCK_SIZE, y : BLOCK_SIZE},
        SDL_Point{x : BLOCK_SIZE, y : BLOCK_SIZE}};

    // Draw the board
    SDL_RenderDrawLines(g_Renderer, boardPoints, 5);
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
    int roundMax = 100000;

    int rotationDelta = 100;
    int movementDelta = 100;

    Tetromino *p_Tetromino = new Tetromino(TetrominoType::Z);

    try
    {
        while (!quit)
        {
            timer.StartNewFrame();

            if (roundDelta >= roundMax)
            {
                p_Tetromino->MoveDown();
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
                            p_Tetromino->Rotate();
                            rotationDelta = 0;
                        }
                        break;
                    case SDLK_DOWN:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveDown();
                            roundDelta = 0;
                            movementDelta = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveRight();
                            movementDelta = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        if (movementDelta >= 100)
                        {
                            p_Tetromino->MoveLeft();
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

            drawBoard();

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

    std::cout << "Quiting game loop..." << std::endl;

    destroy_SDL();
    return 0;
}