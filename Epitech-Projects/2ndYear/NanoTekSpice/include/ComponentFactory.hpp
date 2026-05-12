/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-tekspice-22
** File description:
** ComponentFactory.hpp
*/

#ifndef NTS_COMPONENT_FACTORY
    #define NTS_COMPONENT_FACTORY

    #include <memory>
    #include <functional>
    #include <map>

    #include "IComponent.hpp"
    #include "InputComponent.hpp"
    #include "OutputComponent.hpp"
    #include "TrueComponent.hpp"
    #include "FalseComponent.hpp"
    #include "ClockComponent.hpp"
    #include "LoggerComponent.hpp"
    #include "AndComponent.hpp"
    #include "OrComponent.hpp"
    #include "XorComponent.hpp"
    #include "NotComponent.hpp"
    #include "AdderComponent.hpp"
    #include "CounterComponent.hpp"
    #include "DecoderComponent.hpp"
    #include "FlipFlopComponent.hpp"
    #include "RomComponent.hpp"
    #include "RamComponent.hpp"
    #include "JohnsonComponent.hpp"
    #include "SelectorComponent.hpp"
    #include "ShiftComponent.hpp"
    #include "4001.hpp"
    #include "4011.hpp"
    #include "4030.hpp"
    #include "4069.hpp"
    #include "4071.hpp"
    #include "4081.hpp"

namespace nts {
    class ComponentFactory
    {
    private:
        std::unique_ptr<nts::IComponent> createInput() const;
        std::unique_ptr<nts::IComponent> createOutput() const;
        std::unique_ptr<nts::IComponent> createTrue() const;
        std::unique_ptr<nts::IComponent> createFalse() const;
        std::unique_ptr<nts::IComponent> createClock() const;
        std::unique_ptr<nts::IComponent> createLogger() const;

        std::unique_ptr<nts::IComponent> createAnd() const;
        std::unique_ptr<nts::IComponent> createOr() const;
        std::unique_ptr<nts::IComponent> createXor() const;
        std::unique_ptr<nts::IComponent> createNot() const;

        std::unique_ptr<nts::IComponent> create2716() const;
        std::unique_ptr<nts::IComponent> create4001() const;
        std::unique_ptr<nts::IComponent> create4008() const;
        std::unique_ptr<nts::IComponent> create4011() const;
        std::unique_ptr<nts::IComponent> create4013() const;
        std::unique_ptr<nts::IComponent> create4017() const;
        std::unique_ptr<nts::IComponent> create4030() const;
        std::unique_ptr<nts::IComponent> create4040() const;
        std::unique_ptr<nts::IComponent> create4069() const;
        std::unique_ptr<nts::IComponent> create4071() const;
        std::unique_ptr<nts::IComponent> create4081() const;
        std::unique_ptr<nts::IComponent> create4094() const;
        std::unique_ptr<nts::IComponent> create4512() const;
        std::unique_ptr<nts::IComponent> create4514() const;
        std::unique_ptr<nts::IComponent> create4801() const;
    public:
        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
    };
}

#endif
