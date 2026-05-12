/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Utils.cpp
*/

#include "Utils.hpp"

std::size_t nts::Utils::triBinToBin(std::vector<nts::Tristate> triBin)
{
    std::size_t bin = 0;

    for (nts::Tristate status : triBin) {
        if (!status && bin == 0)
            continue;
        bin *= 10;
        if (status)
            bin += 1;
        else if (status == nts::Undefined)
            return -1;
    }
    return bin;
}

std::size_t nts::Utils::binToDec(std::size_t bin, std::size_t nbBits)
{
    std::string zeros = "";
    std::string strBin = std::to_string(bin);
    std::size_t len = strBin.size();
    std::size_t dec = 0;

    if (len != nbBits) {
        for (std::size_t i = 0; i < nbBits - len; i++)
            zeros.append("0");
    }
    strBin = zeros + strBin;
    len = nbBits;
    for (std::size_t i = 0; strBin[i]; i++) {
        dec += ((strBin[i] - '0') * static_cast<std::size_t>(std::pow(2, (len - 1))));
        len--;
    }
    return dec;
}