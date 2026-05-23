global ft_list_push_front
extern malloc

section .text

; void ft_list_push_front(t_list **begin_list, void *data)
; rdi = begin_list
; rsi = data

ft_list_push_front:
    push rbx
    push r12
    sub rsp, 8              ; alineación ABI

    mov rbx, rdi            ; guardar begin_list
    mov r12, rsi            ; guardar data

    mov rdi, 16             ; sizeof(t_list)
    call malloc
    test rax, rax
    je .end

    mov [rax], r12          ; new->data = data
    mov rcx, [rbx]          ; old head
    mov [rax + 8], rcx      ; new->next = old head
    mov [rbx], rax          ; *begin_list = new

.end:
    add rsp, 8
    pop r12
    pop rbx
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
