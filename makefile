# architecture
ARCH      := x86_16
ARCH_PATH := arch/$(ARCH)

# files
F_BOOT := $(ARCH_PATH)/boot/entry.asm
F_LINK := $(ARCH_PATH)/linker.ld

# make flags
# run after compile
r ?= s
# debug qemu
d ?= n

# logic
all: init clean compile run end

# rotines
init:
	@clear
	@echo --- slime build-system arch $(ARCH) ---
	@echo flags:
	@echo - r: run after compile = $(r)
	@echo - d: debug qemu = $(d)
	@echo

clean:
	@echo [ starting clean rotine ]
	@echo cleaning build
	@rm -rf build
	@mkdir -p build
	@echo

compile:
	@echo [ starting compile rotine ]

	@echo compiling boot
	@$(call compile_boot)

	@echo linking
	@ld -m elf_i386 -T $(F_LINK) -o build/slime.img build/*.o

	@echo 

run:
	@echo [ starting run rotine ]
ifeq ($(r), s)
	@echo running
	@qemu-system-x86_64 -drive format=raw,file=build/slime.img
else
	@echo nothing to do
endif
	@echo

end:
	@echo --- all process finished ---

# sub-rotines
define compile_boot
	@nasm -f elf32 $(F_BOOT) -o build/boot.o
endef