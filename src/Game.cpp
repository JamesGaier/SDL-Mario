#include "Game.hpp"
#include "Level.hpp"
#include <SDL_image.h>
#include <cassert>
#include <iostream>
#include <thread>

namespace smb
{

bool Game::instantiated = false;

Game::Game(const std::string &title, unsigned width, unsigned height) : m_title{title}, m_width{width}, m_height{height}
{
    assert(!instantiated);
    instantiated = true;

    m_level.reset(new Level("w1-1.txt"));
    m_escCommand.reset(new EscCommand([&] { m_playing = false; }));

    render();
    // std::thread renderThread{&Game::render, this};
    std::thread physicsThread{&Game::update, this};
    // renderThread.join();
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

void Game::handleInput(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        m_playing = false;
        break;
    case SDL_KEYDOWN:
        if (auto *command = handleKeyInput(event); command != nullptr)
        {
            command->execute();
        }
        break;
    }
}

Command *Game::handleKeyInput(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        return m_escCommand.get();
    case SDLK_d:
        return m_level->getDCommand();
    case SDLK_a:
        return m_level->getACommand();
    default:
        return nullptr;
    }
}

void Game::render()
{
    windowInit();
    while (m_playing)
    {
        while (SDL_PollEvent(&m_event))
        {
            handleInput(m_event);
        }
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 0x93, 0xBB, 0xEC, 0xFF);
        m_level->render(0, m_renderer);
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