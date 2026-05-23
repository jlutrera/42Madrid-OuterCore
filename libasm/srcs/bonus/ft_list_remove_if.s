; ft_list_remove_if.s
; Prototype: void ft_list_remove_if(t_list **begin_list, void *data_ref, 
;                                  int (*cmp)(), void (*free_fct)(void *));

extern free

section .text
    global ft_list_remove_if

ft_list_remove_if:
    ; Prologue: Save callee-saved registers
    push    rbp
    mov     rbp, rsp
    push    r12             ; Will store pointer to the "current pointer" (t_list **)
    push    r13             ; Will store data_ref
    push    r14             ; Will store cmp function pointer
    push    r15             ; Will store free_fct function pointer
    push    rbx             ; Will store current node (t_list *)
   ; sub     rsp, 8          ; Stack alignment (6 pushes + 8 bytes = 56 + 8 = 64 bytes)

    ; Null check for begin_list
    test    rdi, rdi
    jz      .end
    
    ; Initialize registers with arguments
    mov     r12, rdi        ; r12 = begin_list
    mov     r13, rsi        ; r13 = data_ref
    mov     r14, rdx       ; r14 = cmp
    mov     r15, rcx        ; r15 = free_fct

.loop:
    mov     rbx, [r12]      ; rbx = *r12 (current node)
    test    rbx, rbx        ; if (current == NULL) break
    jz      .end

    ; Call cmp(current->data, data_ref)
    mov     rdi, [rbx]      ; arg1: current->data
    mov     rsi, r13        ; arg2: data_ref
    call    r14

    test    eax, eax        ; if (cmp() == 0) -> remove node
    jz      .remove_node

    ; Else: Move to next node
    ; We set r12 to the address of the current node's 'next' field
    lea     r12, [rbx + 8]  ; r12 = &current->next
    jmp     .loop

.remove_node:
    ; 1. Update the previous pointer (or head) to point to current->next
    mov     rax, [rbx + 8]  ; rax = current->next
    mov     [r12], rax      ; *r12 = current->next

    ; 2. Call free_fct(current->data)
    mov     rdi, [rbx]      ; arg1: current->data
    call    r15

    ; 3. Call free(current node)
    mov     rdi, rbx        ; arg1: current node
    call    free

    ; 4. Re-check the same pointer position (r12 hasn't moved)
    jmp     .loop

.end:
    ; Epilogue
   ;add     rsp, 8
    pop     rbx
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits