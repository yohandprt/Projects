/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Link.hpp
*/

#ifndef NTS_LINK
    #define NTS_LINK

    #include <iostream>

    #include "IComponent.hpp"

namespace nts {
    class Link
    {
    private:
        std::size_t _pin;
        nts::IComponent &_component;
    public:
        Link(std::size_t pin, nts::IComponent &component) : _pin(pin), _component(component) {};
        ~Link() = default;

        nts::IComponent &getComponent();
        std::size_t getPin() const;
    };    
}


#endif