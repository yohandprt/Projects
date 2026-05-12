/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ArcadeSfml.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <memory>

#include "ADisplayModule.hpp"

#include "SfmlRectangle.hpp"
#include "SfmlCircle.hpp"
#include "SfmlSprite.hpp"

#include <SFML/Graphics.hpp>

namespace ARCADE {

    static std::map<std::string, sf::Keyboard::Key> sfmlKeys = {
        {"z", sf::Keyboard::Z},
        {"q", sf::Keyboard::Q},
        {"s", sf::Keyboard::S},
        {"d", sf::Keyboard::D},
        {"m", sf::Keyboard::M},
        {"r", sf::Keyboard::R},
        {"up", sf::Keyboard::Up},
        {"down", sf::Keyboard::Down},
        {"left", sf::Keyboard::Left},
        {"right", sf::Keyboard::Right},
        {"space", sf::Keyboard::Space},
        {"tab", sf::Keyboard::Tab},
        {"enter", sf::Keyboard::Return},
        {"esc", sf::Keyboard::Escape}
    };

    static std::map<ARCADE::Color, sf::Color> sfmlColors = {
        {ARCADE::Color::Black, sf::Color::Black},
        {ARCADE::Color::White, sf::Color::White},
        {ARCADE::Color::Red, sf::Color::Red},
        {ARCADE::Color::Green, sf::Color::Green},
        {ARCADE::Color::Blue, sf::Color::Blue},
        {ARCADE::Color::Yellow, sf::Color::Yellow},
    };

    class SFML : public ARCADE::ADisplayModule
    {
    private:
        sf::Event _event;
        std::unique_ptr<sf::RenderWindow> _window;
    public:
        SFML() = default;
        ~SFML() = default;

        void init() override;
        void stop() override;
        bool isOpen() override;
        bool pollEvent() override;
        void close() override;
        void clear() override;
        void display() override;

        std::size_t getWindowSizeX() const override;
        std::size_t getWindowSizeY() const override;
        bool isKeyPressed(std::string key) override;
        std::string getKeyPressed() override;
        std::unique_ptr<ARCADE::IRectangle> createRectangle() override;
        std::unique_ptr<ARCADE::ICircle> createCircle() override;
        std::unique_ptr<ARCADE::IRectangle> createSprite() override;
    };
}