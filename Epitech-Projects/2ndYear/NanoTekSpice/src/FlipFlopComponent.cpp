/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** FlipFlopComponent.cpp
*/

#include "FlipFlopComponent.hpp"

nts::FlipFlopComponent::FlipFlopComponent() : nts::AComponent(13, "4013") {
    this->_Q1 = nts::Undefined;
    this->_QP1 = nts::Undefined;
    this->_Q2 = nts::Undefined;
    this->_QP2 = nts::Undefined;
}

void nts::FlipFlopComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (getLink(3) == nts::True && getLink(5) == nts::False && getLink(4) == nts::False && getLink(6) == nts::False) {
        this->_Q1 = nts::False;
        this->_QP1 = nts::True;
    } else if (getLink(3) == nts::True && getLink(5) == nts::True && getLink(4) == nts::False && getLink(6) == nts::False) {
        this->_Q1 = nts::True;
        this->_QP1 = nts::False;
    } else if (getLink(3) == nts::False && getLink(4) == nts::False && getLink(6) == nts::False) {
        return;
    } else if (getLink(4) == nts::True && getLink(6) == nts::False) {
        this->_Q1 = nts::False;
        this->_QP1 = nts::True;
    } else if (getLink(4) == nts::False && getLink(6) == nts::True) {
        this->_Q1 = nts::True;
        this->_QP1 = nts::False;
    } else if (getLink(4) == nts::True && getLink(6) == nts::True) {
        this->_Q1 = nts::True;
        this->_QP1 = nts::True;
    }


    if (getLink(11) == nts::True && getLink(9) == nts::False && getLink(10) == nts::False && getLink(8) == nts::False) {
        this->_Q2 = nts::False;
        this->_QP2 = nts::True;
    } else if (getLink(11) == nts::True && getLink(9) == nts::True && getLink(10) == nts::False && getLink(8) == nts::False) {
        this->_Q2 = nts::True;
        this->_QP2 = nts::False;
    } else if (getLink(11) == nts::False && getLink(10) == nts::False && getLink(8) == nts::False) {
        return;
    } else if (getLink(10) == nts::True && getLink(8) == nts::False) {
        this->_Q2 = nts::False;
        this->_QP2 = nts::True;
    } else if (getLink(10) == nts::False && getLink(8) == nts::True) {
        this->_Q2 = nts::True;
        this->_QP2 = nts::False;
    } else if (getLink(10) == nts::True && getLink(8) == nts::True) {
        this->_Q2 = nts::True;
        this->_QP2 = nts::True;
    }
}

nts::Tristate nts::FlipFlopComponent::compute(std::size_t pin)
{
    if (pin > this->_nbPins)
        return nts::Undefined;
    if (pin == 1) {
        return this->_Q1;
    } else if (pin == 2) {
        return this->_QP1;
    } else if (pin == 13) {
        return this->_Q2;
    } else if (pin == 12) {
        return this->_QP2;
    } else
        return getLink(pin);
}
