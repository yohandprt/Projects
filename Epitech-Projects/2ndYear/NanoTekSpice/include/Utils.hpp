/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Utils.hpp
*/

#ifndef NTS_UTILS
    #define NTS_UTILS

    #include <iostream>
    #include <vector>
    #include <cmath>

    #include "IComponent.hpp"

namespace nts {
    class Utils
    {
    public:
        Utils() = default;
        ~Utils() = default;

        std::size_t triBinToBin(std::vector<nts::Tristate> triBin);
        std::size_t binToDec(std::size_t bin, std::size_t nbBits);
    };
}

#endif