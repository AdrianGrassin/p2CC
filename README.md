# Simulador de Máquina de Turing

**Asignatura:** Complejidad Computacional  
**Curso:** 2024-2025  
**Autor:** Adrián Grassin Luis

---

## 📋 Descripción

Simulador de Máquinas de Turing implementado en C++17 que permite:
- ✅ Cargar especificaciones de MT desde archivos de texto
- ✅ Validación automática de la definición formal
- ✅ Ejecución paso a paso con visualización de la traza
- ✅ Detección de errores en tiempo de carga

Implementa la definición formal: **M = (Q, Σ, Γ, δ, q₀, F)**

---

## 🚀 Compilación y Ejecución

### Compilación

```bash
mkdir build
cd build
cmake ..
make
```

El ejecutable se genera en `build/mtsimulator`.

**Alternativa sin CMake:**
```bash
g++ -std=c++17 -I./include -o build/mtsimulator src/*.cpp
```

> **Nota:** En Windows usar `compile.bat` o MinGW/MSYS2.

### Uso

```bash
# Modo resumido (solo muestra estado inicial y final)
./build/mtsimulator <archivo_MT> <entrada>

# Modo detallado (muestra todos los pasos)
./build/mtsimulator <archivo_MT> <entrada> -h
```

**Ejemplos:**
```bash
./build/mtsimulator data/Ejemplo_MT.txt "0011"
./build/mtsimulator data/Ejemplo2_MT.txt "11" -h
```

---

### Reglas del Formato

- Los elementos se separan por espacios
- Las líneas con `#` son comentarios
- Dirección: `L` (izquierda) o `R` (derecha)
- Las 6 líneas de cabecera deben estar en orden

---

## 🏗️ Arquitectura

### Estructura del Proyecto

```
p2CC/
├── include/          # Archivos de cabecera (.h)
├── src/             # Implementaciones (.cpp)
├── data/            # Ejemplos de MT
│   ├── Ejemplo_MT.txt
│   ├── Ejemplo2_MT.txt
│   └── invalid/     # Casos de prueba inválidos
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
- Movimientos: L (izquierda) y R (derecha)
- Cinta infinita en ambas direcciones
- Máquina determinista

**Características:**
- Soporte para múltiples estados de aceptación (F ⊆ Q)
- Validación exhaustiva de la especificación antes de ejecutar
- Límite de 10,000 pasos para evitar bucles infinitos (puede ajustarse)
- Modo de visualización resumido o detallado con `-h`

---

## 💡 Ejemplos de Uso

### Ejemplo 1: Reconocimiento de {0ⁿ1ⁿ | n ≥ 0}

```bash
./build/mtsimulator data/Ejemplo_MT.txt "0011"
```

**Salida (modo resumido):**
```
=== Traza de Ejecución ===
Paso 0 (inicial): Estado: q0, Cinta: [0011], Cabezal: 0
Paso 4 (final): Estado: q0, Cinta: [0011], Cabezal: 4

=== Resultado ===
Resultado: RECHAZA
```

Con `-h` se muestran todos los pasos intermedios.

---

### Ejemplo 2: Duplicación en unario

```bash
./build/mtsimulator data/Ejemplo2_MT.txt "11"
```

**Salida:**
```
=== Traza de Ejecución ===
Paso 0 (inicial): Estado: q0, Cinta: [11], Cabezal: 0
Paso 16 (final): Estado: q5, Cinta: [1111], Cabezal: 1

=== Resultado ===
Resultado: ACEPTA
Cinta final: [1111]
```

La entrada `11` (2 en unario) se duplica a `1111` (4 en unario).

---

## ⚠️ Validación de Errores

El parser detecta automáticamente errores en las especificaciones antes de la ejecución:

### Ejemplos de Errores Detectados

#### ❌ Estado inicial no definido:
```text
q1 q2      # Q = {q1, q2}
0 1
0 1 .
q99        # Error: q99 ∉ Q
```
```
Error de validación: El estado inicial 'q99' no está en el conjunto de estados Q
```

#### ❌ Símbolo blanco en alfabeto de entrada:
```text
q0 q1
0 1 .      # Error: . está en Σ
0 1 .
q0
.
q1
```
```
Error de validación: El símbolo blanco '.' no puede estar en el alfabeto de entrada Σ
```

#### ❌ Símbolo no definido en transición:
```text
q0 q1
0 1        # Σ = {0, 1}
0 1 .      # Γ = {0, 1, .}
q0
.
q1
q0 0 q1 X R   # Error: X ∉ Γ
```
```
Error de validación: Símbolo escrito 'X' en transición no está en Γ
```

#### ❌ Estado de aceptación inválido:
```text
q0 q1      # Q = {q0, q1}
0 1
0 1 .
q0
.
q99        # Error: q99 ∉ Q
```
```
Error de validación: Estado de aceptación 'q99' no está en Q
```

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

---

## 🧪 Casos de Prueba

**Válidos:**

- `data/Ejemplo_MT.txt` - Reconocedor de patrones
- `data/Ejemplo2_MT.txt` - Duplicador en unario

**Inválidos (para validación):**

- `data/invalid/Test_BlankInSigma.txt`
- `data/invalid/Test_InvalidAcceptState.txt`
- `data/invalid/Test_InvalidSymbol.txt`

---

## 📄 Licencia

Proyecto académico para la asignatura de Complejidad Computacional - Universidad de La Laguna
