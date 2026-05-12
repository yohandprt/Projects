/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OutputComponent.hpp
*/

#ifndef NTS_OUTPUT
    #define NTS_OUTPUT

    #include "AComponent.hpp"

namespace nts {
    class OutputComponent : public nts::AComponent
    {
    public:
        OutputComponent() : nts::AComponent(1, "output") {};
        virtual ~OutputComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}


#endif