/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4081.cpp
*/

#include "4081.hpp"

nts::Tristate nts::nts4081Component::compute(std::size_t pin)
{
    if (pin == 7 || pin == 14 || pin > this->_nbPins)
        return nts::Undefined;
    
    if (pin == 3)
        return this->getLink(1) && this->getLink(2);
    else if (pin == 4)
        return this->getLink(5) && this->getLink(6);
    else if (pin == 10)
        return this->getLink(8) && this->getLink(9);
    else if (pin == 11)
        return this->getLink(12) && this->getLink(13);
    else
        return this->getLink(pin);
}