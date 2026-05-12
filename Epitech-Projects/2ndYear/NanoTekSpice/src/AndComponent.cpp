/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AndComponent.cpp
*/

#include "AndComponent.hpp"

nts::Tristate nts::AndComponent::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2)
        return this->getLink(pin);

    nts::Tristate a = this->getLink(1);
    nts::Tristate b = this->getLink(2);

    return a && b;
}