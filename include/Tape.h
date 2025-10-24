#ifndef TAPE_H
#define TAPE_H

#include <deque>
#include <string>
#include "Alphabet.h"

/**
 * Representa la cinta de la Máquina de Turing
 * La cinta es infinita (se expande dinámicamente)
 */
class Tape {
private:
    std::deque<std::string> cells;
    int headPosition;
    std::string blankSymbol;
    const Alphabet* tapeAlphabet;  // Referencia al alfabeto de cinta

public:
    /**
     * Constructor de Tape
     * @param initialContent Contenido inicial de la cinta (cadena de entrada)
     * @param blank Símbolo que representa celdas vacías
     * @param alphabet Alfabeto de cinta (opcional, para validación)
     */
    Tape(const std::string& initialContent, const std::string& blank, 
         const Alphabet* alphabet = nullptr);

    /**
     * Lee el símbolo en la posición actual del cabezal
     */
    std::string read() const;

    /**
     * Escribe un símbolo en la posición actual del cabezal
     */
    void write(const std::string& symbol);

    /**
     * Mueve el cabezal a la derecha
     */
    void moveRight();

    /**
     * Mueve el cabezal a la izquierda
     */
    void moveLeft();

    /**
     * Obtiene la posición del cabezal
     */
    int getHeadPosition() const;

    /**
     * Obtiene el contenido actual de la cinta
     */
    std::string getContent() const;

    /**
     * Obtiene el contenido visible de la cinta (sin blancos al final)
     */
    std::string getVisibleContent() const;

    /**
     * Reinicia la cinta a su estado inicial
     */
    void reset(const std::string& initialContent);

    /**
     * Valida si un símbolo es válido para escribir en la cinta
     */
    bool isValidSymbol(const std::string& symbol) const;

private:
    /**
     * Expande la cinta si es necesario
     */
    void expandIfNeeded();
};

#endif // TAPE_H
