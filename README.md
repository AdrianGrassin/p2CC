# Simulador de Máquina de Turing

**Asignatura:** Complejidad Computacional  
**Curso:** 2024-2025  
**Autor:** Adrián Grassin Luis

---

## 📋 Descripción

Simulador de Máquinas de Turing implementado en C++17 que permite:

- ✅ Cargar especificaciones de MT desde archivos de texto
- ✅ Soporte para máquinas monocinta y multicinta
- ✅ Validación automática de la definición formal
- ✅ Ejecución paso a paso con visualización de la traza
- ✅ Ejercicios propuestos implementados
Implementa la definición formal: **M = (Q, Σ, Γ, δ, q₀, F)** para monocinta y **M = (Q, Σ, Γ, δ, q₀, F, k)** para multicinta.

---

## Compilación y Ejecución

### Compilación

Para compilar el proyecto se puede utilizar CMake, aunque también es posible compilar con los scripts compile.sh para Linux/Mac o compile.bat para Windows.

```bash
mkdir build
cd build
cmake ..
make
```

El ejecutable se genera en `build/mtsimulator`.

### Uso

El simulador detecta automáticamente si la MT es monocinta o multicinta.

```bash
# Modo resumido (solo muestra estado inicial y final)
.\build\TuringMachineSimulator.exe <archivo_MT> <entrada>

# Modo detallado (muestra todos los pasos)
.\build\TuringMachineSimulator.exe <archivo_MT> <entrada> -t
```

**Ejemplos:**

```bash
# Windows
.\build\TuringMachineSimulator.exe data\Ejemplo_MT.txt "0011"
.\build\TuringMachineSimulator.exe data\Ejemplo2_MT.txt "11" -t

# Linux/Mac
./build/TuringMachineSimulator data/Ejemplo_MT.txt "0011"
./build/TuringMachineSimulator data/Ejemplo2_MT.txt "11" -t
```

### Flags Disponibles

- **-t**: Muestra la traza completa de ejecución (todos los pasos intermedios)

---

## 🎯 Ejercicios Propuestos Implementados

### 1. Contador de a^n b^m (Multicinta)

**Archivo:** `data/MTproposed/mt_abcontador.txt`

Máquina de Turing de 2 cintas que cuenta el número de 'a's y 'b's en una cadena y genera como salida `1^(n+1).1^(m+1)` donde n es el número de 'a's y m el número de 'b's.

**Ejemplo de uso:**

```bash
.\build\TuringMachineSimulator data\MTproposed\mt_abcontador.txt "abbabaabb" 
Ejecutando con entrada: "abbabaabb"

=== Traza de Ejecución ===
Paso 0 (inicial): Estado: q0
Cinta 1: [abbabaabb], Cabezal: 0
Cinta 2: [], Cabezal: 0
Paso 49 (final): Estado: qacc
Cinta 1: [11111.111111], Cabezal: 13
Cinta 2: [11111.111111], Cabezal: 13

=== Resultado ===
Pasos totales: 49
Resultado: ACEPTA
Cintas finales:
  Cinta 1: [11111.111111]
  Cinta 2: [11111.111111]
Estado final: qacc
=================================================
```

### 2. Reconocedor L = {a^n b^m | m > n, n > 0}

**Archivo:** `data/MTproposed/mt_an_bm.txt`

Máquina de Turing que acepta cadenas donde:

- Debe haber al menos una 'a' (n > 0)
- El número de 'b's debe ser estrictamente mayor que el de 'a's (m > n)

**Ejemplos:**
```bash
# Cadenas aceptadas
.\build\TuringMachineSimulator data\MTproposed\mt_an_bm.txt "abb"        # n=1, m=2 ✓
.\build\TuringMachineSimulator data\MTproposed\mt_an_bm.txt "aabbb"  # n=2, m=3 ✓

# Cadenas rechazadas
.\build\TuringMachineSimulator data\MTproposed\mt_an_bm.txt "bb"     # n=0 ✗
.\build\TuringMachineSimulator data\MTproposed\mt_an_bm.txt "ab"     # m=n ✗
.\build\TuringMachineSimulator data\MTproposed\mt_an_bm.txt "aaab"   # m<n ✗
```

### Reglas del Formato

- Los elementos se separan por espacios
- Las líneas con `#` son comentarios
- Las 6 líneas de cabecera deben estar en orden
- Antes de la sección de transiciones, se puede incluir el número de cintas para máquinas multicinta, si no se asume monocinta por defecto.

---

## 🏗️ Arquitectura

### Estructura del Proyecto

```
p2CC/
├── include/         # Archivos de cabecera (.h)
├── src/             # Implementaciones (.cpp)
├── data/            # Ejemplos de MT
│   ├── Ejemplo_MT.txt
│   ├── Ejemplo2_MT.txt
│   └── multitape/   # Ejemplos multicinta
├── build/           # Archivos compilados
└── CMakeLists.txt   # Configuración CMake
```

### Componentes Principales

**TuringMachine**: Clase principal que implementa M = (Q, Σ, Γ, δ, q₀, F)

- Gestión de estados, alfabetos y transiciones
- Ejecución paso a paso
- Verificación de aceptación

**Tape**: Cinta infinita implementada con `std::deque`

- Expansión dinámica O(1) en ambas direcciones
- Operaciones de lectura/escritura
- Movimiento del cabezal (L/R)

**MTParser**: Análisis y validación de archivos

- Validación de definición formal
- Detección de errores en especificación
- Lanza excepciones descriptivas

**MTSimulator**: Control de ejecución y visualización

- Registro de traza completa
- Modos de visualización (resumido/detallado)
- Estadísticas de ejecución

---

## ⚙️ Decisiones de Implementación

**Variante de MT implementada:**

- Escritura y movimiento simultáneos: δ(q, a) = (q', b, D)
- Movimientos: L (izquierda), R (derecha) y S (sin movimiento)
- Cinta infinita en ambas direcciones
- Máquina determinista

**Características:**

- Soporte para múltiples estados de aceptación (F ⊆ Q)
- Validación exhaustiva de la especificación antes de ejecutar
- Límite de 10,000 pasos para evitar bucles infinitos (puede ajustarse)
- Modo de visualización resumido o detallado con `-t`

### Validaciones Realizadas

El sistema verifica automáticamente:

- ✅ q₀ ∈ Q (estado inicial está en Q)
- ✅ F ⊆ Q (todos los estados de aceptación están en Q)
- ✅ Σ ⊆ Γ (alfabeto de entrada es subconjunto del alfabeto de cinta)
- ✅ blank ∈ Γ ∧ blank ∉ Σ (símbolo blanco está en Γ pero no en Σ)
- ✅ Para cada transición δ(q,a) = (q',b,D):
  - q, q' ∈ Q
  - a, b ∈ Γ
  - D ∈ {L, R}

**Archivos de prueba:** Los archivos en `data/invalid/` contienen ejemplos de MTs inválidas para probar el sistema de validación.

## 📄 Licencia

Proyecto académico para la asignatura de Complejidad Computacional - Universidad de La Laguna
