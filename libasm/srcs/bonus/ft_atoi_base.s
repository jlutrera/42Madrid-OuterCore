global ft_atoi_base
section .text

; int ft_atoi_base(char *str, char *base)
;   rdi = str
;   rsi = base
;   eax = return 

ft_atoi_base:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14

    xor eax, eax
    test rdi, rdi
    jz .error
    test rsi, rsi
    jz .error

; ---------------------------------------
; Validar base y calcular longitud
; ---------------------------------------
    xor rcx, rcx              ; rcx = len

.base_len_loop:
    mov bl, [rsi + rcx]
    test bl, bl
    jz .base_len_done

    ; caracteres prohibidos
    cmp bl, '+'
    je .error
    cmp bl, '-'
    je .error
    cmp bl, ' '
    je .error
    cmp bl, 9
    jb .check_dup
    cmp bl, 13
    jbe .error

.check_dup:
    mov rdx, rcx
.dup_loop:
    test rdx, rdx
    jz .dup_ok
    dec rdx
    cmp bl, [rsi + rdx]
    je .error
    jmp .dup_loop

.dup_ok:
    inc rcx
    jmp .base_len_loop

.base_len_done:
    cmp rcx, 2
    jb .error
    mov r12d, ecx             ; base_len

; ---------------------------------------
; Saltar espacios iniciales
; ---------------------------------------
.skip_space:
    mov bl, [rdi]
    cmp bl, ' '
    je .skip_inc
    cmp bl, 9
    jb .sign
    cmp bl, 13
    jbe .skip_inc
    jmp .sign

.skip_inc:
    inc rdi
    jmp .skip_space

; ---------------------------------------
; Signo
; ---------------------------------------
.sign:
    mov r13d, 1
    cmp byte [rdi], '-'
    jne .check_plus
    mov r13d, -1
    inc rdi
    jmp .convert

.check_plus:
    cmp byte [rdi], '+'
    jne .convert
    inc rdi

; ---------------------------------------
; Conversión
; ---------------------------------------
.convert:
    xor r14d, r14d            ; value = 0

.convert_loop:
    mov bl, [rdi]
    test bl, bl
    jz .done

    xor rcx, rcx
.find_char:
    cmp rcx, r12
    je .error
    cmp bl, [rsi + rcx]
    je .found
    inc rcx
    jmp .find_char

.found:
    imul r14d, r12d           ; value *= base_len
    add r14d, ecx             ; value += digit
    inc rdi
    jmp .convert_loop

; ---------------------------------------
; Final
; ---------------------------------------
.done:
    imul r14d, r13d           ; aplicar signo
    mov eax, r14d
    jmp .exit

.error:
    xor eax, eax

.exit:
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits