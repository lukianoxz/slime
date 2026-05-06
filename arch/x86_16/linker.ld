OUTPUT_FORMAT (binary)
ENTRY (_start)

SECTIONS {
    . = 0x7C00;
    .boot : {
        KEEP(*(.slm_boot));
    }

    .fill : {
        . = 512 * 128;
        SHORT(0);
    }
}