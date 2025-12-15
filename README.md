# Nemergent_technical_test_C

Proyecto: Programa en C — listas concurrentes de enteros (positivos y negativos)

Descripción
-----------
Este proyecto es una prueba técnica que implementa un programa en C que crea múltiples hilos en paralelo. Cada hilo genera números enteros aleatorios (tipo `int`, en el rango de `INT_MIN` a `INT_MAX`) y los inserta en una de dos listas enlazadas compartidas: una para números negativos y otra para números positivos.

Características principales
- Hilos en paralelo (POSIX threads / `pthread`).
- Dos listas enlazadas compartidas: una para números positivos y otra para negativos.
- Protección de acceso concurrente mediante `pthread_mutex_t`.
- Manejo explícito de memoria (sin fugas) y limpieza al finalizar.
- Salida de errores por `stderr`, resto por `stdout`.
- Código modular: varios archivos `.c` y `.h`.

Estructura del repositorio
-------------------------
- `main.c`          : Comprobación de argumentos y arranque del programa.
- `run.c`           : Lógica principal: creación/join de hilos y estructura de datos "globales".
- `rutine.c`        : Rutina del hilo que genera e inserta números.
- `list.c`          : Implementación de la lista enlazada y operaciones (insert, print, create/destroy).
- `technical_test.h`: Cabeceras públicas, tipos y prototipos.
- `Makefile`        : Reglas para compilar (`make`, `make sani`, `make test`, etc.).
- `test.py`         : Script de pruebas básicas (chequeo de códigos de salida).

Compilación
-----------
Requisitos: `gcc`, `make`. Para análisis adicional (Valgrind) instale `valgrind`.

Compilar (modo normal):

AVISO IMPORTANTE: No usar Valgrind junto con los sanitizers (por ejemplo, no ejecutar Valgrind sobre un binario compilado con `make sani` / `-fsanitize`).
Valgrind y las herramientas del sistema de sanitizers son incompatibles: los binarios compilados con `-fsanitize` no funcionan correctamente bajo Valgrind y los informes resultantes pueden ser erróneos o la ejecución puede fallar.

- Si quieres usar Valgrind: compila el binario SIN sanitizers, pero con símbolos de depuración (`-g`), y ejecuta Valgrind sobre ese binario.
- Si quieres usar AddressSanitizer/UndefinedBehaviorSanitizer: usa `make sani` y analiza la salida del sanitizer SIN envolverlo en Valgrind.

Valgrind (y sus herramientas como `helgrind`/`drd`) además ralentizan drásticamente la ejecución y pueden cambiar el comportamiento temporal del programa (p. ej. hilos muy cortos). Úsalo solo para depuración local con casos de prueba controlados.

```bash
make
```

Compilar con AddressSanitizer (útil para detectar memory leaks/uso inválido):

```bash
make sani
```

Compilar sin flags (para comportamiento sin warnings ni sanitizers):

```bash
make flagless
```

Uso
---
El ejecutable generado se llama `technical_test`.
Su invocación correcta requiere 2 parámetros de entrada:

1. Número total de hilos.
2. Número de números que generará cada hilo.

Ejemplo:

```bash
./technical_test 8 1000
```

Si los parámetros son incorrectos o faltan, el programa imprimirá un mensaje de error por `stderr` con el uso correcto y saldrá con un código de error. Los códigos usados por el programa (definidos en `technical_test.h`) son:

- `ERROR_ARGC`  (0x10): número de argumentos inválido.
- `ERROR_ARGV1` (0x11): primer argumento inválido.
- `ERROR_ARGV2` (0x12): segundo argumento inválido.

Salida
------
- Al finalizar, el programa imprimirá ambas listas (negativos y positivos), cada elemento en una línea.
- Los errores, en caso de haberlos, se imprimen en `stderr`.

Pruebas básicas
---------------
Hay un pequeño `test.py` que verifica los códigos de salida para algunos casos básicos. Para ejecutar las pruebas:

```bash
make test
```

Esto compilará el programa y lanzará `python3 test.py ./technical_test`.


Diseño y consideraciones importantes
------------------------------------
- Sincronización: las listas enlazadas comparten un `pthread_mutex_t` por cabecera de lista (`t_list_head`). Cada operación de inserción y de imprimido toma/desbloquea el mutex correspondiente.
- Ordenación: la inserción intenta mantener el orden deseado al insertar de forma consecutiva en la lista.
- Memoria: todas las asignaciones se liberan al terminar (con `destroy_list` y `free` de buffers auxiliares).
- Robustez: el programa valida los argumentos de entrada; los errores se reportan por `stderr` y se usan códigos de salida bien definidos.


## Posibles mejoras

Al realizar el proyecto en tan solo dos horas, hay cosas que se podrian mejorar o ampliar, como por ejemplo:

- Escribir de una manera mas limpia y eficiente el codigo, evitando repeticiones ,mejorando la legibilidad, haciendolo mas claro y mantenible. Funciones como insert o run podrian beneficiarse estar mucho mejor.
- Utilizar una estructura de datos mas eficiente para la insercion concurrente, como un arbol binario.
- Se podria testear si sería mas eficiente usar un mutex por nodo en lugar de uno por lista y en caso de serlo y ser necesario implementarlo.
- Ampliar los tests para cubrir mas casos y asegurar la robustez del programa mucho mas alla de las pruebas basicas actuales..
- Gestionar mejor los errores de malloc y otras llamadas al sistema, para evitar salidas abruptas del programa.
- rand_r es una funcion obsoleta, se podria usar una mejor alternativa para la generacion de numeros aleatorios en un entorno multihilo y ya de paso no generar de manera tan chapucera las seeds.
- Revisar la seguridad general del programa mas profundamente.


Proyecto de prueba técnica — Nemergent Solutions SL. Diciembre 2025.
