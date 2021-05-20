#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <future>
#include <map>
#include <optional>
#include "Command.hpp"

namespace smb
{

    enum class Key
    {
        ESC,
        W,
        A,
        S,
        D
    };

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
        std::shared_ptr<Command> m_escCommand{
            new EscCommand([&] {
                m_playing = false;
            })
        };
        std::shared_ptr<Command> m_aCommand{ new ACommand() };
        std::shared_ptr<Command> m_dCommand{ new DCommand() };
        
        void handleInput(SDL_Event& event);
        std::shared_ptr<Command> handleKeyInput(SDL_Event& event);
    };

}