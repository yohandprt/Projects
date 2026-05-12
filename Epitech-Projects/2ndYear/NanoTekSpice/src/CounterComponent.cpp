/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CounterComponent.cpp
*/

#include "CounterComponent.hpp"

nts::CounterComponent::CounterComponent() : nts::AComponent(16, "4040")
{
    this->_currentNb = {
        nts::Undefined,
        nts::Undefined,
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
    this->_increment = {
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::False,
        nts::True
    };
}

nts::Tristate nts::CounterComponent::getValue(std::size_t pin)
{
    if (pin == 1)
        return this->_currentNb[0];
    else if (pin == 15)
        return this->_currentNb[1];
    else if (pin == 14)
        return this->_currentNb[2];
    else if (pin == 12)
        return this->_currentNb[3];
    else if (pin == 13)
        return this->_currentNb[4];
    else if (pin == 4)
        return this->_currentNb[5];
    else if (pin == 2)
        return this->_currentNb[6];
    else if (pin == 3)
        return this->_currentNb[7];
    else if (pin == 5)
        return this->_currentNb[8];
    else if (pin == 6)
        return this->_currentNb[9];
    else if (pin == 7)
        return this->_currentNb[10];
    else if (pin == 9)
        return this->_currentNb[11];
    else
        return this->getLink(pin);
}

void nts::CounterComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (this->getLink(11) == nts::True) {
        for (std::size_t i = 0; i < this->_currentNb.size(); i++)
            this->_currentNb[i] = nts::False;
        return;
    }
    if (!(this->getLink(10) == nts::True || this->getLink(10) == nts::Undefined))
        this->_currentNb = this->_adder.addVecTriBin(this->_currentNb, this->_increment);
}

nts::Tristate nts::CounterComponent::compute(std::size_t pin)
{
    if (pin == 8 || pin == 16 || pin > this->_nbPins)
        return nts::Undefined;
    return this->getValue(pin);
}
