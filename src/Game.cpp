#include "Game.hpp"
#include "Util.hpp"
#include <iostream>
#include <thread>
#include <cassert>
#include <SDL_image.h>

namespace smb
{

    bool Game::instantiated = false;

    Game::Game(const std::string &title, unsigned width, unsigned height)
        : m_title{title}
        , m_width{width}
        , m_height{height}
    {
        assert(!instantiated); 
        instantiated = true;
        windowInit();
        m_player.reset(new Player(Vec2<float>{0, 0}, SDL_Rect{0, 0, 0, 0}));

        std::thread renderThread{&Game::render, this};
        std::thread logicThread{&Game::keyInput, this};
        renderThread.join();
        logicThread.join();
    }

    Game::~Game()
    {
        instantiated = false;
        SDL_FreeSurface(m_surface);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }


    void Game::handleInput(SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_playing = false;
            break;
        case SDL_KEYDOWN:
            if(auto* command = handleKeyInput(event);  command != nullptr)
            {
                command->execute();
            }
            break;
        }
    }

    Command* Game::handleKeyInput(SDL_Event& event)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            return m_escCommand.get();
        case SDLK_d:
            return m_dCommand.get();
        case SDLK_a:
            return m_aCommand.get();
        default:
            return nullptr; 
        }
    }

    void Game::render()
    {
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "Could not initialize SDL_image" << std::endl;
            m_playing = false;
        }
        else
        {
            m_surface = SDL_GetWindowSurface(m_window);
        }

        while(m_playing)
        {
           // set screen color to black
           SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));
           m_player->render(0, m_surface); 

           // update window surface
           SDL_UpdateWindowSurface(m_window);
        }
    }

    void Game::keyInput()
    {
        SDL_Event m_event;
        while (m_playing)
        {
            while (SDL_PollEvent(&m_event))
            {
                handleInput(m_event);
            }
        }
    }

    void Game::windowInit()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize!" << std::endl;
        }

        m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);

        if (m_window == NULL)
        {
            std::cout << "Window could not be created" << std::endl;
        }
    }

}