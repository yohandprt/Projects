/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AndComponent.hpp
*/

#ifndef NTS_AND
    #define NTS_AND

    #include "AComponent.hpp"

namespace nts {
    class AndComponent : public nts::AComponent
    {
    public:
        AndComponent() : nts::AComponent(3, "and") {};
        virtual ~AndComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif