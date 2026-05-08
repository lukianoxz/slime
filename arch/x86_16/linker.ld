OUTPUT_FORMAT (binary)
ENTRY (slm_boot_entry)

SECTIONS {
    . = 0x7C00;
    .boot : {
        KEEP(*(.section_slm_boot));
    }

    .kernel : {
        *(.text)
        *(.data)
        *(.rodata)
        *(.bss)
    }

    .fill : {
        . = 512 * 128;
        SHORT(0);
    }
}