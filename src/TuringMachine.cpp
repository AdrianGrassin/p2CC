#include "../include/TuringMachine.h"
#include <iostream>

/**
 * Constructor de TuringMachine
 */
TuringMachine::TuringMachine()
    : initialState(State()), numberOfTapes(1), currentState(State()),
      stepCount(0), isAccepted(false), hasHalted(false) {
    tapes.resize(1, nullptr);
}

/**
 * Destructor
 */
TuringMachine::~TuringMachine() {
    for (auto tape : tapes) {
        if (tape != nullptr) {
            delete tape;
        }
    }
    tapes.clear();
}

// Métodos para construir la MT
void TuringMachine::addState(const State& state) {
    states.insert(state);
}

void TuringMachine::addInputSymbol(const std::string& symbol) {
    inputAlphabet.addSymbol(symbol);
}

void TuringMachine::addTapeSymbol(const std::string& symbol) {
    tapeAlphabet.addSymbol(symbol);
}

void TuringMachine::setInitialState(const State& state) {
    initialState = state;
    initialState.setInitial(true);
    // No agregar automáticamente a states - debe estar ya definido en Q
}

void TuringMachine::setBlankSymbol(const std::string& symbol) {
    tapeAlphabet.setBlankSymbol(symbol);
    tapeAlphabet.addSymbol(symbol);
}

void TuringMachine::addAcceptanceState(const State& state) {
    State acceptState = state;
    acceptState.setAcceptance(true);
    acceptanceStates.insert(acceptState);
    // No agregar automáticamente a states - debe estar ya definido en Q
}

void TuringMachine::addTransition(const Transition& transition) {
    // Para multicinta, crear clave con todos los símbolos separados por |
    std::string symbolKey;
    const auto& readSymbols = transition.getReadSymbols();
    for (size_t i = 0; i < readSymbols.size(); i++) {
        symbolKey += readSymbols[i];
        if (i < readSymbols.size() - 1) symbolKey += "|";
    }
    
    std::pair<std::string, std::string> key = 
        {transition.getCurrentState().getName(), symbolKey};
    transitions[key] = transition;
}

void TuringMachine::setNumberOfTapes(int n) {
    numberOfTapes = (n < 1) ? 1 : n;
    // Limpiar cintas antiguas si existen
    for (auto tape : tapes) {
        if (tape != nullptr) {
            delete tape;
        }
    }
    tapes.clear();
    tapes.resize(numberOfTapes, nullptr);
}

// Métodos de ejecución
void TuringMachine::initialize(const std::string& input) {
    currentState = initialState;
    stepCount = 0;
    isAccepted = false;
    hasHalted = false;
    
    // Limpiar cintas antiguas
    for (auto tape : tapes) {
        if (tape != nullptr) {
            delete tape;
        }
    }
    
    std::string blank = tapeAlphabet.getBlankSymbol();
    // Crear cintas
    for (int i = 0; i < numberOfTapes; i++) {
        if (i == 0) {
            // La primera cinta contiene la entrada
            tapes[i] = new Tape(input, blank, &tapeAlphabet);
        } else {
            // Las demás cintas empiezan vacías
            tapes[i] = new Tape("", blank, &tapeAlphabet);
        }
    }
}

bool TuringMachine::executeStep() {
    if (hasHalted) {
        return false;
    }
    
    bool success = applyTransition();
    if (success) {
        stepCount++;
        
        // Verificar si se llegó a un estado de aceptación
        if (acceptanceStates.find(currentState) != acceptanceStates.end()) {
            isAccepted = true;
            hasHalted = true;
        }
    }
    
    return success;
}

bool TuringMachine::execute(const std::string& input, int maxSteps) {
    initialize(input);
    
    for (int i = 0; i < maxSteps && !hasHalted; i++) {
        if (!executeStep()) {
            break;
        }
    }
    
    return isAccepted;
}

void TuringMachine::reset() {
    currentState = initialState;
    stepCount = 0;
    isAccepted = false;
    hasHalted = false;
    for (auto tape : tapes) {
        if (tape != nullptr) {
            delete tape;
        }
    }
    tapes.clear();
    tapes.resize(numberOfTapes, nullptr);
}

// Métodos de consulta
const State& TuringMachine::getCurrentState() const {
    return currentState;
}

const State& TuringMachine::getInitialState() const {
    return initialState;
}

const Alphabet& TuringMachine::getInputAlphabet() const {
    return inputAlphabet;
}

const Alphabet& TuringMachine::getTapeAlphabet() const {
    return tapeAlphabet;
}

const std::set<State>& TuringMachine::getStates() const {
    return states;
}

