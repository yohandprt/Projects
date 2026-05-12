/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

nts::AComponent::AComponent(std::size_t nbPins, std::string type) : _nbPins(nbPins), _type(type)
{
    this->_status = nts::Undefined;
    this->_futurStatus = nts::Undefined;
    this->_modification = false;
}

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::AComponent::compute(std::size_t pin)
{
    (void)pin;
    return this->_status;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 0 || pin > this->_nbPins)
        return;
    this->_links[pin].push_back(Link(otherPin, other));
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    nts::Tristate state = nts::Undefined;

    for (auto &link : this->_links[pin])
        state = link.getComponent().compute(link.getPin());
    return state;
}

nts::Tristate nts::AComponent::getLink(std::size_t pin, std::vector<nts::IComponent *> &visited)
{
    nts::Tristate state = nts::Undefined;

    if (!this->_modification)
        return nts::Undefined;

    for (auto &link : this->_links[pin]) {
        nts::IComponent *component = &link.getComponent();

        if (std::find(visited.begin(), visited.end(), component) != visited.end())
            continue;
        visited.push_back(component);
        state = (*component).compute(link.getPin());
    }
    return state;
}

nts::Tristate nts::AComponent::getStatus() const
{
    return this->_status;
}

std::string& nts::AComponent::getType()
{
    return this->_type;
}

void nts::AComponent::setStatus(nts::Tristate status)
{
    this->_status = status;
}

void nts::AComponent::setFuturStatus(nts::Tristate status)
{
    this->_futurStatus = status;
}

void nts::AComponent::setTempStatus(nts::Tristate status)
{
    this->_tempStatus = status;
}

void nts::AComponent::hasBeenModified()
{
    this->_modification = true;
}

nts::Tristate operator&&(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::Undefined && b == nts::Undefined)
        return nts::Undefined;
    else if ((a == nts::True && b == nts::Undefined) || (a == nts::Undefined && b == nts::True))
        return nts::Undefined;
    else if (a == nts::True && b == nts::True)
        return nts::True;
    else
        return nts::False;
}

nts::Tristate operator||(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::Undefined && b == nts::Undefined)
        return nts::Undefined;
    else if ((a == nts::Undefined && b == nts::False) || (a == nts::False && b == nts::Undefined))
        return nts::Undefined;
    else if (a == nts::True || b == nts::True)
        return nts::True;
    else
        return nts::False;
}

nts::Tristate operator^(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::Undefined || b == nts::Undefined)
        return nts::Undefined;
    else if (a == nts::True && b == nts::False)
        return nts::True;
    else if (a == nts::False && b == nts::True)
        return nts::True;
    else
        return nts::False;
}

nts::Tristate operator!(nts::Tristate a)
{
    if (a == nts::True)
        return nts::False;
    else if (a == nts::False)
        return nts::True;
    else
        return nts::Undefined;
}