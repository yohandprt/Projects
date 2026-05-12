/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** JohnsonComponent.cpp
*/

#include "JohnsonComponent.hpp"

nts::JohnsonComponent::JohnsonComponent() : nts::AComponent(15, "4017")
{
    this->_currentNb = {
        {3, nts::Undefined},
        {2, nts::Undefined},
        {4, nts::Undefined},
        {7, nts::Undefined},
        {10, nts::Undefined},
        {1, nts::Undefined},
        {5, nts::Undefined},
        {6, nts::Undefined},
        {9, nts::Undefined},
        {11, nts::Undefined},
        {12, nts::Undefined}
    };
    this->_cpt = 0;
    this->_undefinedValue = true;
}

nts::Tristate nts::JohnsonComponent::getValue(std::size_t pin)
{
    if (this->_cpt == 0 || this->_undefinedValue || getLink(15) == nts::True)
        return this->_currentNb[pin];

    if (pin == 12) {
        if (this->_cpt <= 5)
            return nts::True;
        else
            return nts::False;
    }

    if (this->_cpt == 1 && pin == 3)
        return nts::True;
    else if (this->_cpt == 2 && pin == 2)
        return nts::True;
    else if (this->_cpt == 3 && pin == 4)
        return nts::True;
    else if (this->_cpt == 4 && pin == 7)
        return nts::True;
    else if (this->_cpt == 5 && pin == 10)
        return nts::True;
    else if (this->_cpt == 6 && pin == 1)
        return nts::True;
    else if (this->_cpt == 7 && pin == 5)
        return nts::True;
    else if (this->_cpt == 8 && pin == 6)
        return nts::True;
    else if (this->_cpt == 9 && pin == 9)
        return nts::True;
    else if (this->_cpt == 10 && pin == 11)
        return nts::True;
    else
        return nts::False;
}

void nts::JohnsonComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (getLink(15) == nts::True) {
        this->_cpt = 0;
        for (std::size_t i = 0; i < this->_currentNb.size(); i++)
            this->_currentNb[i] = nts::False;
        return;
    }
    if (getLink(13) == nts::Undefined || getLink(14) == nts::Undefined) {
        this->_undefinedValue = true;
        return;
    } else if (!(getLink(14) == nts::True && getLink(13) == nts::False))
        return;
    this->_undefinedValue = false;
    if (this->_cpt == 10)
        this->_cpt = 1;
    else
        this->_cpt++;
}

nts::Tristate nts::JohnsonComponent::compute(std::size_t pin)
{
    if (pin > this->_nbPins)
        return nts::Undefined;

    if (pin == 14 || pin == 13 || pin == 15)
        return this->getLink(pin);
    else
        return this->getValue(pin);
}