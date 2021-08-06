mkdir \out
mkdir \out\tmp
nasm boot/bootsect.asm -o out/bootsect.o -Iboot
nasm kernel/kernel_entry.asm -f elf32 -o out/kernel_entry.o

gcc -g -m32 -c kernel/kernel.c -o out/kernel.o -ffreestanding -nostdlib -nostdinc
gcc -g -m32 -c drivers/ports.c -o out/ports.o -ffreestanding -nostdlib -nostdinc

ld -m i386pe -o out/kernel.tmp -Ttext 0x1000 out/kernel_entry.o out/ports.o out/kernel.o
objcopy -O binary -j .text  out/kernel.tmp out/kernel.bin
type .\out\bootsect.o .\out\kernel.bin > .\out\os.bin