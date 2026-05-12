/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4071.hpp
*/

#ifndef NTS_4071
    #define NTS_4071

    #include "AComponent.hpp"

namespace nts {
    class nts4071Component : public nts::AComponent
    {
    public:
        nts4071Component() : nts::AComponent(14, "4071") {};
        virtual ~nts4071Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif