#include <iostream>
#include <string>
#include <vector>
#include "../include/MTSimulator.h"
#include "../include/MTException.h"

/**
 * Programa principal del simulador de Máquinas de Turing
 * Soporta tanto máquinas monocinta como multicinta automáticamente
 */
int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Uso: " << argv[0] << " <archivo_MT> <entrada1> [entrada2] ... [-t]" << std::endl;
            std::cerr << "  -t: Muestra la traza completa de ejecución (para todas las entradas)" << std::endl;
            std::cerr << "Ejemplos:" << std::endl;
            std::cerr << "  " << argv[0] << " data/Ejemplo_MT.txt \"0101\" \"11\"" << std::endl;
            std::cerr << "  " << argv[0] << " data/MTproposed/mt_copiar.txt \"101\" -t" << std::endl;
            return 1;
        }

        std::string mtFile = argv[1];
        std::vector<std::string> inputs;
        bool showFullTrace = false;

        // Procesar argumentos
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-t") {
                showFullTrace = true;
            } else {
                // Si no es un flag, es una cadena de entrada
                inputs.push_back(arg);
            }
        }

        MTSimulator simulator;

        // Cargar la máquina de Turing (detecta automáticamente mono/multicinta)
        if (!simulator.loadMachine(mtFile)) {
            std::cerr << "Error: No se pudo cargar la máquina de Turing desde: " << mtFile << std::endl;
            return 1;
        }

        std::cout << "Máquina de Turing cargada exitosamente." << std::endl;
        simulator.printMachineInfo();

        // Ejecutar con las entradas
        if (!inputs.empty()) {
            for (const std::string& input : inputs) {
                std::cout << "\n=================================================" << std::endl;
                std::cout << "Ejecutando con entrada: \"" << input << "\"" << std::endl;
                
                simulator.run(input); 
                
                if (showFullTrace) {
                    simulator.printExecutionTrace();
                } else {
                    simulator.printSummaryTrace();
                }               
                simulator.printResult();
                std::cout << "=================================================\n" << std::endl;
            }
        } else {
            std::cout << "No se proporcionó ninguna cadena de entrada." << std::endl;
        }

        return 0;
        
    } catch (const MTException& e) {
        std::cerr << "\nError de validación: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\nError inesperado: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\nError desconocido" << std::endl;
        return 1;
    }
}