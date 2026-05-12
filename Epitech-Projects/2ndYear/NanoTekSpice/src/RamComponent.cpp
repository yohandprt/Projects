/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** RamComponent.cpp
*/

#include "RamComponent.hpp"

nts::RamComponent::RamComponent() : nts::AComponent(24, "4801")
{
    this->_address = 0;
    this->_undefinedValue = true;
    this->_content = {0};
    this->_content.resize(1024);
}

nts::Tristate nts::RamComponent::getValue(std::size_t idxBit)
{
    if (this->_undefinedValue)
        return nts::Undefined;
    if (getLink(18) != nts::False)
        return nts::Undefined;
    if (getLink(20) != nts::False && getLink(21) != nts::False)
        return nts::Undefined;
    if (getLink(21) == nts::False)
        return nts::Undefined;

    std::string strBit = std::to_string(this->_content[this->_address]);

    if (idxBit >= strBit.size())
        return nts::True;

    if (strBit[idxBit] == '0')
        return nts::True;
    return nts::False;
}

void nts::RamComponent::write()
{
    std::vector<nts::Tristate> triBin = {
        this->getLinkByType(17, "input"),
        this->getLinkByType(16, "input"),
        this->getLinkByType(15, "input"),
        this->getLinkByType(14, "input"),
        this->getLinkByType(13, "input"),
        this->getLinkByType(11, "input"),
        this->getLinkByType(10, "input"),
        this->getLinkByType(9, "input")
    };
    std::size_t bin = this->_utils.triBinToBin(triBin);

    this->_content[this->_address] = bin;
}

void nts::RamComponent::simulate(std::size_t tick)
{
    (void)tick;
    std::size_t bin = 0;
    std::vector<nts::Tristate> triBin = {
        getLink(22),
        getLink(23),
        getLink(1),
        getLink(2),
        getLink(3),
        getLink(4),
        getLink(5),
        getLink(6),
        getLink(7),
        getLink(8)
    };
    this->_undefinedValue = false;
    for (std::size_t i = 0; i < 10; i++) {
        if (triBin[i] == nts::Undefined)
            this->_undefinedValue = true;
    }
    bin = this->_utils.triBinToBin(triBin);
    this->_address = this->_utils.binToDec(bin, 11);

    if (getLink(21) == nts::False && getLink(18) == nts::False)
        this->write();
}

nts::Tristate nts::RamComponent::compute(std::size_t pin)
{
    if (pin == 12 || pin == 19 || pin == 24 || pin > this->_nbPins)
        return nts::Undefined;

    if (pin == 17)
        return this->getValue(7);
    else if (pin == 16)
        return this->getValue(6);
    else if (pin == 15)
        return this->getValue(5);
    else if (pin == 14)
        return this->getValue(4);
    else if (pin == 13)
        return this->getValue(3);
    else if (pin == 11)
        return this->getValue(2);
    else if (pin == 10)
        return this->getValue(1);
    else if (pin == 9)
        return this->getValue(0);
    else
        return this->getLink(pin);
}

nts::Tristate nts::RamComponent::getLinkByType(std::size_t pin, const std::string &type)
{
    nts::Tristate state = nts::Undefined;

    for (auto &link : this->_links[pin]) {
        if (dynamic_cast<nts::AComponent &>(link.getComponent()).getType() == type)
            state = link.getComponent().compute(link.getPin());
    }
    return state;
}