/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** NotComponent.hpp
*/

#ifndef NTS_NOT
    #define NTS_NOT

    #include "AComponent.hpp"

namespace nts {
    class NotComponent : public nts::AComponent
    {
    public:
        NotComponent() : nts::AComponent(2, "not") {};
        virtual ~NotComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif