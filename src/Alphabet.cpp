#include "../include/Alphabet.h"
#include <sstream>

/**
 * Constructor por defecto
 */
Alphabet::Alphabet() : blankSymbol("") {
}

/**
 * Constructor con símbolo blanco
 */
Alphabet::Alphabet(const std::string& blank) : blankSymbol(blank) {
    if (!blank.empty()) {
        symbols.insert(blank);
    }
}

/**
 * Añade un símbolo al alfabeto
 */
bool Alphabet::addSymbol(const std::string& symbol) {
    if (symbol.empty()) {
        return false;
    }
    auto result = symbols.insert(symbol);
    return result.second;  // true si se insertó, false si ya existía
}

/**
 * Añade múltiples símbolos al alfabeto
 */
void Alphabet::addSymbols(const std::vector<std::string>& symbolList) {
    for (const auto& symbol : symbolList) {
        addSymbol(symbol);
    }
}

/**
 * Verifica si un símbolo pertenece al alfabeto
 */
bool Alphabet::contains(const std::string& symbol) const {
    return symbols.find(symbol) != symbols.end();
}

/**
 * Verifica si una cadena completa es válida
 */
bool Alphabet::isValidString(const std::string& input) const {
    for (char c : input) {
        std::string symbol(1, c);
        if (!contains(symbol)) {
            return false;
        }
    }
    return true;
}

/**
 * Elimina un símbolo del alfabeto
 */
bool Alphabet::removeSymbol(const std::string& symbol) {
    return symbols.erase(symbol) > 0;
}

/**
 * Obtiene el tamaño del alfabeto
 */
size_t Alphabet::size() const {
    return symbols.size();
}

/**
 * Verifica si el alfabeto está vacío
 */
bool Alphabet::isEmpty() const {
    return symbols.empty();
}

/**
 * Obtiene todos los símbolos como vector
 */
std::vector<std::string> Alphabet::getSymbols() const {
    return std::vector<std::string>(symbols.begin(), symbols.end());
}

/**
 * Obtiene el símbolo blanco
 */
std::string Alphabet::getBlankSymbol() const {
    return blankSymbol;
}

/**
 * Establece el símbolo blanco
 */
void Alphabet::setBlankSymbol(const std::string& blank) {
    blankSymbol = blank;
    if (!blank.empty()) {
        addSymbol(blank);
    }
}

/**
 * Limpia el alfabeto
 */
void Alphabet::clear() {
    symbols.clear();
    blankSymbol.clear();
}

/**
 * Verifica si este alfabeto es subconjunto de otro
 */
bool Alphabet::isSubsetOf(const Alphabet& other) const {
    for (const auto& symbol : symbols) {
        if (!other.contains(symbol)) {
            return false;
        }
    }
    return true;
}

/**
 * Método auxiliar para imprimir el alfabeto
 */
std::string Alphabet::toString() const {
    std::stringstream ss;
    ss << "Σ = {";
    bool first = true;
    for (const auto& symbol : symbols) {
        if (!first) ss << ", ";
        ss << "'" << symbol << "'";
        first = false;
    }
    ss << "}";
    if (!blankSymbol.empty()) {
        ss << " [Blanco: '" << blankSymbol << "']";
    }
    return ss.str();
}
