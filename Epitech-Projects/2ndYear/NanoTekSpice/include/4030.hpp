/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4030.hpp
*/

#ifndef NTS_4030
    #define NTS_4030

    #include "AComponent.hpp"

namespace nts {
    class nts4030Component : public nts::AComponent
    {
    public:
        nts4030Component() : nts::AComponent(14, "4030") {};
        virtual ~nts4030Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif