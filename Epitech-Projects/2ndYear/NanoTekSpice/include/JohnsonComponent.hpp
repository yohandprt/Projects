/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** JohnsonComponent.hpp
*/

#ifndef NTS_JOHNSON
    #define NTS_JOHNSON

    #include "AComponent.hpp"
    #include "Utils.hpp"

    #include <map>

namespace nts {
    class JohnsonComponent : public nts::AComponent
    {
    private:
        std::map<std::size_t, nts::Tristate> _currentNb;
        std::size_t _cpt;
        bool _undefinedValue;
    public:
        JohnsonComponent();
        virtual ~JohnsonComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate getValue(std::size_t pin);
    };
}

#endif