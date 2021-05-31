#pragma once

#include "Command.hpp"
#include "Ground.hpp"
#include "Player.hpp"
#include <SDL.h>
#include <atomic>
#include <memory>

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
    std::string m_title{};
    unsigned m_width;
    unsigned m_height;
    SDL_Window *m_window = NULL;
    SDL_Renderer *m_renderer = NULL;
    static bool instantiated;
    std::atomic<bool> m_playing{true};
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Ground> m_ground;
    std::unique_ptr<Command> m_escCommand;
    std::unique_ptr<Command> m_aCommand;
    std::unique_ptr<Command> m_dCommand;

    void handleInput(SDL_Event &event);
    Command *handleKeyInput(SDL_Event &event);
    void render();
    void keyInput();
    void windowInit();
    void rendererInit();
    void update();
};

} // namespace smb