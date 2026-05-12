/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4069.hpp
*/

#ifndef NTS_4069
    #define NTS_4069

    #include "AComponent.hpp"

namespace nts {
    class nts4069Component : public nts::AComponent
    {
    public:
        nts4069Component() : nts::AComponent(14, "4069") {};
        virtual ~nts4069Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif