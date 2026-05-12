/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** TrueComponent.cpp
*/

#include "TrueComponent.hpp"

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return nts::True;
}