#include "../include/MTParser.h"
#include "../include/MTException.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * Parsea un archivo y retorna una Máquina de Turing
 */
TuringMachine* MTParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw MTException("No se pudo abrir el archivo: " + filename);
    }

    TuringMachine* tm = new TuringMachine();
    std::string line;
    int lineNumber = 0;

    // Función auxiliar para leer la siguiente línea no vacía/no comentario
    auto getNextValidLine = [&](std::string& outLine) -> bool {
        while (std::getline(file, outLine)) {
            lineNumber++;
            outLine = trim(outLine);
            if (!isCommentOrEmpty(outLine)) {
                return true;
            }
        }
        return false;
    };

    // Línea 1: Estados
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        for (const auto& token : tokens) {
            tm->addState(State(token));
        }
    }

    // Línea 2: Alfabeto de entrada
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        for (const auto& token : tokens) {
            tm->addInputSymbol(token);
        }
    }

    // Línea 3: Alfabeto de cinta
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        for (const auto& token : tokens) {
            tm->addTapeSymbol(token);
        }
    }

    // Línea 4: Estado inicial
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        if (!tokens.empty()) {
            tm->setInitialState(State(tokens[0], true, false));
        }
    }

    // Línea 5: Símbolo blanco
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        if (!tokens.empty()) {
            std::string blanco = tokens[0];
            
            if (!tm->getTapeAlphabet().contains(blanco)) {
                throw MTException("Error de validación: El símbolo blanco '" + blanco + 
                    "' no está incluido en el alfabeto de cinta (Γ) definido en la línea 3.");
                }

            tm->setBlankSymbol(tokens[0]);
        }

    }

    // Línea 6: Estado(s) de aceptación
    if (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        for (const auto& token : tokens) {
            tm->addAcceptanceState(State(token, false, true));
        }
    }

    // Líneas 7+: Transiciones
    while (getNextValidLine(line)) {
        auto tokens = tokenize(line);
        if (tokens.size() == 5) {
            // Formato: estado_actual símbolo_leído estado_siguiente símbolo_escrito dirección
            State currentState(tokens[0]);
            std::string readSymbol = tokens[1];
            State nextState(tokens[2]);
            std::string writeSymbol = tokens[3];
            char direction = tokens[4][0];

            Transition trans(currentState, readSymbol, nextState, writeSymbol, direction);
            tm->addTransition(trans);
        } else {
            throw MTException("Línea " + std::to_string(lineNumber) + " tiene formato incorrecto: " + line);
        }
    }

    file.close();

    // Validar la máquina
    validateMachine(tm);

    return tm;
}

std::vector<std::string> MTParser::tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (ss >> token) {
        if (token[0] != '#') {  // Ignorar comentarios
            tokens.push_back(token);
        } else {
            break;  // El resto de la línea es comentario
        }
    }

    return tokens;
}

std::string MTParser::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, (end - start + 1));
}

bool MTParser::isCommentOrEmpty(const std::string& line) {
    std::string trimmed = trim(line);
    return trimmed.empty() || trimmed[0] == '#';
}

void MTParser::validateMachine(const TuringMachine* tm) {
    if (!tm) {
        throw MTException("La máquina de Turing es nula");
    }

    // Validación 1: Verificar que la máquina tiene al menos un estado
    const auto& states = tm->getStates();
    if (states.empty()) {
        throw MTException("La máquina debe tener al menos un estado");
    }

    // Validación 2: Verificar que el estado inicial existe en Q
    const State& initialState = tm->getInitialState();
    bool initialFound = false;
    for (const auto& state : states) {
        if (state.getName() == initialState.getName()) {
            initialFound = true;
            break;
        }
    }
    if (!initialFound) {
        throw MTException("El estado inicial '" + initialState.getName() + 
                         "' no está en el conjunto de estados Q");
    }

    // Validación 3: Verificar que todos los estados de aceptación están en Q
    const auto& acceptanceStates = tm->getAcceptanceStates();
    if (acceptanceStates.empty()) {
        throw MTException("La máquina debe tener al menos un estado de aceptación");
    }
    
    for (const auto& acceptState : acceptanceStates) {
        bool found = false;
        for (const auto& state : states) {
            if (state.getName() == acceptState.getName()) {
                found = true;
                break;
            }
        }
        if (!found) {
            throw MTException("El estado de aceptación '" + acceptState.getName() + 
                             "' no está en el conjunto de estados Q");
        }
    }

    // Validación 4: Verificar que Σ ⊆ Γ (alfabeto entrada subconjunto de alfabeto cinta)
    const Alphabet& inputAlphabet = tm->getInputAlphabet();
    const Alphabet& tapeAlphabet = tm->getTapeAlphabet();
    
    for (const auto& symbol : inputAlphabet.getSymbols()) {
        if (!tapeAlphabet.contains(symbol)) {
            throw MTException("El símbolo '" + symbol + 
                             "' del alfabeto de entrada Σ no está en el alfabeto de cinta Γ");
        }
    }

    // Validación 5: Verificar que el símbolo blanco no está en Σ
    const std::string& blankSymbol = tapeAlphabet.getBlankSymbol();
    if (inputAlphabet.contains(blankSymbol)) {
        throw MTException("El símbolo blanco '" + blankSymbol + 
                         "' no puede estar en el alfabeto de entrada Σ");
    }

    // Validación 6: Verificar que el símbolo blanco está en Γ
    if (!tapeAlphabet.contains(blankSymbol)) {
        throw MTException("El símbolo blanco '" + blankSymbol + 
                         "' debe estar en el alfabeto de cinta Γ");
    }

    // Validación 7: Verificar transiciones
    const auto& transitions = tm->getTransitions();
    for (const auto& [key, trans] : transitions) {
        // Verificar que los estados de la transición existen en Q
        bool currentExists = false;
        bool nextExists = false;
        
        for (const auto& state : states) {
            if (state.getName() == trans.getCurrentState().getName()) {
                currentExists = true;
            }
            if (state.getName() == trans.getNextState().getName()) {
                nextExists = true;
            }
        }
        
        if (!currentExists) {
            throw MTException("Estado '" + trans.getCurrentState().getName() + 
                             "' en transición no está en Q");
        }
        if (!nextExists) {
            throw MTException("Estado '" + trans.getNextState().getName() + 
                             "' en transición no está en Q");
        }

        // Verificar que los símbolos están en Γ
        if (!tapeAlphabet.contains(trans.getReadSymbol())) {
            throw MTException("Símbolo leído '" + trans.getReadSymbol() + 
                             "' en transición no está en Γ");
        }
        if (!tapeAlphabet.contains(trans.getWriteSymbol())) {
            throw MTException("Símbolo escrito '" + trans.getWriteSymbol() + 
                             "' en transición no está en Γ");
        }

        // Verificar que la dirección es válida
        char dir = trans.getDirection();
        if (dir != 'L' && dir != 'R') {
            throw MTException("Dirección '" + std::string(1, dir) + 
                             "' en transición no es válida (debe ser L o R)");
        }
    }
}
