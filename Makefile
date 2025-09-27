# PionnerOS Projesi Makefile
# make komutunun ne yapacağını anlatır.

AS = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386
CFLAGS = -m32 -nostdlib -ffreestanding -g

all: pionneros_orbital.img

run: all
	$(QEMU) -fda pionneros_orbital.img -boot a

pionneros_orbital.img: boot.o kernel.o
	$(LD) -m elf_i386 -T linker.ld -o kernel.elf boot.o kernel.o
	objcopy -O binary kernel.elf kernel.bin
	cat kernel.bin /dev/zero | head -c 1440k > pionneros_orbital.img

boot.o: boot.asm
	$(AS) -f elf boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

clean:
	rm -f *.o *.elf *.bin *.img
