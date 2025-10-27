#include "../include/Transition.h"

/**
 * Constructor por defecto
 */
Transition::Transition()
    : currentState(State()) {
    readSymbols.push_back("");
    writeSymbols.push_back("");
    directions.push_back('R');
}

/**
 * Constructor de Transition monocinta
 */
Transition::Transition(const State& current, const std::string& read,
                       const State& next, const std::string& write, char dir)
    : currentState(current), nextState(next) {
    readSymbols.push_back(read);
    writeSymbols.push_back(write);
    directions.push_back(dir);
}

/**
 * Constructor de Transition multicinta
 */
Transition::Transition(const State& current, const std::vector<std::string>& read,
                       const State& next, const std::vector<std::string>& write, 
                       const std::vector<char>& dir)
    : currentState(current), readSymbols(read), nextState(next), 
      writeSymbols(write), directions(dir) {
}

// Getters monocinta (compatibilidad)
const State& Transition::getCurrentState() const {
    return currentState;
}

std::string Transition::getReadSymbol() const {
    return readSymbols.empty() ? "" : readSymbols[0];
}

const State& Transition::getNextState() const {
    return nextState;
}

std::string Transition::getWriteSymbol() const {
    return writeSymbols.empty() ? "" : writeSymbols[0];
}

char Transition::getDirection() const {
    return directions.empty() ? 'R' : directions[0];
}

// Getters multicinta
const std::vector<std::string>& Transition::getReadSymbols() const {
    return readSymbols;
}

const std::vector<std::string>& Transition::getWriteSymbols() const {
    return writeSymbols;
}

const std::vector<char>& Transition::getDirections() const {
    return directions;
}

int Transition::getNumTapes() const {
    return readSymbols.size();
}

bool Transition::isMultiTape() const {
    return readSymbols.size() > 1;
}

std::string Transition::toString() const {
    if (isMultiTape()) {
        std::string result = currentState.getName() + " [";
        for (size_t i = 0; i < readSymbols.size(); i++) {
            result += readSymbols[i];
            if (i < readSymbols.size() - 1) result += ",";
        }
        result += "] -> " + nextState.getName() + " [";
        for (size_t i = 0; i < writeSymbols.size(); i++) {
            result += writeSymbols[i];
            if (i < writeSymbols.size() - 1) result += ",";
        }
        result += "] [";
        for (size_t i = 0; i < directions.size(); i++) {
            result += directions[i];
            if (i < directions.size() - 1) result += ",";
        }
        result += "]";
        return result;
    } else {
        std::string dir = (directions[0] == 'R') ? "RIGHT" : "LEFT";
        return currentState.getName() + " " + readSymbols[0] + " -> " + 
               nextState.getName() + " " + writeSymbols[0] + " " + dir;
    }
}
