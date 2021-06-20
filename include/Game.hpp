#pragma once

#include "Ground.hpp"
#include "Level.hpp"
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
    std::unique_ptr<Level> m_level;
    SDL_Event m_event;

    void render();
    void windowInit();
    void rendererInit();
    void update();
    float getCurrentTime();
};

} // namespace smb