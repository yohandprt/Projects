/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4081.hpp
*/

#ifndef NTS_4081
    #define NTS_4081

    #include "AComponent.hpp"

namespace nts {
    class nts4081Component : public nts::AComponent
    {
    public:
        nts4081Component() : nts::AComponent(14, "4081") {};
        virtual ~nts4081Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif