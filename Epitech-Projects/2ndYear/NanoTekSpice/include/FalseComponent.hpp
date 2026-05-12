/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** FalseComponent.hpp
*/

#ifndef NTS_FALSE
    #define NTS_FALSE

    #include "AComponent.hpp"

namespace nts {
    class FalseComponent : public nts::AComponent
    {
    public:
        FalseComponent() : nts::AComponent(1, "false") {this->_status = nts::False;};
        virtual ~FalseComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
    
}

#endif