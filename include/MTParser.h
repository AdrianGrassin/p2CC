#ifndef MT_PARSER_H
#define MT_PARSER_H

#include <string>
#include <vector>
#include "TuringMachine.h"

/**
 * Parsea un archivo de especificación de Máquina de Turing
 * y construye una instancia de TuringMachine
 */
class MTParser {
public:
    /**
     * Parsea un archivo y retorna una Máquina de Turing
     * @param filename Ruta del archivo de especificación
     * @return TuringMachine cargada desde el archivo
     */
    static TuringMachine* parseFile(const std::string& filename);

private:
    /**
     * Divide una línea en tokens separados por espacios
     */
    static std::vector<std::string> tokenize(const std::string& line);

    /**
     * Elimina espacios en blanco al inicio y final de una línea
     */
    static std::string trim(const std::string& str);

    /**
     * Verifica si una línea es un comentario o está vacía
     */
    static bool isCommentOrEmpty(const std::string& line);

    /**
     * Valida que la MT esté correctamente definida
     * Lanza MTException si hay errores
     */
    static void validateMachine(const TuringMachine* tm);
};

#endif // MT_PARSER_H