const std::set<State>& TuringMachine::getAcceptanceStates() const {
    return acceptanceStates;
}

const std::map<std::pair<std::string, std::string>, Transition>& TuringMachine::getTransitions() const {
    return transitions;
}

int TuringMachine::getStepCount() const {
    return stepCount;
}

int TuringMachine::getNumberOfTapes() const {
    return numberOfTapes;
}

bool TuringMachine::isMultiTape() const {
    return numberOfTapes > 1;
}

bool TuringMachine::isHalted() const {
    return hasHalted;
}

bool TuringMachine::wasAccepted() const {
    return isAccepted;
}

std::string TuringMachine::getTapeContent() const {
    return getTapeContent(0);
}

std::string TuringMachine::getTapeContent(int tapeIndex) const {
    if (tapeIndex >= 0 && tapeIndex < numberOfTapes && tapes[tapeIndex] != nullptr) {
        return tapes[tapeIndex]->getVisibleContent();
    }
    return "";
}

int TuringMachine::getHeadPosition() const {
    return getHeadPosition(0);
}

int TuringMachine::getHeadPosition(int tapeIndex) const {
    if (tapeIndex >= 0 && tapeIndex < numberOfTapes && tapes[tapeIndex] != nullptr) {
        return tapes[tapeIndex]->getHeadPosition();
    }
    return -1;
}

// Métodos de validación
bool TuringMachine::isValidInput(const std::string& input) const {
    return inputAlphabet.isValidString(input);
}

bool TuringMachine::validateTransition(const std::string& state, const std::string& symbol) const {
    std::pair<std::string, std::string> key = {state, symbol};
    return transitions.find(key) != transitions.end();
}

bool TuringMachine::hasState(const std::string& stateName) const {
    for (const auto& state : states) {
        if (state.getName() == stateName) {
            return true;
        }
    }
    return false;
}

// Método para obtener información
std::string TuringMachine::getConfiguration() const {
    std::string config = "Estado: " + currentState.getName();
    if (isMultiTape()) {
        config += "\n";
        for (int i = 0; i < numberOfTapes; i++) {
            config += "Cinta " + std::to_string(i + 1) + ": [" + getTapeContent(i) + "], " +
                     "Cabezal: " + std::to_string(getHeadPosition(i));
            if (i < numberOfTapes - 1) config += "\n";
        }
    } else {
        config += ", Cinta: [" + getTapeContent() + "], Cabezal: " + 
                 std::to_string(getHeadPosition());
    }
    return config;
}

std::string TuringMachine::toString() const {
    std::string result = "=== Máquina de Turing";
    if (isMultiTape()) {
        result += " (" + std::to_string(numberOfTapes) + " cintas)";
    }
    result += " ===\n";
    result += "Estados: " + std::to_string(states.size()) + "\n";
    result += "Alfabeto entrada: " + inputAlphabet.toString() + "\n";
    result += "Alfabeto cinta: " + tapeAlphabet.toString() + "\n";
    result += "Estado inicial: " + initialState.getName() + "\n";
    
    // Estados de aceptación
    result += "Estados aceptación: { ";
    bool first = true;
    for (const auto& state : acceptanceStates) {
        if (!first) result += ", ";
        result += state.getName();
        first = false;
    }
    result += " }\n";
    
    result += "Transiciones: " + std::to_string(transitions.size()) + "\n";
    return result;
}

// Método privado
bool TuringMachine::applyTransition() {
    // Leer símbolos de todas las cintas
    std::string symbolKey;
    for (int i = 0; i < numberOfTapes; i++) {
        symbolKey += tapes[i]->read();
        if (i < numberOfTapes - 1) symbolKey += "|";
    }
    
    std::pair<std::string, std::string> key = {currentState.getName(), symbolKey};
    
    // Buscar transición
    auto it = transitions.find(key);
    if (it == transitions.end()) {
        // No hay transición válida
        hasHalted = true;
        return false;
    }
    
    // Aplicar transición
    const Transition& trans = it->second;
    const auto& writeSymbols = trans.getWriteSymbols();
    const auto& directions = trans.getDirections();
    
    // Escribir y mover en cada cinta
    for (int i = 0; i < numberOfTapes; i++) {
        tapes[i]->write(writeSymbols[i]);
        
        char dir = directions[i];
        if (dir == 'R') {
            tapes[i]->moveRight();
        } else if (dir == 'L') {
            tapes[i]->moveLeft();
        }
        // Si dir == 'S', el cabezal no se mueve
    }
    
    currentState = trans.getNextState();
    
    return true;
}
