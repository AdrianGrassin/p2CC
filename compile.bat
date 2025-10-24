@echo off
REM Script de compilación para Windows
REM Uso: compile.bat

echo === Compilando Simulador de Maquina de Turing ===

REM Crear directorio de compilación si no existe
if not exist build mkdir build

echo Compilando archivos fuente...

REM Compilar con g++
g++ -std=c++17 -I./include -o build/TuringMachineSimulator.exe ^
    src/main.cpp ^
    src/State.cpp ^
    src/Alphabet.cpp ^
    src/Transition.cpp ^
    src/Tape.cpp ^
    src/TuringMachine.cpp ^
    src/MTParser.cpp ^
    src/MTSimulator.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [OK] Compilacion exitosa!
    echo Ejecutable: build\TuringMachineSimulator.exe
    echo.
    echo Uso:
    echo   .\build\TuringMachineSimulator.exe ^<archivo_MT^> ^<entrada^>
    echo   .\build\TuringMachineSimulator.exe ^<archivo_MT^> ^<entrada^> -h
    echo.
    echo Ejemplos:
    echo   .\build\TuringMachineSimulator.exe data\Ejemplo_MT.txt "0011"
    echo   .\build\TuringMachineSimulator.exe data\Ejemplo2_MT.txt "11" -h
) else (
    echo.
    echo [ERROR] Error en la compilacion
    exit /b 1
)
