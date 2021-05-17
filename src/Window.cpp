#include "Window.hpp"
#include "Util.hpp"

namespace smb
{

    bool Window::instantiated = false;

    Window::Window(const std::string &title, unsigned width, unsigned height)
        : m_title{title}
        , m_width{width}
        , m_height{height}
    {

        dynamic_assert(!instantiated, "Window Created");
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
            // get window surface
            m_surface = SDL_GetWindowSurface(m_window);

            // set screen color to black
            SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));

            // update window surface
            SDL_UpdateWindowSurface(m_window);

            SDL_Delay(2000);
        }
    }

    Window::~Window()
    {
        instantiated = false;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}