OUTPUT_FORMAT (binary)
ENTRY (slm_boot_entry)

SECTIONS {
    . = 0x7C00;
    .boot : {
        KEEP(*(.section_slm_boot));
    }

    . = 0x7E00;
    .text : { *(.text) }
    .data : { *(.data) }
    .rodata : { *(.rodata) }
    .bss : { *(.bss) }

    .fill : {
        . = 512 * 65;
        SHORT(0);
    }
}