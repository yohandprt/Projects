/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** XorComponent.cpp
*/

#include "XorComponent.hpp"

nts::Tristate nts::XorComponent::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2)
        return this->getLink(pin);

    nts::Tristate a = this->getLink(1);
    nts::Tristate b = this->getLink(2);

    return a ^ b;
}