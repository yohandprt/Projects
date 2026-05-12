/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Adder.cpp
*/

#include "AdderComponent.hpp"

nts::Tristate nts::AdderComponent::addTriBin(nts::Tristate b1, nts::Tristate b2, nts::Tristate &ci)
{
    if (b1 == nts::Undefined || b2 == nts::Undefined || ci == nts::Undefined)
        return nts::Undefined;
    if (!b1 && !b2) {
        if (ci) {
            ci = nts::False;
            return addTriBin(nts::False, nts::True, ci);
        }
        return nts::False;
    } else if ((b1 && !b2) || (!b1 && b2)) {
        if (ci) {
            ci = nts::False;
            return addTriBin(nts::True, nts::True, ci);
        }
        return nts::True;
    } else {
        if (ci) {
            return nts::True;
        }
        ci = nts::True;
        return nts::False;
    }
}

std::vector<nts::Tristate> nts::AdderComponent::addVecTriBin(std::vector<nts::Tristate> triBin1, std::vector<nts::Tristate> triBin2)
{
    nts::AdderComponent adder;
    std::size_t len = triBin1.size();
    std::vector<nts::Tristate> result {len};
    nts::Tristate ci = nts::False;
    std::vector<nts::Tristate> errorResult = {
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

    for (std::size_t i = len - 1; i < triBin1.size(); i--) {
        if (triBin1[i] == nts::Undefined || triBin2[i] == nts::Undefined)
            return errorResult;
        result[i] = adder.addTriBin(triBin1[i], triBin2[i], ci);
    }
    return result;
}

nts::Tristate nts::AdderComponent::compute(std::size_t pin)
{
    if (pin == 8 || pin == 16 || pin > this->_nbPins)
        return nts::Undefined;
    
    nts::Tristate b1 = getLink(7);
    nts::Tristate b2 = getLink(6);
    nts::Tristate ci = getLink(9);
    nts::Tristate result = this->addTriBin(b1, b2, ci);;

    if (pin == 10)
        return result;
    result = this->addTriBin(getLink(5), getLink(4), ci);
    if (pin == 11)
        return result;
    result = this->addTriBin(getLink(3), getLink(2), ci);
    if (pin == 12)
        return result;
    result = this->addTriBin(getLink(1), getLink(15), ci);
    if (pin == 13)
        return result;
    if (pin == 14)
        return ci;
    else
        return this->getLink(pin);
}