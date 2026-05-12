/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ArcadeSdl.cpp
*/

#include "ArcadeSdl.hpp"

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()
{
    return std::make_unique<ARCADE::SDL2>();
}

ARCADE::SDL2::SDL2() : _window(nullptr, SDL_DestroyWindow), _renderer(nullptr, SDL_DestroyRenderer), _event{}, _isOpen(true), _maxX(0), _maxY(0)
{
}

void ARCADE::SDL2::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    this->_window.reset(SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP));
    if (!this->_window) {
        printf("ERROR: %s\n", SDL_GetError());
        SDL_Quit();
    }

    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!this->_renderer) {
        printf("ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(this->_window.get());
        SDL_Quit();
    }
    TTF_Init();
    SDL_StartTextInput();

    SDL_GetWindowSizeInPixels(this->_window.get(), &this->_maxX, &this->_maxY);
};

void ARCADE::SDL2::stop()
{
    if (SDL_WasInit(SDL_INIT_VIDEO))
        SDL_Quit();

    TTF_Quit();
    SDL_StopTextInput();
}

bool ARCADE::SDL2::isOpen()
{
    return this->_isOpen;
}

bool ARCADE::SDL2::pollEvent()
{
    bool poll = SDL_PollEvent(&this->_event);

    if (!poll)
        return false;

    if (this->_event.type == SDL_EventType::SDL_QUIT || this->isKeyPressed("esc"))
        this->close();
    return poll;
}

void ARCADE::SDL2::close()
{
    this->_isOpen = false;
}

void ARCADE::SDL2::clear()
{
    SDL_SetRenderDrawColor(this->_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer.get());
}

void ARCADE::SDL2::display()
{
    SDL_RenderPresent(this->_renderer.get());
}

std::size_t ARCADE::SDL2::getWindowSizeX() const
{
    return this->_maxX;
}

std::size_t ARCADE::SDL2::getWindowSizeY() const
{
    return this->_maxY;
}

bool ARCADE::SDL2::isKeyPressed(std::string key)
{
    if (!ARCADE::sdlKeys.contains(key))
        return false;
    SDL_Scancode scancode = SDL_GetScancodeFromKey(ARCADE::sdlKeys.at(key));
    if (SDL_GetKeyboardState(nullptr)[scancode])
        return true;

    if (this->_event.type == SDL_KEYDOWN) {
        if (this->_event.key.keysym.sym == ARCADE::sdlKeys.at(key))
            return true;
    }
    return false;
}

std::string ARCADE::SDL2::getKeyPressed()
{
    if (this->_event.type == SDL_TEXTINPUT) {
        std::string letter = this->_event.text.text;

        if (letter.size() == 1 && std::isalnum(static_cast<unsigned char>(letter[0])))
            return letter;
    }
    return "";
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::SDL2::createRectangle()
{
    return std::make_unique<ARCADE::SdlRectangle>(this->_renderer);
}

std::unique_ptr<ARCADE::ICircle> ARCADE::SDL2::createCircle()
{
    return std::make_unique<ARCADE::SdlCircle>(this->_renderer);
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::SDL2::createSprite()
{
    return std::make_unique<ARCADE::SdlSprite>(this->_renderer);
}