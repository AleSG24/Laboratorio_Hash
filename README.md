# Laboratorio_Hash

---

Implementación de una tabla de hash con encadenamiento separado para resolver colisiones. Almacena números enteros en un arreglo de listas enlazadas de tamaño limitado, con rehash automático cuando el factor de carga supera el 70%.

---

## Constructor y Destructor

### `TablaHash(int tamano)`

| | |
|---|---|
| **Parámetro** | `tamano` *(int)* — Tamaño inicial del arreglo de cubetas. |
| **Retorna** | — Constructor, no retorna valor. |
| **Funcionamiento** | Inicializa la tabla de hash con el tamaño indicado. |

- Valida que `tamano > 0`, lanza `std::invalid_argument` si no.
- Asigna dinámicamente un arreglo de `std::list<int>` de tamaño `tamano`.
- Cada cubeta comienza como una lista vacía.

---

### `~TablaHash()`

| | |
|---|---|
| **Parámetro** | — No recibe parámetros. |
| **Retorna** | — Destructor, no retorna valor. |
| **Funcionamiento** | Libera la memoria dinámica del arreglo de listas. |

- Ejecuta `delete[] tabla` para evitar memory leaks.
- Se invoca automáticamente cuando el objeto sale de scope.

---

## Métodos Públicos

### `bool insertar(int valor)`

| | |
|---|---|
| **Parámetro** | `valor` *(int)* — Número entero a insertar en la tabla. |
| **Retorna** | `true` si se insertó correctamente. `false` si el valor ya existía. |
| **Funcionamiento** | Inserta un valor entero en la tabla de hash. |

- Verifica si el índice de llenado >= 0.7, si es así, llama a `rehash()`. Esto se hace así porque al investigar me di cuenta que la convención suele ser llamar rehash cuando el indice de llenado llega a 0.7. 
- Calcula la posición con `hash(valor)`.
- Recorre la lista en esa posición para detectar duplicados.
- Si no hay duplicado, añade el valor al final de la lista.

---

### `bool eliminar(int valor)`

| | |
|---|---|
| **Parámetro** | `valor` *(int)* — Número entero a eliminar de la tabla. |
| **Retorna** | `true` si el valor fue encontrado y eliminado. `false` si no existía. |
| **Funcionamiento** | Elimina un valor de la tabla si existe. |

- Calcula la posición con `hash(valor)`.
- Recorre la lista de esa cubeta buscando el valor.
- Si lo encuentra, usa `list::erase()` para eliminarlo y retorna `true`.
- Si no lo encuentra, retorna `false` sin modificar nada.

---

### `bool buscar(int valor)`

| | |
|---|---|
| **Parámetro** | `valor` *(int)* — Número entero a buscar en la tabla. |
| **Retorna** | `true` si el valor existe en la tabla. `false` si no se encontró. |
| **Funcionamiento** | Busca un valor en la tabla de hash. |

- Calcula la posición con `hash(valor)`.
- Recorre la lista de esa cubeta comparando cada elemento.
- Operación O(1) promedio, O(n) en el peor caso.

---

## Métodos Privados

### `int hash(int valor)`

| | |
|---|---|
| **Parámetro** | `valor` *(int)* — Número entero del que se calculará el índice. |
| **Retorna** | `int` — Índice entre 0 y `tamano-1` correspondiente al valor. |
| **Funcionamiento** | Función de dispersión que mapea un entero a una cubeta. |

- Aplica la fórmula: `abs(valor) % tamano`.
- `abs()` garantiza índices no negativos para valores negativos.
- Distribuye uniformemente si `tamano` es un número primo.
- Es llamada internamente por `insertar`, `eliminar` y `buscar`.

---

### `float indice_llenado()`

| | |
|---|---|
| **Parámetro** | — No recibe parámetros. |
| **Retorna** | `float` — Fracción de cubetas ocupadas (entre 0.0 y 1.0). |
| **Funcionamiento** | Calcula el factor de carga actual de la tabla. |

- Recorre todas las cubetas y cuenta las que tienen al menos un elemento.
- Retorna `ocupadas / tamano` como número flotante.
- Un valor >= 0.7 dispara el rehash en la próxima inserción.

---

### `bool rehash()`

| | |
|---|---|
| **Parámetro** | — No recibe parámetros. |
| **Retorna** | `true` siempre que el proceso de rehash se complete con éxito. |
| **Funcionamiento** | Duplica el tamaño de la tabla y redistribuye todos los elementos. |

- Crea una nueva tabla de tamaño `tamano * 2`.
- Reinserta cada valor en la nueva tabla usando el nuevo módulo.
- Libera la memoria de la tabla antigua con `delete[]`.
- Se invoca automáticamente desde `insertar` cuando `indice_llenado() >= 0.7`.

---

## Notas de Uso

| Función | Complejidad |
|---|---|
| `insertar()` | O(1) amortizado — O(n·m) en rehash ocasional |
| `eliminar()` | O(1) promedio |
| `buscar()` | O(1) promedio |
