/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include <iostream>
#include <memory>

#include "IModule.hpp"
#include "IRectangle.hpp"
#include "ICircle.hpp"

namespace ARCADE {

    class IDisplayModule : public ARCADE::IModule
    {
    public:
        virtual ~IDisplayModule() = default;
        virtual void init() = 0;
        virtual void stop() = 0;
        virtual bool isOpen() = 0;
        virtual bool pollEvent() = 0;
        virtual void close() = 0;
        virtual void clear() = 0;
        virtual void display() = 0;
    };
}