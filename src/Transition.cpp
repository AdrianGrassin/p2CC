#include "../include/Transition.h"

/**
 * Constructor por defecto
 */
Transition::Transition()
    : currentState(State()), readSymbol(""), nextState(State()), 
      writeSymbol(""), direction('R') {
}

/**
 * Constructor de Transition
 */
Transition::Transition(const State& current, const std::string& read,
                       const State& next, const std::string& write, char dir)
    : currentState(current), readSymbol(read), nextState(next), 
      writeSymbol(write), direction(dir) {
}

// Getters
const State& Transition::getCurrentState() const {
    return currentState;
}

std::string Transition::getReadSymbol() const {
    return readSymbol;
}

const State& Transition::getNextState() const {
    return nextState;
}

std::string Transition::getWriteSymbol() const {
    return writeSymbol;
}

char Transition::getDirection() const {
    return direction;
}

std::string Transition::toString() const {
    std::string dir = (direction == 'R') ? "RIGHT" : "LEFT";
    return currentState.getName() + " " + readSymbol + " -> " + 
           nextState.getName() + " " + writeSymbol + " " + dir;
}
