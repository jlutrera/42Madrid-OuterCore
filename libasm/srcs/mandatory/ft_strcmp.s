; **************************************************************************
; *                int strcmp(const char *s1, const char *s2)              *
; **************************************************************************

; The  strcmp()  function compares the two strings s1 and s2.
; The comparison is done using unsigned characters.
;
; strcmp() returns an integer indicating the result of the comparison, 
; s follows:
;  •  0, if the s1 and s2 are equal
;  •  a negative value if s1 is less than s2;
;  •  a positive value if s1 is greater than s2.
; **************************************************************************

global ft_strcmp

section .text

ft_strcmp:
.loop:
    movzx eax, byte [rdi]
    movzx edx, byte [rsi]
    cmp al, dl
    jne .diff
    test al, al
    je .equal
    inc rdi
    inc rsi
    jmp .loop

.diff:
    sub eax, edx
    ret

.equal:
    xor eax, eax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
