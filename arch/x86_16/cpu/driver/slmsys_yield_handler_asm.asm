[BITS 16]

extern slmsys_schelduler
extern slmsys_current_process_sp

global slmsys_yield_handler
slmsys_yield_handler:
    ; save process state
    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di
    push ds
    push es

    ; change to kernel segment
    xor ax, ax
    mov ds, ax             ; kernel segment
    
    ; save stack pointer of this process
    mov bx, [slmsys_current_process_sp]
    mov [bx], sp

    call slmsys_schelduler ; change process

    ; load new stack pointer
    mov bx, [slmsys_current_process_sp]
    mov sp, [bx]

    ; restore process state
    pop es
    pop ds
    pop di
    pop si
    pop bp
    pop bx
    pop dx
    pop cx
    pop ax
    iret