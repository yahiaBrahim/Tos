CFLAGS= -lgcc -g -Wall -Winline -fno-stack-protector -ffreestanding -nostdinc -nostdlib -fno-strict-aliasing -m32
#for compatibility between deferent GCC versions

OBJ=KERNEL
CC=gcc -w

all: $(OBJ) 

KERNEL: asmEntry.o kernel.o  
	ld -static -nostdlib -Tlink.ld -o KERNEL.TOS $^
	
asmEntry.o:asmEntry.asm
	nasm -f elf $^ -o $@

.o: .c 
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ) *.o
