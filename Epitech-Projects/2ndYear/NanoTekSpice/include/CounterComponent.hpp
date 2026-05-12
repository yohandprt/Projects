/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** CounterComponent.hpp
*/

#ifndef NTS_COUNTER
    #define NTS_COUNTER

    #include <vector>

    #include "AComponent.hpp"
    #include "AdderComponent.hpp"

namespace nts {
    class CounterComponent : public nts::AComponent
    {
    private:
        nts::AdderComponent _adder;
        std::vector<nts::Tristate> _currentNb;
        std::vector<nts::Tristate> _increment;
    public:
        CounterComponent();
        virtual ~CounterComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
        nts::Tristate getValue(std::size_t pin);
    };
}

#endif