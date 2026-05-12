/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** FalseComponent.cpp
*/

#include "FalseComponent.hpp"

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return nts::False;
}