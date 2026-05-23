; **************************************************************************
; *       char *strcpy(char *restrict dst, const char *restrict src)       *
; **************************************************************************

; This function copy the string pointed to by src, into a string
; at the buffer pointed to by dst.  The programmer is  responsible
; for  allocating  a  destination  buffer  large  enough, that is,
; strlen(src) + 1.  For the difference between the two  functions,
; this  function returns a pointer to the terminating null byte of
; the copied string.
; **************************************************************************

global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi        ; return dst
.copy:
    movsb               ; copia byte [rsi] → [rdi], incrementa ambos
    cmp byte [rdi - 1], 0
    jne .copy
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
