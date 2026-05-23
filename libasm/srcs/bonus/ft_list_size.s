global ft_list_size

section .text

; int ft_list_size(t_list *begin_list)
;   rdi = begin_list
;   eax = return

ft_list_size:
    push rbp            ; guardar rbp (callee-saved estándar)
    mov rbp, rsp

    ; No hay llamadas externas, así que la pila no necesita realineación extra.
    ; Solo usamos rax para el contador y rdi para iterar.

    xor rax, rax        ; size = 0

.loop:
    test rdi, rdi       ; if begin_list == NULL, salir
    je .end

    inc rax             ; size++
    mov rdi, [rdi + 8]  ; begin_list = begin_list->next
    jmp .loop

.end:
    pop rbp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
