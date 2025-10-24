#include "../include/State.h"

/**
 * Constructor por defecto
 */
State::State() : name(""), isInitial(false), isAcceptance(false) {
}

/**
 * Constructor con nombre
 */
State::State(const std::string& stateName) 
    : name(stateName), isInitial(false), isAcceptance(false) {
}

/**
 * Constructor completo
 */
State::State(const std::string& stateName, bool initial, bool acceptance)
    : name(stateName), isInitial(initial), isAcceptance(acceptance) {
}

// Getters
std::string State::getName() const {
    return name;
}

bool State::isInitialState() const {
    return isInitial;
}

bool State::isAcceptanceState() const {
    return isAcceptance;
}

// Setters
void State::setName(const std::string& stateName) {
    name = stateName;
}

void State::setInitial(bool initial) {
    isInitial = initial;
}

void State::setAcceptance(bool acceptance) {
    isAcceptance = acceptance;
}

// Operadores de comparación
bool State::operator==(const State& other) const {
    return name == other.name;
}

bool State::operator!=(const State& other) const {
    return !(*this == other);
}

bool State::operator<(const State& other) const {
    return name < other.name;
}

// Método auxiliar
std::string State::toString() const {
    std::string result = name;
    if (isInitial) result += " (inicial)";
    if (isAcceptance) result += " (aceptación)";
    return result;
}
