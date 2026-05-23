# 🧩 Libasm — NASM x86_64 Library

![Language](https://img.shields.io/badge/language-NASM%20x86__64-blue)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![School](https://img.shields.io/badge/42-Madrid-black)
![License](https://img.shields.io/badge/license-MIT-yellow)

Libasm es un proyecto cuyo objetivo es reimplementar funciones estándar de la libc utilizando exclusivamente **Assembly x86_64** bajo Linux.  
El propósito es comprender en profundidad:

- El ABI System V AMD64  
- El funcionamiento real de las syscalls  
- La gestión de memoria  
- La manipulación de punteros y cadenas  
- La interacción entre C y ASM  

Este proyecto desarrolla una librería (`libasm.a`) escrita íntegramente en ASM, junto con una batería de tests interactivos y benchmarks para validar su comportamiento.

---

## 📑 Índice

1. [Descripción del proyecto](#-descripción-del-proyecto)
2. [Estructura](#-estructura-del-proyecto)
3. [Compilación y uso](#-compilación)  
4. [Funciones mandatory](#-funciones-mandatory)  
5. [Funciones bonus](#-funciones-bonus)
6. [Tests interactivos y benchmarks](#-tests-interactivos-y-benchmarks)  
7. [Notas técnicas](#-notas-técnicas)  

---

## 🧩 Descripción del proyecto

El objetivo es implementar una librería en Assembly que replique el comportamiento de varias funciones de la libc.  
Las funciones deben:

- Respetar el ABI System V AMD64  
- Ser compatibles con Linux  
- Manejar correctamente errores y `errno`  
- Ser fieles a la implementación estándar  

El proyecto incluye un sistema de tests interactivos que permite:

- Comparar cada función con su equivalente en C  
- Probar casos límite  
- Medir rendimiento mediante benchmarks  
- Validar comportamiento en tiempo real  

---

## 📁 Estructura del proyecto

```c
libasm/
│── README.md
│── Makefile
│── include/
│   │─  libasm.h
│   │─  libasm_bonus.h
│   │─  tests.h
│   └── tests_bonus.h
├── srcs/
│   ├── Makefile
│   ├── mandatory/
│   │   ├── ft_strlen.s
│   │   ├── ft_strcpy.s
│   │   ├── ft_strcmp.s
│   │   ├── ft_write.s
│   │   ├── ft_read.s
│   │   └── ft_strdup.s
│   └── bonus/
│       ├── ft_atoi_base.s
│       ├── ft_list_push_front.s
│       ├── ft_list_size.s
│       ├── ft_list_sort.s
│       └── ft_list_remove_if.s
└── tests/
    ├── main.c
    ├── main_bonus.c
    ├── mandatory/
    │   ├── test_strlen.c
    │   ├── test_strdup.c
    │   ├── test_strcpy.c
    │   ├── test_strcmp.c
    │   ├── test_read.c
    │   └── test_write.c
    └── bonus/
        ├── test_atoi_base.c
        ├── test_list_push_front.c
        ├── test_list_size.c
        ├── test_list_sort.c
        └── test_list_remove_if.c
```

---

## 🚀 Compilación

Desde la carpeta `srcs/`

```bash
make
make bonus
```

---

## 🧱 Funciones mandatory

### 🔹 `ft_strlen`

```c
size_t ft_strlen(const char *s);
```

Devuelve la longitud de una cadena terminada en \0.
Implementada mediante un bucle que avanza byte a byte hasta encontrar el terminador.

- No modifica registros callee-saved
- Devuelve el resultado en rax
- Comportamiento idéntico a strlen estándar
- strlen(NULL) → comportamiento indefinido (igual que libc)

### 🔹 `ft_strcpy`

```c
char *ft_strcpy(char *dst, const char *src);
```

Copia src en dst, incluyendo el byte nulo final.

- Devuelve dst en rax
- Copia byte a byte
- No comprueba solapamientos (igual que libc)

### 🔹 `ft_strcmp`

```c
int ft_strcmp(const char *s1, const char *s2);
```

Compara dos cadenas lexicográficamente.

- Compara byte a byte
- Devuelve la diferencia entre los primeros bytes distintos
- Usa movzx para comparación unsigned
- Comportamiento idéntico a strcmp

### 🔹 `ft_write`

```c
ssize_t ft_write(int fd, const void *buf, size_t count);
```

Wrapper de la syscall write.

- rax = 1 → syscall write
- Manejo de errores POSIX:
  - Si la syscall devuelve -errno, se asigna a errno mediante __errno_location
  - Devuelve -1 en caso de error
- Comportamiento idéntico a write estándar

### 🔹 `ft_read`

```c
ssize_t ft_read(int fd, void *buf, size_t count);
```

Wrapper de la syscall `read`.

- rax = 0 → syscall read
- Manejo de errores idéntico a ft_write
- No valida punteros (igual que libc)
- read(NULL) → segfault (comportamiento estándar)

### 🔹 `ft_strdup`

```c
char *ft_strdup(const char *s);
```

Duplica una cadena usando `malloc`.

- Llama a ft_strlen para obtener longitud
- Reserva len + 1 bytes
- Copia con ft_strcpy
- Devuelve NULL si malloc falla
- No comprueba s == NULL (igual que libc → comportamiento indefinido)

---

## ⭐ Funciones Bonus

### 🔸 `ft_atoi_base`

Convierte un número en una base arbitraria a entero.

**ASM:**  

- Validar base  
- Saltar espacios  
- Detectar signo  
- Convertir usando índice en la base  

---

### 🔸 `ft_list_push_front`

Inserta un nodo al inicio de la lista.

**ASM:**  

- Reservar memoria  
- Asignar `data`  
- Enlazar con head  

---

### 🔸 `ft_list_size`

Cuenta los nodos de la lista.

**ASM:**  

- Recorrer `next`  
- Incrementar contador  

---

### 🔸 `ft_list_sort`

Ordena la lista usando bubble-sort.

**ASM:**  

- Dos bucles  
- Comparar `data`  
- Intercambiar si es necesario  

---

### 🔸 `ft_list_remove_if`

Elimina nodos cuyo `data` coincide con `ref`.

**ASM:**  

- Recorrer lista  
- Si `cmp(data, ref) == 0`:  
  - `free_fct(data)`  
  - Eliminar nodo  
  - Actualizar head  

---

## 🧪 Tests interactivos y benchmarks

El proyecto incluye un sistema de tests que permite:

- Introducir cadenas y ver el comportamiento en tiempo real
- Comparar ft_* con las funciones estándar
- Probar errores (fd = -1, punteros inválidos, etc.)
- Medir rendimiento mediante benchmarks de cientos de miles de iteraciones
- Validar estabilidad y exactitud de la implementación

Cada función tiene su propio test interactivo y se compila con -fno-pie -no-pie

---

## 📝 Notas técnicas

- Todas las funciones siguen el System V AMD64 ABI
- Se usa NASM como ensamblador
- Las syscalls se realizan mediante la instrucción syscall
- errno se gestiona mediante __errno_location
- La librería no se compila con -fno-pie -no-pie
- Proyecto diseñado para Linux (no compatible con macOS)
