/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** TrueComponent.hpp
*/

#ifndef NTS_TRUE
    #define NTS_TRUE

    #include "AComponent.hpp"

namespace nts {
    class TrueComponent : public nts::AComponent
    {
    public:
        TrueComponent() : nts::AComponent(1, "true") {this->_status = nts::True;};
        virtual ~TrueComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
    };
    
}

#endif