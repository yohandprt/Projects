/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OutputComponent.cpp
*/

#include "OutputComponent.hpp"

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return this->getLink(pin);
}