/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4069.cpp
*/

#include "4069.hpp"

nts::Tristate nts::nts4069Component::compute(std::size_t pin)
{
    if (pin == 7 || pin == 14 || pin > this->_nbPins)
        return nts::Undefined;

    if (pin == 2)
        return !this->getLink(1);
    else if (pin == 4)
        return !this->getLink(3);
    else if (pin == 6)
        return !this->getLink(5);
    else if (pin == 8)
        return !this->getLink(9);
    else if (pin == 10)
        return !this->getLink(11);
    else if (pin == 12)
        return !this->getLink(13);
    else
        return this->getLink(pin);
}