/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-tekspice-22
** File description:
** ComponentFactory.cpp
*/

#include "ComponentFactory.hpp"

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createInput() const
{
    return std::make_unique<nts::InputComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createOutput() const
{
    return std::make_unique<nts::OutputComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createTrue() const
{
    return std::make_unique<nts::TrueComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createFalse() const
{
    return std::make_unique<nts::FalseComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createClock() const
{
    return std::make_unique<nts::ClockComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createLogger() const
{
    return std::make_unique<nts::LoggerComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createAnd() const
{
    return std::make_unique<nts::AndComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createOr() const
{
    return std::make_unique<nts::OrComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createXor() const
{
    return std::make_unique<nts::XorComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createNot() const
{
    return std::make_unique<nts::NotComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create2716() const
{
    return std::make_unique<nts::RomComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4001() const
{
    return std::make_unique<nts::nts4001Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4008() const
{
    return std::make_unique<nts::AdderComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4011() const
{
    return std::make_unique<nts::nts4011Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4013() const
{
    return std::make_unique<nts::FlipFlopComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4017() const
{
    return std::make_unique<nts::JohnsonComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4030() const
{
    return std::make_unique<nts::nts4030Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4040() const
{
    return std::make_unique<nts::CounterComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4069() const
{
    return std::make_unique<nts::nts4069Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4071() const
{
    return std::make_unique<nts::nts4071Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4081() const
{
    return std::make_unique<nts::nts4081Component>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4094() const
{
    return std::make_unique<nts::ShiftComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4512() const
{
    return std::make_unique<nts::SelectorComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4514() const
{
    return std::make_unique<nts::DecoderComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4801() const
{
    return std::make_unique<nts::RamComponent>();
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createComponent(const std::string &type)
{
    using func = std::function<std::unique_ptr<nts::IComponent>()>;

    std::map<std::string, func> creators = {
        {"input", [this]() {return ComponentFactory::createInput();}},
        {"output", [this]() {return ComponentFactory::createOutput();}},
        {"true", [this]() {return ComponentFactory::createTrue();}},
        {"false", [this]() {return ComponentFactory::createFalse();}},
        {"clock", [this]() {return ComponentFactory::createClock();}},
        {"logger", [this]() {return ComponentFactory::createLogger();}},
        {"and", [this]() {return ComponentFactory::createAnd();}},
        {"or", [this]() {return ComponentFactory::createOr();}},
        {"xor", [this]() {return ComponentFactory::createXor();}},
        {"not", [this]() {return ComponentFactory::createNot();}},
        {"2716", [this]() {return ComponentFactory::create2716();}},
        {"4001", [this]() {return ComponentFactory::create4001();}},
        {"4008", [this]() {return ComponentFactory::create4008();}},
        {"4011", [this]() {return ComponentFactory::create4011();}},
        {"4013", [this]() {return ComponentFactory::create4013();}},
        {"4017", [this]() {return ComponentFactory::create4017();}},
        {"4030", [this]() {return ComponentFactory::create4030();}},
        {"4040", [this]() {return ComponentFactory::create4040();}},
        {"4069", [this]() {return ComponentFactory::create4069();}},
        {"4071", [this]() {return ComponentFactory::create4071();}},
        {"4081", [this]() {return ComponentFactory::create4081();}},
        {"4094", [this]() {return ComponentFactory::create4094();}},
        {"4512", [this]() {return ComponentFactory::create4512();}},
        {"4514", [this]() {return ComponentFactory::create4514();}},
        {"4801", [this]() {return ComponentFactory::create4801();}},
    };

    if (creators[type])
        return creators[type]();
    return nullptr;
}
