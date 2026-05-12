/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** SelectorComponent.hpp
*/

#ifndef NTS_SELECTOR
    #define NTS_SELECTOR

    #include "AComponent.hpp"

namespace nts {
    class SelectorComponent : public nts::AComponent
    {
    private:
    public:
        SelectorComponent() : nts::AComponent(15, "4512") {};
        virtual ~SelectorComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate getValue();
    };
}

#endif