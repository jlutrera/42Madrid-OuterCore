; **************************************************************************
; *                        size_t strlen(const char *s)                    *
; **************************************************************************

; The strlen() function calculates the length of the string pointed to by s,
; excluding the terminating null byte ('\0').
; The strlen() function returns the number of bytes in 
; the string pointed to by s.
; **************************************************************************

global ft_strlen            ; *s = rdi (puntero al primer argumento)

section .text

ft_strlen:
    xor rax, rax            ; rax (valor de retorno) = 0
.loop:
    cmp byte [rdi + rax], 0 ; ¿fin de string?
    je .end                 ; en caso afirmativo -> fin
    inc rax
    jmp .loop
.end:
    ret

; Esta sección le dice al linker que el archivo no necesita una pila ejecutable
; Evita el warning: "missing .note.GNU-stack section implies executable stack"

section .note.GNU-stack noalloc noexec nowrite progbits
