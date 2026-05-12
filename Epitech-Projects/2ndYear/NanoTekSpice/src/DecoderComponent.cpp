/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** DecoderComponent.cpp
*/
;
#include "DecoderComponent.hpp"

nts::DecoderComponent::DecoderComponent() : nts::AComponent(24, "4514")
{
    this->_currentOutputs = {
        {11, nts::Undefined},
        {9, nts::Undefined},
        {10, nts::Undefined},
        {8, nts::Undefined},
        {7, nts::Undefined},
        {6, nts::Undefined},
        {5, nts::Undefined},
        {4, nts::Undefined},
        {18, nts::Undefined},
        {17, nts::Undefined},
        {20, nts::Undefined},
        {19, nts::Undefined},
        {14, nts::Undefined},
        {13, nts::Undefined},
        {16, nts::Undefined},
        {15, nts::Undefined}
    };
}

nts::Tristate nts::DecoderComponent::getValue(std::size_t pin, nts::Tristate DValue, nts::Tristate CValue, nts::Tristate BValue, nts::Tristate AValue)
{
    if (this->getLink(1) == nts::False || this->getLink(1) == nts::Undefined)
        return this->_currentOutputs[pin];

    if (this->getLink(23) == nts::True) {
        for (auto &pair : this->_currentOutputs)
            pair.second = nts::False;
        return nts::False;
    }
    if (this->getLink(22) == nts::Undefined || this->getLink(21) == nts::Undefined || this->getLink(3) == nts::Undefined || this->getLink(2) == nts::Undefined) {
        // for (auto &pair : this->_currentOutputs)
        //     pair.second = nts::Undefined;
        // return nts::Undefined;
        return this->_currentOutputs[pin];
    }

    if (this->getLink(22) == DValue && this->getLink(21) == CValue && this->getLink(3) == BValue && this->getLink(2) == AValue)
        this->_currentOutputs[pin] = nts::True;
    else
        this->_currentOutputs[pin] = nts::False;
    return this->_currentOutputs[pin];
}

nts::Tristate nts::DecoderComponent::compute(std::size_t pin)
{
    if (pin == 12 || pin == 24 || pin > this->_nbPins)
        return nts::Undefined;

    if (pin == 11)
        return this->getValue(11, nts::False, nts::False, nts::False, nts::False);
    else if (pin == 9)
        return this->getValue(9, nts::False, nts::False, nts::False, nts::True);
    else if (pin == 10)
        return this->getValue(10, nts::False, nts::False, nts::True, nts::False);
    else if (pin == 8)
        return this->getValue(8, nts::False, nts::False, nts::True, nts::True);
    else if (pin == 7)
        return this->getValue(7, nts::False, nts::True, nts::False, nts::False);
    else if (pin == 6)
        return this->getValue(6, nts::False, nts::True, nts::False, nts::True);
    else if (pin == 5)
        return this->getValue(5, nts::False, nts::True, nts::True, nts::False);
    else if (pin == 4)
        return this->getValue(4, nts::False, nts::True, nts::True, nts::True);
    else if (pin == 18)
        return this->getValue(18, nts::True, nts::False, nts::False, nts::False);
    else if (pin == 17)
        return this->getValue(17, nts::True, nts::False, nts::False, nts::True);
    else if (pin == 20)
        return this->getValue(20, nts::True, nts::False, nts::True, nts::False);
    else if (pin == 19)
        return this->getValue(19, nts::True, nts::False, nts::True, nts::True);
    else if (pin == 14)
        return this->getValue(14, nts::True, nts::True, nts::False, nts::False);
    else if (pin == 13)
        return this->getValue(13, nts::True, nts::True, nts::False, nts::True);
    else if (pin == 16)
        return this->getValue(16, nts::True, nts::True, nts::True, nts::False);
    else if (pin == 15)
        return this->getValue(15, nts::True, nts::True, nts::True, nts::True);
    else
        return this->getLink(pin);
}