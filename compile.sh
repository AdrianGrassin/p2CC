#!/bin/bash
# Script de compilación para Linux/macOS
# Uso: ./compile.sh

echo "=== Compilando Simulador de Máquina de Turing ==="
echo "(Soporta monocinta y multicinta)"

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
    echo "  ./build/TuringMachineSimulator <archivo_MT> <entrada> [-t]"
    echo ""
    echo "Flags:"
    echo "  -t  Muestra la traza completa de ejecución"
    echo ""
    echo "El simulador detecta automáticamente si la MT es monocinta o multicinta."
    echo ""
    echo "Ejemplos:"
    echo "  Monocinta:"
    echo "    ./build/TuringMachineSimulator data/Ejemplo_MT.txt \"0011\""
    echo "    ./build/TuringMachineSimulator data/Ejemplo2_MT.txt \"11\" -t"
    echo ""
    echo "  Multicinta:"
    echo "    ./build/TuringMachineSimulator data/MTproposed/mt_copiar.txt \"101\""
    echo "    ./build/TuringMachineSimulator data/MTproposed/mt_copiar.txt \"101\" -t"
else
    echo "✗ Error en la compilación"
    exit 1
fi
