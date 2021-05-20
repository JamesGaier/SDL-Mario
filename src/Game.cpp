#include "Game.hpp"
#include "Util.hpp"

namespace smb
{

    bool Game::instantiated = false;

    Game::Game(const std::string &title, unsigned width, unsigned height)
        : m_title{title}
        , m_width{width}
        , m_height{height}
    {
        
        dynamic_assert(!instantiated, "Game instantiated");
        instantiated = true;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize!" << std::endl;
        }

        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        if (m_window == NULL)
        {
            std::cout << "Window could not be created" << std::endl;
        }
        else
        {
            std::thread renderThread{[&] {
                m_surface = SDL_GetWindowSurface(m_window);
                while(m_playing)
                {
                    // set screen color to black
                    SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));

                    // update window surface
                    SDL_UpdateWindowSurface(m_window);
                }
            }};

            std::thread logicThread{[&] {
                SDL_Event m_event;
                while(m_playing)
                {
                    while(SDL_PollEvent(&m_event))
                    {
                       handleInput(m_event); 
                    }
                }
            }};

            renderThread.join();
            logicThread.join();
        }
    }

    Game::~Game()
    {
        instantiated = false;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }


    void Game::handleInput(SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_playing = false;
            break;
        case SDL_KEYDOWN:
            auto command = handleKeyInput(event);
            if(command != nullptr)
            {
                command->execute();
            }
            break;
        }
    }

    std::shared_ptr<Command> Game::handleKeyInput(SDL_Event& event)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            return m_escCommand;
        case SDLK_d:
            return m_dCommand;
        case SDLK_a:
            return m_aCommand;
        default:
            return nullptr; 
        }
    }
}