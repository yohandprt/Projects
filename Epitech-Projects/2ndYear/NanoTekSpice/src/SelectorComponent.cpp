/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** SelectorComponent.cpp
*/

#include "SelectorComponent.hpp"

nts::Tristate nts::SelectorComponent::getValue()
{
    if (getLink(13) == nts::False && getLink(12) == nts::False && getLink(11) == nts::False)
        return getLink(1);
    else if (getLink(13) == nts::False && getLink(12) == nts::False && getLink(11) == nts::True)
        return getLink(2);
    else if (getLink(13) == nts::False && getLink(12) == nts::True && getLink(11) == nts::False)
        return getLink(3);
    else if (getLink(13) == nts::False && getLink(12) == nts::True && getLink(11) == nts::True)
        return getLink(4);
    else if (getLink(13) == nts::True && getLink(12) == nts::False && getLink(11) == nts::False)
        return getLink(5);
    else if (getLink(13) == nts::True && getLink(12) == nts::False && getLink(11) == nts::True)
        return getLink(6);
    else if (getLink(13) == nts::True && getLink(12) == nts::True && getLink(11) == nts::False)
        return getLink(7);
    else if (getLink(13) == nts::True && getLink(12) == nts::True && getLink(11) == nts::True)
        return getLink(9);
    else
        return nts::Undefined;
}

nts::Tristate nts::SelectorComponent::compute(std::size_t pin)
{
    if (pin > this->_nbPins)
        return nts::Undefined;
    
    if (getLink(15) == nts::True)
        return nts::Undefined;
    else if (getLink(10) == nts::True)
        return nts::False;
    else if (pin != 14)
        return getLink(pin);
    else
        return this->getValue();
    
}