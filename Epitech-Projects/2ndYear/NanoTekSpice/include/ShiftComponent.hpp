/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** ShiftComponent.hpp
*/

#ifndef NTS_SHIFT
    #define NTS_SHIFT

    #include "AComponent.hpp"

    #include <vector>

namespace nts {
    class ShiftComponent : public nts::AComponent
    {
    private:
        std::vector<nts::Tristate> _lastValues;
        std::vector<nts::Tristate> _currentValues;
    public:
        ShiftComponent();
        virtual ~ShiftComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
    };
    
}

#endif