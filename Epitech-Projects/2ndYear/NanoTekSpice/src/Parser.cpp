/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

std::deque<std::string> nts::Parser::split(std::string line, char delimiter)
{
    std::istringstream iss(line);
    std::deque<std::string> linkParts;
    std::string part;

    while (getline(iss, part, delimiter))
        linkParts.push_back(part);
    return linkParts;
}

std::string nts::Parser::trim(std::string str)
{
    std::size_t left = str.find_first_not_of(" \t\r\n");
    if (left == std::string::npos)
        return "";

    std::size_t right = str.find_last_not_of(" \t\r\n");
    return str.substr(left, right - left + 1);
}

std::size_t nts::Parser::to_size_t(std::string strNb)
{
    std::stringstream ss(strNb);
    std::size_t nb;

    ss >> nb;
    return nb;
}

void nts::Parser::parseChipsets(std::unique_ptr<nts::Circuit>& circuit, std::istringstream& iss)
{
    ComponentFactory creator;
    std::unique_ptr<nts::IComponent> component;
    std::string type;
    std::string name;

    iss >> type >> name;

    if (name.empty())
        throw nts::Parser::Error("CHIPSETS: Undefined name of component.");

    if (circuit->containsComponent(name))
        throw nts::Parser::Error("CHIPSETS: Multiple definition of variable '" + name + "'.");

    component = creator.createComponent(type);
    if (component == nullptr)
        throw nts::Parser::Error("CHIPSETS: Unknown type '" + type + "'.");

    if (type == "input" || type == "clock")
        circuit->addInput(std::move(component), name);
    else if (type == "output")
        circuit->addOutput(std::move(component), name);
    else
        circuit->addGate(std::move(component), name);
}

void nts::Parser::parseLinks(std::unique_ptr<nts::Circuit>& circuit, std::istringstream& iss)
{
    std::deque<std::string> linkPartsSrc;
    std::deque<std::string> linkPartsDest;
    std::string linkSrc;
    std::string linkDest;
    std::string cSrc;
    std::string cDest;
    std::string pinSrc;
    std::string pinDest;

    iss >> linkSrc >> linkDest;

    linkPartsSrc = this->split(linkSrc, ':');
    linkPartsDest = this->split(linkDest, ':');

    if (linkPartsSrc.size() != 2 || linkPartsDest.size() != 2)
        throw nts::Parser::Error("LINKS: Syntax error.");

    cSrc = linkPartsSrc[0];
    pinSrc = linkPartsSrc[1];

    cDest = linkPartsDest[0];
    pinDest = linkPartsDest[1];

    if (!circuit->containsComponent(cSrc))
        throw nts::Parser::Error("LINKS: Unknown component name '" + cSrc + "'.");
    if (!circuit->containsComponent(cDest))
        throw nts::Parser::Error("LINKS: Unknown component name '" + cDest + "'.");

    circuit->getComponent(cSrc)->setLink(this->to_size_t(pinSrc), *circuit->getComponent(cDest), this->to_size_t(pinDest));
    circuit->getComponent(cDest)->setLink(this->to_size_t(pinDest), *circuit->getComponent(cSrc), this->to_size_t(pinSrc));
}

std::unique_ptr<nts::IComponent> nts::Parser::parse()
{
    std::unique_ptr<nts::Circuit> circuit = std::make_unique<nts::Circuit>();
    std::ifstream file(this->_filename);
    std::string line;
    nts::Parts part = nts::Parts::COMMENTS;
    bool noComponents = false;

    while (getline(file, line)) {
        if (line.empty() || this->trim(line)[0] == '#')
            continue;
        if (line.substr(0, 10) != ".chipsets:" && line.substr(0, 7) != ".links:" && part == nts::Parts::COMMENTS)
            throw nts::Parser::Error("COMMENTS: Syntax error.");
        if (line == ".links:") {
            if (noComponents)
                throw nts::Parser::Error("LINKS: No component have been initialized.");
            if (part != nts::Parts::CHIPSETS)
                throw nts::Parser::Error("LINKS: Declaration of links before chipsets.");
            part = nts::LINKS;
            continue;
        }
        if (line == ".chipsets:") {
            noComponents = true;
            if (part == nts::Parts::CHIPSETS)
                throw nts::Parser::Error("CHIPSETS: Multiple definition of chipsets.");
            else if (part == nts::Parts::LINKS)
                throw nts::Parser::Error("CHIPSETS: Declaration of chipsets after links.");
            part = nts::Parts::CHIPSETS;
            continue;
        } else
            noComponents = false;

        std::istringstream iss(line);

        if (part == nts::Parts::CHIPSETS)
            this->parseChipsets(circuit, iss);

        if (part == nts::Parts::LINKS)
            this->parseLinks(circuit, iss);
    }
    if (part == nts::Parts::COMMENTS)
        throw nts::Parser::Error("CHIPSETS: Chipsets undefined.");
    return circuit;
}