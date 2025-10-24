#include "../include/TuringMachine.h"
#include <iostream>

/**
 * Constructor de TuringMachine
 */
TuringMachine::TuringMachine()
    : initialState(State()), currentState(State()), tape(nullptr), stepCount(0), 
      isAccepted(false), hasHalted(false) {
}

/**
 * Destructor
 */
TuringMachine::~TuringMachine() {
    if (tape != nullptr) {
        delete tape;
    }
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
    std::pair<std::string, std::string> key = 
        {transition.getCurrentState().getName(), transition.getReadSymbol()};
    transitions[key] = transition;
}

// Métodos de ejecución
void TuringMachine::initialize(const std::string& input) {
    currentState = initialState;
    stepCount = 0;
    isAccepted = false;
    hasHalted = false;
    
    if (tape != nullptr) {
        delete tape;
    }
    tape = new Tape(input, tapeAlphabet.getBlankSymbol(), &tapeAlphabet);
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
    if (tape != nullptr) {
        delete tape;
        tape = nullptr;
    }
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

bool TuringMachine::isHalted() const {
    return hasHalted;
}

bool TuringMachine::wasAccepted() const {
    return isAccepted;
}

std::string TuringMachine::getTapeContent() const {
    if (tape != nullptr) {
        return tape->getVisibleContent();
    }
    return "";
}

int TuringMachine::getHeadPosition() const {
    if (tape != nullptr) {
        return tape->getHeadPosition();
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
    if (tape != nullptr) {
        config += ", Cinta: [" + tape->getVisibleContent() + "], Cabezal: " + 
                 std::to_string(tape->getHeadPosition());
    }
    return config;
}

std::string TuringMachine::toString() const {
    std::string result = "=== Máquina de Turing ===\n";
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
    std::string readSymbol = tape->read();
    std::pair<std::string, std::string> key = {currentState.getName(), readSymbol};
    
    // Buscar transición
    auto it = transitions.find(key);
    if (it == transitions.end()) {
        // No hay transición válida
        hasHalted = true;
        return false;
    }
    
    // Aplicar transición
    const Transition& trans = it->second;
    tape->write(trans.getWriteSymbol());
    currentState = trans.getNextState();
    
    if (trans.getDirection() == 'R') {
        tape->moveRight();
    } else if (trans.getDirection() == 'L') {
        tape->moveLeft();
    }
    
    return true;
}
