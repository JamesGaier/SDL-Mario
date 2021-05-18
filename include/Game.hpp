#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <future>

namespace smb
{

    class Game
    {
    public:
        ~Game();

        Game(const std::string &title, unsigned width, unsigned height);

        Game &operator=(const Game &game) = delete;

        Game &operator=(const Game &&Game) = delete;

        Game(const Game &Game) = delete;

        Game(Game &&Game) = delete;

    private:
        unsigned m_width;
        unsigned m_height;
        std::string m_title{};
        SDL_Window *m_window = NULL;
        SDL_Surface *m_surface = NULL;
        static bool instantiated;
        std::atomic<bool> m_playing{true};
    };

}