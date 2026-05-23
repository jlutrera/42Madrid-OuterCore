; **************************************************************************
; *                      char *strdup(const char *s)                       *
; **************************************************************************

; Returns a pointer to a new string which is a duplicate of the string s.
; Memory for the new string  is  obtained  with malloc(3),
; and can be freed with free(3).
; **************************************************************************

global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

section .text

ft_strdup:
    push rbx            ; guardar rbx
    mov rbx, rdi        ; guardar s en rbx

    ; len = ft_strlen(s)
    mov rdi, rbx
    call ft_strlen

    inc rax             ; espacio para '\0'
    mov rdi, rax
    call malloc
    test rax, rax
    je .malloc_fail

    ; copiar
    mov rdi, rax        ; dst
    mov rsi, rbx        ; src (s original)
    call ft_strcpy

    pop rbx
    ret

.malloc_fail:
    pop rbx
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
