/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** InputComponent.hpp
*/

#ifndef NTS_INPUT
    #define NTS_INPUT

    #include "AComponent.hpp"

namespace nts {
    class InputComponent : public nts::AComponent
    {
    public:
        InputComponent() : nts::AComponent(1, "input") {};
        virtual ~InputComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
    };
    
}

#endif