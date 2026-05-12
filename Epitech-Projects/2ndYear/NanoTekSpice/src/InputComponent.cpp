/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** InputComponent.cpp
*/

#include "InputComponent.hpp"

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    this->setStatus(this->_futurStatus);
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return this->_status;
}