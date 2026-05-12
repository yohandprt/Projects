/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4011.hpp
*/

#ifndef NTS_4011
    #define NTS_4011

    #include "AComponent.hpp"

namespace nts {
    class nts4011Component : public nts::AComponent
    {
    public:
        nts4011Component() : nts::AComponent(14, "4011") {};
        virtual ~nts4011Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif