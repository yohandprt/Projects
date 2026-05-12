/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ClockComponent.hpp
*/

#ifndef NTS_CLOCK
    #define NTS_CLOCK

    #include "AComponent.hpp"

namespace nts {
    class ClockComponent : public nts::AComponent
    {
    private:
        nts::Tristate _lastStatus;
    public:
        ClockComponent();
        virtual ~ClockComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif