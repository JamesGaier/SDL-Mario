#include "Game.hpp"
#include "Level.hpp"
#include "SDL_render.h"
#include <SDL_image.h>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

namespace smb
{

Game::Game(const std::string &title, unsigned width, unsigned height) : m_title{title}, m_width{width}, m_height{height}
{
    assert(!instantiated);
    instantiated = true;

    windowInit();
    std::thread physicsThread{&Game::update, this};
    render();
    physicsThread.join();
}

Game::~Game()
{
    instantiated = false;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    m_renderer = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void Game::render()
{
    while (m_playing)
    {
        while (SDL_PollEvent(&m_event))
        {
            if (m_event.type == SDL_QUIT || m_event.key.keysym.sym == SDLK_ESCAPE)
            {
                m_playing = false;
            }
        }
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 0x93, 0xBB, 0xEC, 0xFF); // Please change magic numbers here
        m_level->render();
        SDL_RenderPresent(m_renderer);
    }
}

void Game::windowInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize!" << std::endl;
    }

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        std::cout << "Window could not be created" << std::endl;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_level.reset(new Level("w1-1.txt", m_renderer));

    if (m_renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        m_playing = false;
    }
    else
    {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "Could not initialize SDL_image" << std::endl;
            m_playing = false;
        }
    }
}

float Game::getCurrentTime()
{
    using namespace std::chrono;
    auto currentTime = steady_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(currentTime).count();
}

void Game::update()
{
    constexpr auto dt = 1.0f / 60;
    auto currentTime = getCurrentTime();
    auto accumulator = 0.0f;

    while (m_playing)
    {
        auto newTime = getCurrentTime();
        auto frameTime = (newTime - currentTime) / 1000.0f;
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            m_level->update(dt);
            accumulator -= dt;
        }
    }
}

} // namespace smb
