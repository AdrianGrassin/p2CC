#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>
#include "State.h"

/**
 * Representa una transición en la Máquina de Turing
 * Formato: δ(estado_actual, símbolo_leído) = (estado_siguiente, símbolo_escrito, dirección)
 */
class Transition {
private:
    State currentState;
    std::string readSymbol;
    State nextState;
    std::string writeSymbol;
    char direction;  // 'R' (derecha) o 'L' (izquierda)

public:
    /**
     * Constructor por defecto
     */
    Transition();

    /**
     * Constructor de Transition
     */
    Transition(const State& current, const std::string& read,
               const State& next, const std::string& write, char dir);

    // Getters
    const State& getCurrentState() const;
    std::string getReadSymbol() const;
    const State& getNextState() const;
    std::string getWriteSymbol() const;
    char getDirection() const;

    // Métodos auxiliares
    std::string toString() const;
};

#endif // TRANSITION_H
