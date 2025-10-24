cmake_minimum_required(VERSION 3.10)
project(MTSimulator)

# Configurar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(mtsimulator ${SOURCES})

# Directorios de inclusión
target_include_directories(mtsimulator PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Opciones de compilación
if(MSVC)
    target_compile_options(mtsimulator PRIVATE /W4)
else()
    target_compile_options(mtsimulator PRIVATE -Wall -Wextra -Wpedantic)
endif()
