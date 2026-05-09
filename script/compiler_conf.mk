C_COMPILER := ia16-elf-gcc
C_FLAGS := \
	-c \
	-march=i8086 \
	-ffreestanding \
	-fno-stack-protector \
	-mcmodel=small \
	-nostdlib

C_ := $(C_COMPILER) $(C_FLAGS) -Ilibc/include