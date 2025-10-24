#ifndef STATE_H
#define STATE_H

#include <string>

/**
 * Representa un estado en la Máquina de Turing
 */
class State {
private:
    std::string name;
    bool isInitial;
    bool isAcceptance;

public:
    /**
     * Constructor por defecto
     */
    State();

    /**
     * Constructor con nombre
     */
    explicit State(const std::string& stateName);

    /**
     * Constructor completo
     */
    State(const std::string& stateName, bool initial, bool acceptance);

    // Getters
    std::string getName() const;
    bool isInitialState() const;
    bool isAcceptanceState() const;

    // Setters
    void setName(const std::string& stateName);
    void setInitial(bool initial);
    void setAcceptance(bool acceptance);

    // Operadores de comparación
    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
    bool operator<(const State& other) const;  // Para usar en std::set y std::map

    // Método auxiliar
    std::string toString() const;
};

#endif // STATE_H
