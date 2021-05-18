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

            std::thread renderThread{[this] {
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
                    while(SDL_PollEvent(&m_event) != 0)
                    {
                        std::cout << (m_event.type == SDL_QUIT) << std::boolalpha << std::endl;
                        if(m_event.type == SDL_QUIT)
                        {
                            m_playing = false;
                        }
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
}