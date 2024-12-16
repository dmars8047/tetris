#include "gameplayscene.hpp"

GamePlayScene::GamePlayScene(AssetManager &assetManager, int blockSize)
{
    m_Timer = Timer();

    m_Rng = std::mt19937(m_Dev());
    m_Dist7 = std::uniform_int_distribution<std::mt19937::result_type>(0, 6);

    m_Points = 0;
    m_Level = 0;
    m_LinesCleared = 0;
    m_SoftDrops = 0;
    m_BlockSize = blockSize;

    m_RoundMax = 800;
    m_RoundDelta = 0;
    m_RotationalDelta = m_MaxRotationDelta;
    m_MovementDelta = m_MaxMovementDelta;
    m_DownwardMovementMultiplier = 1;
    m_IsGameOver = false;
    m_GameStarted = false;
    m_LastUsedKey = SDL_KeyCode::SDLK_UNKNOWN;

    m_Board = new Board(blockSize);
    m_Preview = new Preview((TetrominoType)m_Dist7(m_Rng), blockSize);
    m_Tetromino = new Tetromino(GetRandomTetrominoType(m_Preview->GetType()), blockSize);
    m_LinesDisplay = new NumericDisplay(assetManager, "line-display-title", "Lines", 12, 7, blockSize);
    m_PointsDisplay = new NumericDisplay(assetManager, "points-display-title", "Points", 12, 11, blockSize);
    m_LevelDisplay = new NumericDisplay(assetManager, "level-display-title", "Level", 12, 15, blockSize);

    assetManager.LoadMusic("tetrizz", "./assets/music/Tetrizz.mp3");
    m_Music = assetManager.GetMusic("tetrizz");
}

GamePlayScene::~GamePlayScene()
{
    delete m_Board;
    delete m_Tetromino;
    delete m_Preview;
    delete m_LinesDisplay;
    delete m_PointsDisplay;
    delete m_LevelDisplay;
}

void GamePlayScene::ParseInput(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            m_LastUsedKey = SDLK_UP;
            if (m_RotationalDelta >= m_MaxRotationDelta)
            {
                m_Tetromino->Rotate(*m_Board);
                m_RotationalDelta = 0;
            }
            if (SDL_GetKeyboardState)
                break;
        case SDLK_DOWN:
        case SDLK_s:
            if (m_MovementDelta >= m_MaxMovementDelta)
            {
                m_SoftDrops++;
                m_Tetromino->MoveDown(*m_Board);

                if (!m_Tetromino->GetIsLanded())
                {
                    m_RoundDelta = 0;
                }

                m_MovementDelta = 0;
            }

            if (m_LastUsedKey == SDLK_DOWN)
            {
                m_DownwardMovementMultiplier = 2;
            }
            else
            {
                m_LastUsedKey = SDLK_DOWN;
            }

            break;
        case SDLK_RIGHT:
        case SDLK_d:
            m_LastUsedKey = SDLK_RIGHT;
            if (m_MovementDelta >= m_MaxMovementDelta)
            {
                m_Tetromino->MoveRight(*m_Board);
                m_MovementDelta = 0;
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            m_LastUsedKey = SDLK_LEFT;
            if (m_MovementDelta >= m_MaxMovementDelta)
            {
                m_Tetromino->MoveLeft(*m_Board);
                m_MovementDelta = 0;
            }
            break;
        default:
            m_LastUsedKey = SDLK_UNKNOWN;
            break;
        }
    }
    else
    {
        if (m_LastUsedKey == SDLK_DOWN)
        {
            m_LastUsedKey == SDLK_UNKNOWN;
            m_SoftDrops = 0;
        }
    }

    if (m_LastUsedKey != SDLK_DOWN)
    {
        m_SoftDrops = 0;
        m_DownwardMovementMultiplier = 1;
    }
}

void GamePlayScene::Render(SDL_Renderer *renderer) const
{
    m_Board->Render(renderer);
    m_Preview->Render(renderer);
    m_LinesDisplay->Render(renderer);
    m_PointsDisplay->Render(renderer);
    m_LevelDisplay->Render(renderer);
    m_Tetromino->Render(renderer);
}

void GamePlayScene::Update()
{
    if (!m_GameStarted)
    {
        m_Timer.StartNewFrame();
        m_GameStarted = true;
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        Mix_PlayMusic(m_Music, -1);
    }

    m_Timer.StartNewFrame();

    if (m_Tetromino->GetIsLanded())
    {
        int clearedLines = m_Board->ClearCompletedRows();

        if (clearedLines > 0)
        {
            m_LinesCleared += clearedLines;
            m_LinesDisplay->SetValue(m_LinesCleared);

            if (m_LinesCleared >= (m_Level + 1) * 10)
            {
                m_Level++;
                m_LevelDisplay->SetValue(m_Level);
                // Make gravity faster
                if (m_Level <= 40)
                {
                    m_RoundMax = m_RoundMax - (m_RoundMax * .15);
                    std::cout << "Setting round timer to : " << m_RoundMax << std::endl;
                }
            }

            switch (clearedLines)
            {
            case 1:
                m_Points += 40 * (m_Level + 1);
                break;
            case 2:
                m_Points += 100 * (m_Level + 1);
                break;
            case 3:
                m_Points += 300 * (m_Level + 1);
                break;
            case 4:
                m_Points += 1200 * (m_Level + 1);
                break;
            }
        }

        m_Points += m_SoftDrops;
        std::cout << "Soft Drops: " << m_SoftDrops << std::endl;
        m_PointsDisplay->SetValue(m_Points);
        m_SoftDrops = 0;

        m_Tetromino = new Tetromino(m_Preview->GetType(), m_BlockSize);
        m_Preview = new Preview(GetRandomTetrominoType(m_Preview->GetType()), m_BlockSize);

        if (m_Tetromino->DetectCollision(*m_Board))
        {
            std::cout << "GAME OVER" << std::endl;
            m_IsGameOver = true;
        }

        m_RoundDelta = 0;
        m_DownwardMovementMultiplier = 1;
    }

    if (m_RoundDelta >= m_RoundMax)
    {
        m_Tetromino->MoveDown(*m_Board);
        m_RoundDelta = m_RoundMax - m_RoundDelta;
    }

    m_RoundDelta += m_Timer.GetDeltaMilliSeconds();

    if (m_RotationalDelta < m_MaxRotationDelta)
    {
        m_RotationalDelta += m_Timer.GetDeltaMilliSeconds();
    }

    if (m_MovementDelta < m_MaxMovementDelta)
    {
        m_MovementDelta += m_Timer.GetDeltaMilliSeconds() * m_DownwardMovementMultiplier;
    }
}

bool GamePlayScene::IsGameOver() const
{
    return m_IsGameOver;
}

int GamePlayScene::GetLevels() const
{
    return m_Level;
}

int GamePlayScene::GetLinesCleared() const
{
    return m_LinesCleared;
}

int GamePlayScene::GetPoints() const
{
    return m_Points;
}

TetrominoType GamePlayScene::GetRandomTetrominoType(TetrominoType previous)
{
    TetrominoType newType = previous;

    while (newType == previous)
    {
        newType = (TetrominoType)m_Dist7(m_Rng);
    }

    return newType;
}
