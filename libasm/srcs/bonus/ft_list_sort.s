; ft_list_sort.s
; Prototype: void ft_list_sort(t_list **begin_list, int (*cmp)());

section .text
    global ft_list_sort

ft_list_sort:
    ; Prologue: Save callee-saved registers to maintain the ABI
    push    rbp
    mov     rbp, rsp
    push    r12             ; begin_list (**t_list)
    push    r13             ; cmp function pointer
    push    r14             ; current node (*t_list)
    push    r15             ; next node (*t_list)
    sub     rsp, 8          ; align stack: rsp % 16 == 8 before call

    ; Null checks
    test    rdi, rdi        ; if (begin_list == NULL) return;
    jz      .end
    mov     r12, rdi        ; r12 = begin_list
    mov     r13, rsi        ; r13 = cmp

    mov     r14, [r12]      ; r14 = *begin_list
    test    r14, r14        ; if (*begin_list == NULL) return;
    jz      .end

.restart_sort:
    mov     r14, [r12]      ; current = *begin_list

.loop:
    mov     r15, [r14 + 8]  ; next = current->next
    test    r15, r15
    jz      .end            ; si next == NULL, no hubo swaps en este recorrido → ordenado

    ; cmp(current->data, next->data)
    mov     rdi, [r14]      ; 1er arg: current->data
    mov     rsi, [r15]      ; 2º arg: next->data
    call    r13             ; cmp(current->data, next->data)

    cmp     eax, 0
    jg      .swap           ; si cmp > 0 → swap y reiniciar desde el principio

    ; sin swap, avanzar al siguiente par
    mov     r14, r15
    jmp     .loop

.swap:
    ; Swap de los punteros data entre current y next
    mov     rax, [r14]      ; tmp = current->data
    mov     rdx, [r15]      ; rdx = next->data
    mov     [r14], rdx      ; current->data = next->data
    mov     [r15], rax      ; next->data = tmp

    ; Tras un swap, reiniciar desde el principio para seguir ordenando
    jmp     .restart_sort

.end:
    add     rsp, 8          ; deshacer la alineación
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
