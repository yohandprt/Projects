/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Logger.cpp
*/

#include "LoggerComponent.hpp"

void nts::LoggerComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (!(this->getLink(9) == nts::True && this->getLink(10) == nts::False) || this->getLink(10) == nts::Undefined)
        return;

    this->_triBin = {
        this->getLink(8),
        this->getLink(7),
        this->getLink(6),
        this->getLink(5),
        this->getLink(4),
        this->getLink(3),
        this->getLink(2),
        this->getLink(1)
    };

    std::size_t bin = this->_utils.triBinToBin(this->_triBin);
    std::size_t dec;

    if (bin == 0 || bin == static_cast<std::size_t>(-1))
        return;
    dec = this->_utils.binToDec(bin, 8);
    std::ofstream logfile("log.bin", std::ios_base::app);
    logfile << static_cast<char>(dec);
    logfile.close();
}