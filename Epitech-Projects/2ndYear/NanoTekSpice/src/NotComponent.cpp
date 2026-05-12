/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** NotComponent.cpp
*/

#include "NotComponent.hpp"

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{
    if (pin != 1 && pin != 2)
        return nts::Undefined;
    nts::Tristate currentStatus = this->getLink(1);

    if (pin == 1)
        return currentStatus;
    return !currentStatus;
}