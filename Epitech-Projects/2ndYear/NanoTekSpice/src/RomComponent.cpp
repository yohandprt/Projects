/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** RomComponent.cpp
*/

#include "RomComponent.hpp"

nts::RomComponent::RomComponent() : nts::AComponent(23, "2716")
{
    std::ifstream file("./rom.bin", std::ios::binary);
    long long int len = 0;

    this->_address = 0;
    this->_undefinedValue = true;

    if (!file)
        this->_content = {0};
    else {
        file.seekg(0, std::ios::end);
        len = file.tellg();
        file.seekg(0, std::ios::beg);
        this->_content.resize(len);
        file.read(reinterpret_cast<char *>(this->_content.data()), len);
    }
}

nts::Tristate nts::RomComponent::getValue(std::size_t idxBit)
{
    if (this->_undefinedValue)
        return nts::Undefined;
    if (getLink(18) != nts::False && getLink(20) != nts::False)
        return nts::Undefined;
    std::size_t bit = (this->_content[this->_address] >> idxBit) & 1;

    if (bit == 0)
        return nts::False;
    return nts::True;
}

void nts::RomComponent::simulate(std::size_t tick)
{
    (void)tick;
    std::size_t bin = 0;
    std::vector<nts::Tristate> triBin = {
        getLink(19),
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
    for (std::size_t i = 0; i < 11; i++) {
        if (triBin[i] == nts::Undefined)
            this->_undefinedValue = true;
    }
    bin = this->_utils.triBinToBin(triBin);
    this->_address = this->_utils.binToDec(bin, 11);
}

nts::Tristate nts::RomComponent::compute(std::size_t pin)
{
    if (pin == 12 || pin == 19 || pin == 21 || pin == 24 || pin > this->_nbPins)
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