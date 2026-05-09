OUTPUT_FORMAT(binary)
ENTRY(main)

SECTIONS {
    . = 0x0;
    .app : {
        *(.text)
        *(.data)
        *(.rodata)
        *(.bss)
    }
}