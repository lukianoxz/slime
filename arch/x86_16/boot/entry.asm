; origin = 0x7C00 in linker.ld
[BITS 16]
section .slm_boot

global _start
_start:
    cli ; off interruptions
    mov [boot_disk], dl ; boot disk number

    ; config segments
    xor ax, ax ; ax = 0
    mov ds, ax ; data segment
    mov es, ax ; extra segment

    ; config stack
    mov ss, ax     ; stack segment (ax = 0)
    mov sp, 0x7C00 ; stack pointer
    mov bp, sp     ; stack base pointer

    mov si, msg_entry
    call print
    mov si, msg_disk_load
    call print

    ; load disk sectors
    mov ah, 0x02        ; read sectors
    mov al, 1           ; sectors to read
    mov ch, 0           ; cylinder
    mov cl, 2           ; start from (sectors start in 1)
    mov dh, 0           ; head
    mov dl, [boot_disk] ; disk
    mov bx, 0x7E00      ; destine
    int 0x13

    jc disk_error ; if disk read error

    mov si, msg_disk_success
    call print

    jmp $

; functions
; need si pointer to a string before call
print:
    mov ah, 0x0E ; teletype output
    mov bx, 0x0F ; page 0, white color
.loop:
    lodsb     ; load to al one byte of string and inc si
    cmp al, 0 ; compare al with 0 (null terminator)
    je .end   ; if compare is true

    ; else
    int 0x10  ; bios interrupt
    jmp .loop ; return to init of loop
.end:
    ret

disk_error:
    mov si, msg_disk_error
    call print
    hlt

; messages (format: string, null terminator (0))
; initial message
msg_entry: db "> slime", 13, 10, "> boot succefull initiated", 13, 10, 0

; disk message
msg_disk_load: db "> loading disk", 13, 10, 0
msg_disk_error: db "> error after trying load disk", 13, 10, 0
msg_disk_success: db "> disk succefull loaded", 13, 10, 0

boot_disk db 0

; assinature
times 510 - ($ - $$) db 0 ; fill with 0 after boot
dw 0xAA55 ; boot assinature (in 510, 512)