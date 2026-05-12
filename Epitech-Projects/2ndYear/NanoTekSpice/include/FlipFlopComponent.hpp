/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** FlipFlopComponent.hpp
*/

#ifndef NTS_FLIPFLOP
    #define NTS_FLIPFLOP

    #include "AComponent.hpp"

namespace nts {
    class FlipFlopComponent : public nts::AComponent
    {
    public:
        FlipFlopComponent();
        virtual ~FlipFlopComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
        virtual void simulate(std::size_t tick) override;
    private:
        nts::Tristate _Q1;
        nts::Tristate _QP1;
        nts::Tristate _Q2;
        nts::Tristate _QP2;
    };
}

#endif