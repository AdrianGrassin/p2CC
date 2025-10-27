#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "State.h"
#include "Alphabet.h"
#include "Transition.h"
#include "Tape.h"

/**
 * Representa una Máquina de Turing completa
 */
class TuringMachine {
private:
    // Componentes de la MT
    std::set<State> states;                    // Q (conjunto de estados)
    Alphabet inputAlphabet;                    // Σ (alfabeto de entrada)
    Alphabet tapeAlphabet;                     // Γ (alfabeto de cinta)
    State initialState;                        // q0
    std::set<State> acceptanceStates;          // F (conjunto de estados de aceptación)
    int numberOfTapes;                         // Número de cintas (1 para monocinta)
    
    // Función de transición: mapa de (estado, símbolo(s)) -> Transition
    std::map<std::pair<std::string, std::string>, Transition> transitions;
    
    // Estado de ejecución
    State currentState;
    std::vector<Tape*> tapes;                  // Cintas (1 o más)
    int stepCount;
    bool isAccepted;
    bool hasHalted;

public:
    /**
     * Constructor de TuringMachine
     */
    TuringMachine();

    /**
     * Destructor
     */
    ~TuringMachine();

    // Métodos para construir la MT
    void addState(const State& state);
    void addInputSymbol(const std::string& symbol);
    void addTapeSymbol(const std::string& symbol);
    void setInitialState(const State& state);
    void setBlankSymbol(const std::string& symbol);
    void addAcceptanceState(const State& state);
    void addTransition(const Transition& transition);
    void setNumberOfTapes(int n);  // Nuevo: establecer número de cintas

    // Métodos de ejecución
    void initialize(const std::string& input);
    bool executeStep();
    bool execute(const std::string& input, int maxSteps = 10000);
    void reset();

    // Métodos de consulta
    const State& getCurrentState() const;
    const State& getInitialState() const;
    const Alphabet& getInputAlphabet() const;
    const Alphabet& getTapeAlphabet() const;
    const std::set<State>& getStates() const;
    const std::set<State>& getAcceptanceStates() const;
    const std::map<std::pair<std::string, std::string>, Transition>& getTransitions() const;
    int getStepCount() const;
    int getNumberOfTapes() const;  // Nuevo
    bool isMultiTape() const;      // Nuevo
    bool isHalted() const;
    bool wasAccepted() const;
    std::string getTapeContent() const;
    std::string getTapeContent(int tapeIndex) const;  // Nuevo: obtener cinta específica
    int getHeadPosition() const;
    int getHeadPosition(int tapeIndex) const;  // Nuevo: posición de cabezal específico

    // Métodos de validación
    bool isValidInput(const std::string& input) const;
    bool validateTransition(const std::string& state, const std::string& symbol) const;
    bool hasState(const std::string& stateName) const;

    // Método para obtener información
    std::string getConfiguration() const;
    std::string toString() const;

private:
    /**
     * Aplica una transición
     */
    bool applyTransition();
};

#endif // TURING_MACHINE_H
