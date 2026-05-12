/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ShiftComponent.cpp
*/

#include "ShiftComponent.hpp"

nts::ShiftComponent::ShiftComponent() : nts::AComponent(15, "4094")
{
    this->_lastValues = {
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined,
        nts::Undefined
    };
    this->_currentValues = {
        nts::Undefined, // Q1
        nts::Undefined, // Q2
        nts::Undefined, // Q3
        nts::Undefined, // Q4
        nts::Undefined, // Q5
        nts::Undefined, // Q6
        nts::Undefined, // Q7
        nts::Undefined, // Q8
        nts::Undefined, // Qs
        nts::Undefined  // Qe
    };
}

void nts::ShiftComponent::simulate(std::size_t tick)
{
    (void)tick;
    this->_lastValues = this->_currentValues;

    if (getLink(15) == nts::False) {
        for (std::size_t i = 0; i < this->_currentValues.size() - 2; i++)
            this->_currentValues[i] = nts::Undefined;
        if (getLink(3) == nts::True)
            this->_currentValues[8] = this->_lastValues[6];
        else if (getLink(3) == nts::False)
            this->_currentValues[9] = this->_lastValues[6];
        return;
    }
    if (getLink(1) == nts::False) {
        if (getLink(3) == nts::True)
            this->_currentValues[8] = this->_lastValues[6];
        else if (getLink(3) == nts::False)
            this->_currentValues[9] = this->_lastValues[6];
        return;
    }

    if (getLink(3) == nts::False) {
        this->_currentValues[9] = this->_lastValues[6];
        return;
    }

    if (getLink(2) == nts::False) {
        this->_currentValues[0] = nts::False;
        for (std::size_t i = 1; i < this->_currentValues.size() - 2; i++)
            this->_currentValues[i] = this->_lastValues[i - 1];
        this->_currentValues[8] = this->_lastValues[6];
    } else if (getLink(2) == nts::True) {
        this->_currentValues[0] = nts::True;
        for (std::size_t i = 1; i < this->_currentValues.size() - 2; i++)
            this->_currentValues[i] = this->_lastValues[i - 1];
        this->_currentValues[8] = this->_lastValues[6];
    }
}

nts::Tristate nts::ShiftComponent::compute(std::size_t pin)
{
    if (pin > this->_nbPins)
        return nts::Undefined;

    if (pin == 4)
        return this->_currentValues[0];
    else if (pin == 5)
        return this->_currentValues[1];
    else if (pin == 6)
        return this->_currentValues[2];
    else if (pin == 7)
        return this->_currentValues[3];
    else if (pin == 14)
        return this->_currentValues[4];
    else if (pin == 13)
        return this->_currentValues[5];
    else if (pin == 12)
        return this->_currentValues[6];
    else if (pin == 11)
        return this->_currentValues[7];
    else if (pin == 9)
        return this->_currentValues[8];
    else if (pin == 10)
        return this->_currentValues[9];
    else
        return getLink(pin);
}