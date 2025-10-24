#!/bin/bash
# Script de compilación para Linux/macOS
# Uso: ./compile.sh

echo "=== Compilando Simulador de Máquina de Turing ==="

# Crear directorio de compilación si no existe
mkdir -p build

echo "Compilando archivos fuente..."

# Compilar con g++
g++ -std=c++17 -I./include -o build/TuringMachineSimulator \
    src/main.cpp \
    src/State.cpp \
    src/Alphabet.cpp \
    src/Transition.cpp \
    src/Tape.cpp \
    src/TuringMachine.cpp \
    src/MTParser.cpp \
    src/MTSimulator.cpp

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "✓ Compilación exitosa!"
    echo "Ejecutable: build/TuringMachineSimulator"
    echo ""
    echo "Uso:"
    echo "  ./build/TuringMachineSimulator <archivo_MT> <entrada>"
    echo "  ./build/TuringMachineSimulator <archivo_MT> <entrada> -h"
    echo ""
    echo "Ejemplos:"
    echo "  ./build/TuringMachineSimulator data/Ejemplo_MT.txt \"0011\""
    echo "  ./build/TuringMachineSimulator data/Ejemplo2_MT.txt \"11\" -h"
else
    echo "✗ Error en la compilación"
    exit 1
fi
