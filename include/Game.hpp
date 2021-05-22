#pragma once

#include <SDL.h>
#include <memory>
#include <atomic>
#include "Command.hpp"
#include "Player.hpp"

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
        std::string m_title{};
        unsigned m_width;
        unsigned m_height;
        SDL_Window *m_window = NULL;
        SDL_Surface *m_surface = NULL;
        static bool instantiated;
        std::atomic<bool> m_playing{true};
        std::unique_ptr<Command> m_escCommand{
            new EscCommand([&] {
                m_playing = false;
            })
        };
        std::unique_ptr<Command> m_aCommand{ new ACommand() };
        std::unique_ptr<Command> m_dCommand{ new DCommand() };
        std::unique_ptr<Player> m_player;
        
        void handleInput(SDL_Event& event);
        Command* handleKeyInput(SDL_Event& event);
        void render();
        void keyInput();
        void windowInit();
    };

}