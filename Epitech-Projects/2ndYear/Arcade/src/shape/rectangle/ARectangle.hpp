/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ARectangle.hpp
*/

#pragma once

#include "IRectangle.hpp"

namespace ARCADE {
    class ARectangle : public IRectangle
    {
    protected:
        float _w;
        float _h;
    public:
        ARectangle();
        ~ARectangle() = default;

        float getWidth() const override;
        float getHeight() const override;
        std::string getText() const override;
        ARCADE::Color getTextColor() const override;

        void setWidth(float width) override;
        void setHeight(float height) override;
        void setText(std::string text, std::size_t charactereSize, ARCADE::Color color) override;
    };
}