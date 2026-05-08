[BITS 16]

global slmsys_init_video
global slmsys_quit_video

global slmsys_draw_pixel

slmsys_init_video:
    mov ah, 0x00
    mov al, 0x13
    int 0x10
    ret

slmsys_quit_video:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

slmsys_draw_pixel:
    push bp
    mov bp, sp

    mov ax, 0xA000 ; video memory address
    mov es, ax

    mov ax, [bp + 6] ; y
    mov dx, 320      ; size of row
    mul dx           ; ax * dx (y * 320)
    add ax, [bp + 4] ; x
    mov di, ax       ; di = offset

    mov al, [bp + 8]
    mov [es:di], al

    pop bp
    ret