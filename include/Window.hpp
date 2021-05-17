#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>

namespace smb
{

    class Window
    {
    public:
        ~Window();

        Window(const std::string &title, unsigned width, unsigned height);

        Window &operator=(const Window &window) = delete;

        Window &operator=(const Window &&window) = delete;

        Window(const Window &window) = delete;

        Window(Window &&window) = delete;

    private:
        unsigned m_width;
        unsigned m_height;
        std::string m_title{};
        SDL_Window *m_window = NULL;
        SDL_Surface *m_surface = NULL;
        static bool instantiated;

    };


}