#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>
#include <set>
#include <vector>

/**
 * Representa un alfabeto (conjunto de símbolos)
 */
class Alphabet {
private:
    std::set<std::string> symbols;
    std::string blankSymbol;

public:
    /**
     * Constructor por defecto
     */
    Alphabet();

    /**
     * Constructor con símbolo blanco
     */
    explicit Alphabet(const std::string& blank);

    /**
     * Añade un símbolo al alfabeto
     */
    bool addSymbol(const std::string& symbol);

    /**
     * Añade múltiples símbolos al alfabeto
     */
    void addSymbols(const std::vector<std::string>& symbolList);

    /**
     * Verifica si un símbolo pertenece al alfabeto
     */
    bool contains(const std::string& symbol) const;

    /**
     * Verifica si una cadena completa es válida (todos sus símbolos están en el alfabeto)
     */
    bool isValidString(const std::string& input) const;

    /**
     * Elimina un símbolo del alfabeto
     */
    bool removeSymbol(const std::string& symbol);

    /**
     * Obtiene el tamaño del alfabeto
     */
    size_t size() const;

    /**
     * Verifica si el alfabeto está vacío
     */
    bool isEmpty() const;

    /**
     * Obtiene todos los símbolos como vector
     */
    std::vector<std::string> getSymbols() const;

    /**
     * Obtiene el símbolo blanco
     */
    std::string getBlankSymbol() const;

    /**
     * Establece el símbolo blanco
     */
    void setBlankSymbol(const std::string& blank);

    /**
     * Limpia el alfabeto
     */
    void clear();

    /**
     * Verifica si este alfabeto es subconjunto de otro
     */
    bool isSubsetOf(const Alphabet& other) const;

    /**
     * Método auxiliar para imprimir el alfabeto
     */
    std::string toString() const;
};

#endif // ALPHABET_H
