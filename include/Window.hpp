#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>


class Window
{
public:
    unsigned m_width = 800u;
    unsigned m_height = 600u;
    std::string m_title = "";
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    ~Window()
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    Window& operator=(const Window& window) = delete;

    Window& operator=(const Window&& window) = delete;

    Window(const Window& window) = delete;

    Window(Window&& window) = delete;

    Window()
    {
        Window(m_title, m_width, m_height);
    }

    Window(const std::string& title, unsigned width, unsigned height) 
    : m_width{width}
    , m_height{height} 
    , m_title{title}
    {

        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize!" << std::endl;
        }

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        if(window == NULL)
        {
            std::cout << "Window could not be created" << std::endl;
        }
        else
        {
            // get window surface
            surface = SDL_GetWindowSurface(window);

            // set screen color to black
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

            // update window surface
            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
        }
    }
};
