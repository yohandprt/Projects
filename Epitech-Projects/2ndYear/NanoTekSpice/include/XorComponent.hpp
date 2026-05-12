/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** XorComponent.hpp
*/

#ifndef NTS_XOR
    #define NTS_XOR

    #include "AComponent.hpp"

namespace nts {
    class XorComponent : public nts::AComponent
    {
    public:
        XorComponent() : nts::AComponent(3, "xor") {};
        virtual ~XorComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
}

#endif