/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OrComponent.hpp
*/

#ifndef NTS_OR
    #define NTS_OR

    #include "AComponent.hpp"

namespace nts {
    class OrComponent : public nts::AComponent
    {
    public:
        OrComponent() : nts::AComponent(3, "or") {};
        virtual ~OrComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif