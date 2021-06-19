#include "Game.hpp"
#include "Level.hpp"
#include <SDL_image.h>
#include <cassert>
#include <thread>
#include <iostream>

namespace smb
{

bool Game::instantiated = false;

Game::Game(const std::string &title, unsigned width, unsigned height) : m_title{title}, m_width{width}, m_height{height}
{
    assert(!instantiated);
    instantiated = true;

    m_level.reset(new Level("w1-1.txt"));

    std::thread renderThread{&Game::render, this};
    std::thread physicsThread{&Game::update, this};
    renderThread.join();
    physicsThread.join();
}

Game::~Game()
{
    instantiated = false;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    m_renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}



void Game::render()
{
    windowInit();
    while (m_playing)
    {
        while (SDL_PollEvent(&m_event))
        {
            if(m_event.type == SDL_QUIT || m_event.key.keysym.sym == SDLK_ESCAPE)
            {
                m_playing = false;
            }
        }
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 0x93, 0xBB, 0xEC, 0xFF); // Please change magic numbers here
        m_level->render(m_renderer);
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

    if (m_window == NULL)
    {
        std::cout << "Window could not be created" << std::endl;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL)
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

void Game::update()
{
    while (m_playing)
    {
        m_level->update(1);
    }
}

void Game::rendererInit()
{
}

} // namespace smb