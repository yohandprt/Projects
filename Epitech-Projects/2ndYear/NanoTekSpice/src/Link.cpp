/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Link.cpp
*/

#include "Link.hpp"

nts::IComponent &nts::Link::getComponent()
{
    return this->_component;
}

std::size_t nts::Link::getPin() const
{
    return this->_pin;
}