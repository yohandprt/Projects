/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Display.cpp
*/

#include "Display.hpp"

RayTracer::Display::Display(unsigned int width, unsigned int height, const std::string& title)
    : _window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close)
{
    _image.create(width, height, sf::Color::Black);
    _texture.create(width, height);
    _sprite.setTexture(_texture);
}

RayTracer::Display::~Display()
{
    waitForClose();
}


void RayTracer::Display::setPixel(unsigned int x, unsigned int y, const Color& color)
{
    _image.setPixel(x, y, sf::Color(
        static_cast<sf::Uint8>(std::min(color.r, static_cast<std::size_t>(255))),
        static_cast<sf::Uint8>(std::min(color.g, static_cast<std::size_t>(255))),
        static_cast<sf::Uint8>(std::min(color.b, static_cast<std::size_t>(255)))
    ));
}

void RayTracer::Display::update(unsigned int row)
{
    _handleEvents();
    const sf::Uint8* rowStart = _image.getPixelsPtr() + row * _image.getSize().x * 4;
    _texture.update(rowStart, _image.getSize().x, 1, 0, row);
    _window.draw(_sprite);
    _window.display();
}

void RayTracer::Display::waitForClose()
{
    while (_window.isOpen()) {
        _handleEvents();
    }
}

bool RayTracer::Display::isOpen() const
{
    return _window.isOpen();
}

void RayTracer::Display::_handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            _window.close();
    }
}
