/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Circuit.cpp
*/

#include "Circuit.hpp"

void nts::Circuit::simulate(std::size_t tick)
{
    this->_currentTick += tick;
    for (std::size_t i = 0; i < this->_orderedComponentNames.size(); i++)
        this->getComponent(this->_orderedComponentNames[i])->simulate(tick);
}

nts::Tristate nts::Circuit::compute(std::size_t pin)
{
    return this->getComponent(this->_orderedComponentNames[this->_orderedComponentNames.size() - 1])->compute(pin);
}

void nts::Circuit::addInput(std::shared_ptr<nts::IComponent> component, std::string name)
{
    if (this->_inputs.find(name) != this->_inputs.end())
        return;
    this->_inputs.insert({name, std::move(component)});
    this->_orderedComponentNames.push_back(name);
}

void nts::Circuit::addOutput(std::shared_ptr<nts::IComponent> component, std::string name)
{
    if (this->_outputs.find(name) != this->_outputs.end())
        return;
    this->_outputs[name] = std::move(component);
    this->_orderedComponentNames.push_back(name);
}

void nts::Circuit::addGate(std::shared_ptr<nts::IComponent> component, std::string name)
{
    if (this->_gates.find(name) != this->_gates.end())
        return;
    this->_gates[name] = std::move(component);
    this->_orderedComponentNames.push_back(name);
}

std::shared_ptr<nts::IComponent> nts::Circuit::getComponent(const std::string &name)
{
    if (this->_inputs.find(name) != this->_inputs.end())
        return this->_inputs[name];
    else if (this->_outputs.find(name) != this->_outputs.end())
        return this->_outputs[name];
    else if (this->_gates.find(name) != this->_gates.end())
        return this->_gates[name];
    return nullptr;
}

bool nts::Circuit::isInput(const std::string &name)
{
    for (auto [key, value] : this->_inputs) {
        if (key == name)
            return true;
    }
    return false;
}

bool nts::Circuit::containsComponent(const std::string &name)
{
    for (auto key : this->_orderedComponentNames) {
        if (key == name)
            return true;
    }
    return false;
}

void nts::Circuit::display()
{
    std::map<std::string, std::shared_ptr<nts::IComponent>>::const_iterator it;
    std::cout <<
    "tick: " << this->_currentTick << std::endl <<
    "input(s):" << std::endl;
    for (it = this->_inputs.begin(); it != this->_inputs.end(); it++)
        std::cout << "  " << it->first << ": " << it->second->compute(1) << std::endl;
    std::cout <<
    "output(s):" << std::endl;
    for (it = this->_outputs.begin(); it != this->_outputs.end(); it++)
        std::cout << "  " << it->first << ": " << it->second->compute(1) << std::endl;
}

void nts::Circuit::instantiate(const std::string &name, nts::Tristate state)
{
    std::shared_ptr<nts::IComponent> component = this->getComponent(name);

    if (component == nullptr)
        return;
    for (const std::string &compName : this->_orderedComponentNames) {
        std::shared_ptr<nts::IComponent> comp = this->getComponent(compName);
        if (comp)
            dynamic_cast<nts::AComponent *>(comp.get())->hasBeenModified();
    }
    dynamic_cast<nts::AComponent *>(component.get())->setFuturStatus(state);
    dynamic_cast<nts::AComponent *>(component.get())->setTempStatus(nts::Undefined);
}

void nts::Circuit::loop()
{
    while (true) {
        this->simulate(1);
        this->display();
    }
}

std::ostream& operator<<(std::ostream& s, nts::Tristate v)
{
    if (v == nts::Undefined)
        s << "U";
    else if (v == nts::True)
        s << "1";
    else if (v == nts::False)
        s << "0";
    return s;
}
