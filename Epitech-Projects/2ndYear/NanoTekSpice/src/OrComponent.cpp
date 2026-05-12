/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OrComponent.cpp
*/

#include "OrComponent.hpp"

nts::Tristate nts::OrComponent::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2)
        return this->getLink(pin);
    
    nts::Tristate a = this->getLink(1);
    nts::Tristate b = this->getLink(2);

    return a || b;
}