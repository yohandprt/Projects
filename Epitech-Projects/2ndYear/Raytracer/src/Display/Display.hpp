/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Display.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include "Color.hpp"

namespace RayTracer {
    class Display {
    public:
        Display(unsigned int width, unsigned int height, const std::string& title);
        ~Display();

        void setPixel(unsigned int x, unsigned int y, const Color& color);
        void update(unsigned int row);
        void waitForClose();
        bool isOpen() const;

    private:
        void _handleEvents();

        sf::RenderWindow _window;
        sf::Image _image;
        sf::Texture _texture;
        sf::Sprite _sprite;
    };
}
