#include "../include/Tape.h"

/**
 * Constructor de Tape
 */
Tape::Tape(const std::string& initialContent, const std::string& blank,
           const Alphabet* alphabet)
    : headPosition(0), blankSymbol(blank), tapeAlphabet(alphabet) {
    // Inicializar la cinta con el contenido
    for (char c : initialContent) {
        cells.push_back(std::string(1, c));
    }
    // Agregar algunos blancos al final para movimiento
    for (int i = 0; i < 10; i++) {
        cells.push_back(blankSymbol);
    }
}

std::string Tape::read() const {
    if (headPosition >= 0 && headPosition < (int)cells.size()) {
        return cells[headPosition];
    }
    return blankSymbol;
}

void Tape::write(const std::string& symbol) {
    expandIfNeeded();
    if (headPosition >= 0 && headPosition < (int)cells.size()) {
        cells[headPosition] = symbol;
    }
}

void Tape::moveRight() {
    headPosition++;
    expandIfNeeded();
}

void Tape::moveLeft() {
    headPosition--;
    expandIfNeeded();
}

int Tape::getHeadPosition() const {
    return headPosition;
}

std::string Tape::getContent() const {
    std::string result;
    for (const auto& cell : cells) {
        result += cell;
    }
    return result;
}

std::string Tape::getVisibleContent() const {
    // Encontrar el primer y último símbolo no-blanco
    int firstNonBlank = -1;
    int lastNonBlank = -1;
    
    for (size_t i = 0; i < cells.size(); i++) {
        if (cells[i] != blankSymbol) {
            if (firstNonBlank == -1) {
                firstNonBlank = i;
            }
            lastNonBlank = i;
        }
    }
    
    // Si no hay símbolos no-blancos, devolver vacío
    if (firstNonBlank == -1) {
        return "";
    }
    
    // Construir el contenido visible desde el primer hasta el último símbolo no-blanco
    std::string result;
    for (int i = firstNonBlank; i <= lastNonBlank; i++) {
        result += cells[i];
    }
    return result;
}

void Tape::reset(const std::string& initialContent) {
    cells.clear();
    headPosition = 0;
    
    for (char c : initialContent) {
        cells.push_back(std::string(1, c));
    }
    for (int i = 0; i < 10; i++) {
        cells.push_back(blankSymbol);
    }
}

void Tape::expandIfNeeded() {
    if (headPosition < 0) {
        // Expandir hacia la izquierda con push_front O(1) amortizado
        int cellsToAdd = -headPosition;
        for (int i = 0; i < cellsToAdd; i++) {
            cells.push_front(blankSymbol);
        }
        headPosition = 0;
    }
    if (headPosition >= (int)cells.size()) {
        // Expandir hacia la derecha
        while (headPosition >= (int)cells.size()) {
            cells.push_back(blankSymbol);
        }
    }
}

bool Tape::isValidSymbol(const std::string& symbol) const {
    if (tapeAlphabet == nullptr) {
        return true;  // Sin alfabeto, todos los símbolos son válidos
    }
    return tapeAlphabet->contains(symbol);
}
