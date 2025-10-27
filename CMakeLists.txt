cmake_minimum_required(VERSION 3.10)
project(MTSimulator)

# Configurar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar el directorio de salida para el ejecutable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/State.cpp
    src/Alphabet.cpp
    src/Transition.cpp
    src/Tape.cpp
    src/TuringMachine.cpp
    src/MTParser.cpp
    src/MTSimulator.cpp
)

# Crear el ejecutable
add_executable(TuringMachineSimulator ${SOURCES})

# Directorios de inclusión
target_include_directories(TuringMachineSimulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Opciones de compilación
if(MSVC)
    target_compile_options(TuringMachineSimulator PRIVATE /W4)
else()
    target_compile_options(TuringMachineSimulator PRIVATE -Wall -Wextra -Wpedantic)
endif()
