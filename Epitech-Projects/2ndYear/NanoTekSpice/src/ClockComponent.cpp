/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ClockComponent.cpp
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent() : nts::AComponent(1, "clock")
{
    this->_lastStatus = nts::Undefined;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (this->_lastStatus != nts::Undefined && this->_futurStatus == nts::Undefined) {
        this->setStatus(nts::Undefined);
        this->_lastStatus = this->_futurStatus;
        return;
    }
    if (this->_status == nts::Undefined) {
        this->setStatus(this->_futurStatus);
        this->_tempStatus = this->_futurStatus;
        this->_lastStatus = this->_futurStatus;
        return;
    }
    if (this->_tempStatus != this->_futurStatus) {
        this->setStatus(this->_futurStatus);
        this->_tempStatus = this->_futurStatus;
        this->_lastStatus = this->_futurStatus;
        return;
    }
    if (tick % 2 == 0)
        return;
    else if (this->_status == nts::False) {
        this->_status = nts::True;
        this->_tempStatus = this->_futurStatus;
        this->_lastStatus = this->_futurStatus;
    } else {
        this->_status = nts::False;
        this->_tempStatus = this->_futurStatus;
        this->_lastStatus = this->_futurStatus;
    }
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return this->_status;
}