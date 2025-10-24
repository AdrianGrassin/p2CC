#ifndef MT_SIMULATOR_H
#define MT_SIMULATOR_H

#include <string>
#include <vector>
#include "TuringMachine.h"

/**
 * Ejecutor y visualizador del simulador de Máquinas de Turing
 * Maneja la interfaz de usuario y la salida
 */
class MTSimulator {
private:
    TuringMachine* machine;
    std::vector<std::string> executionTrace;

public:
    /**
     * Constructor de MTSimulator
     */
    MTSimulator();

    /**
     * Destructor
     */
    ~MTSimulator();

    /**
     * Carga una máquina de Turing desde un archivo
     */
    bool loadMachine(const std::string& filename);

    /**
     * Ejecuta la máquina con una entrada específica
     */
    bool run(const std::string& input, int maxSteps = 10000);

    /**
     * Ejecuta la máquina paso a paso (una transición por llamada)
     */
    bool step();

    /**
     * Obtiene la traza completa de ejecución
     */
    const std::vector<std::string>& getExecutionTrace() const;

    /**
     * Imprime el estado actual de la máquina
     */
    void printCurrentState() const;

    /**
     * Imprime la traza completa de ejecución
     */
    void printExecutionTrace() const;

    /**
     * Imprime solo el estado inicial y final de la ejecución
     */
    void printSummaryTrace() const;

    /**
     * Imprime el resultado final
     */
    void printResult() const;

    /**
     * Imprime toda la información de la máquina
     */
    void printMachineInfo() const;

private:
    /**
     * Agrega una entrada a la traza
     */
    void recordStep();

    /**
     * Crea una representación visual de la cinta
     */
    std::string visualizeTape() const;
};

#endif // MT_SIMULATOR_H
