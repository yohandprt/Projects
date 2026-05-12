/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4001.cpp
*/

#include "4001.hpp"

void nts::nts4001Component::simulate(std::size_t tick)
{
    (void)tick;
    this->_visited.clear();
}

nts::Tristate nts::nts4001Component::compute(std::size_t pin)
{
    if (pin == 7 || pin == 14 || pin > this->_nbPins)
        return nts::Undefined;
    
    if (pin == 3)
        return !(this->getLink(1, this->_visited) || this->getLink(2, this->_visited));
    else if (pin == 4)
        return !(this->getLink(5, this->_visited) || this->getLink(6, this->_visited));
    else if (pin == 10)
        return !(this->getLink(8, this->_visited) || this->getLink(9, this->_visited));
    else if (pin == 11)
        return !(this->getLink(12, this->_visited) || this->getLink(13, this->_visited));
    else
        return this->getLink(pin, this->_visited);
}