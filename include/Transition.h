#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>
#include <vector>
#include "State.h"

/**
 * Representa una transición en la Máquina de Turing
 * Soporta tanto monocinta como multicinta
 * Formato monocinta: δ(estado_actual, símbolo_leído) = (estado_siguiente, símbolo_escrito, dirección)
 * Formato multicinta: δ(estado_actual, [s1,...,sk]) = (estado_siguiente, [w1,...,wk], [d1,...,dk])
 */
class Transition {
private:
    State currentState;
    std::vector<std::string> readSymbols;   // Para multicinta (monocinta usa solo [0])
    State nextState;
    std::vector<std::string> writeSymbols;  // Para multicinta (monocinta usa solo [0])
    std::vector<char> directions;           // Para multicinta (monocinta usa solo [0])

public:
    /**
     * Constructor por defecto
     */
    Transition();

    /**
     * Constructor de Transition monocinta
     */
    Transition(const State& current, const std::string& read,
               const State& next, const std::string& write, char dir);

    /**
     * Constructor de Transition multicinta
     */
    Transition(const State& current, const std::vector<std::string>& read,
               const State& next, const std::vector<std::string>& write, 
               const std::vector<char>& dir);

    // Getters monocinta (compatibilidad)
    const State& getCurrentState() const;
    std::string getReadSymbol() const;
    const State& getNextState() const;
    std::string getWriteSymbol() const;
    char getDirection() const;

    // Getters multicinta
    const std::vector<std::string>& getReadSymbols() const;
    const std::vector<std::string>& getWriteSymbols() const;
    const std::vector<char>& getDirections() const;
    int getNumTapes() const;
    bool isMultiTape() const;

    // Métodos auxiliares
    std::string toString() const;
};

#endif // TRANSITION_H
