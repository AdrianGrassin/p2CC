#include "../include/MTSimulator.h"
#include "../include/MTParser.h"
#include <iostream>
#include <iomanip>

/**
 * Constructor de MTSimulator
 */
MTSimulator::MTSimulator() : machine(nullptr) {
}

/**
 * Destructor
 */
MTSimulator::~MTSimulator() {
    if (machine != nullptr) {
        delete machine;
    }
}

/**
 * Carga una máquina de Turing desde un archivo
 */
bool MTSimulator::loadMachine(const std::string& filename) {
    if (machine != nullptr) {
        delete machine;
    }

    machine = MTParser::parseFile(filename);
    return machine != nullptr;
}

/**
 * Ejecuta la máquina con una entrada específica
 */
bool MTSimulator::run(const std::string& input, int maxSteps) {
    if (machine == nullptr) {
        std::cerr << "Error: No hay máquina cargada" << std::endl;
        return false;
    }

    executionTrace.clear();
    
    // Inicializar la máquina
    machine->initialize(input);
    recordStep();  // Registrar estado inicial

    // Ejecutar paso a paso y registrar cada paso
    for (int i = 0; i < maxSteps && !machine->isHalted(); i++) {
        if (!machine->executeStep()) {
            break;
        }
        recordStep();  // Registrar después de cada paso
    }

    return machine->wasAccepted();
}

/**
 * Ejecuta la máquina paso a paso
 */
bool MTSimulator::step() {
    if (machine == nullptr) {
        std::cerr << "Error: No hay máquina cargada" << std::endl;
        return false;
    }

    recordStep();
    return machine->executeStep();
}

/**
 * Obtiene la traza de ejecución
 */
const std::vector<std::string>& MTSimulator::getExecutionTrace() const {
    return executionTrace;
}

/**
 * Imprime el estado actual
 */
void MTSimulator::printCurrentState() const {
    if (machine == nullptr) {
        std::cout << "No hay máquina cargada" << std::endl;
        return;
    }

    std::cout << "\n--- Estado Actual ---" << std::endl;
    std::cout << machine->getConfiguration() << std::endl;
    std::cout << visualizeTape() << std::endl;
}

/**
 * Imprime la traza de ejecución
 */
void MTSimulator::printExecutionTrace() const {
    std::cout << "\n=== Traza de Ejecución ===" << std::endl;
    for (size_t i = 0; i < executionTrace.size(); i++) {
        std::cout << "Paso " << i << ": " << executionTrace[i] << std::endl;
    }
}

/**
 * Imprime solo el estado inicial y final
 */
void MTSimulator::printSummaryTrace() const {
    std::cout << "\n=== Traza de Ejecución ===" << std::endl;
    if (!executionTrace.empty()) {
        std::cout << "Paso 0 (inicial): " << executionTrace.front() << std::endl;
        if (executionTrace.size() > 1) {
            std::cout << "Paso " << (executionTrace.size() - 1) << " (final): " << executionTrace.back() << std::endl;
        }
    }
}

/**
 * Imprime el resultado final
 */
void MTSimulator::printResult() const {
    if (machine == nullptr) {
        std::cout << "No hay máquina cargada" << std::endl;
        return;
    }

    std::cout << "\n=== Resultado ===" << std::endl;
    std::cout << "Pasos totales: " << machine->getStepCount() << std::endl;
    std::cout << "Resultado: " << (machine->wasAccepted() ? "ACEPTA" : "RECHAZA") << std::endl;
    
    if (machine->isMultiTape()) {
        std::cout << "Cintas finales:" << std::endl;
        for (int i = 0; i < machine->getNumberOfTapes(); i++) {
            std::cout << "  Cinta " << (i + 1) << ": [" << machine->getTapeContent(i) << "]" << std::endl;
        }
    } else {
        std::cout << "Cinta final: [" << machine->getTapeContent() << "]" << std::endl;
    }
    
    std::cout << "Estado final: " << machine->getCurrentState().getName() << std::endl;
}

/**
 * Imprime información de la máquina
 */
void MTSimulator::printMachineInfo() const {
    if (machine == nullptr) {
        std::cout << "No hay máquina cargada" << std::endl;
        return;
    }

    std::cout << machine->toString();
}

void MTSimulator::recordStep() {
    if (machine == nullptr) return;

    std::string config = machine->getConfiguration();
    executionTrace.push_back(config);
}

std::string MTSimulator::visualizeTape() const {
    if (machine == nullptr) return "";

    std::string visualization = "Cinta: ";
    std::string content = machine->getTapeContent();
    int headPos = machine->getHeadPosition();

    visualization += "[";
    for (int i = 0; i < (int)content.size(); i++) {
        if (i == headPos) {
            visualization += "|" + std::string(1, content[i]) + "|";
        } else {
            visualization += content[i];
        }
    }
    visualization += "]";

    return visualization;
}
