#pragma once

#include "Level.hpp"
#include <SDL.h>
#include <atomic>
#include <memory>
#include <mutex>


namespace smb
{

class Game
{
  public:
    ~Game();

    Game(const std::string &title, unsigned width, unsigned height);

    Game &operator=(const Game &game) = delete;

    Game &operator=(Game &&Game) = delete;

    Game(const Game &Game) = delete;

    Game(Game &&Game) = delete;

  private:
    std::string m_title{};
    unsigned m_width;
    unsigned m_height;
    SDL_Window *m_window{nullptr};
    SDL_Renderer *m_renderer{nullptr};
    inline static bool instantiated{false};
    std::atomic<bool> m_playing{true};
    std::unique_ptr<Level> m_level;
    SDL_Event m_event;
    std::mutex m_mutex;

    void render();
    void windowInit();
    void rendererInit();
    void update();
    float getCurrentTime();
};

} // namespace smb
