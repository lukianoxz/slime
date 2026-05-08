C_COMPILER := ia16-elf-gcc
C_FLAGS := \
	-c \
	-march=i8086 \
	-ffreestanding \
	-fno-stack-protector
C_INCLUDE := \
	-Ikernel/include \
	-Ikernel/driver

C_ := $(C_COMPILER) $(C_FLAGS) $(C_INCLUDE)