CFLAGS=-fno-stack-protector -ffreestanding -fno-builtin
#for compatibility between deferent GCC versions

OBJ=floppy 

all: $(OBJ) 

floppy: bootsect kernel

bootsect: 
	make -C boot

kernel: 
	make -C kern
	cp kern/KERNEL.TOS  /mnt/tos_floppy/KERNEL.TOS
	
compile_only:
	make -C kern
	
#compile the kernel, copy the result to the floppy image and test it with qemu
c: prepare kernel terminate

#compile and test with qemu
ct: c run

terminate:
	umount /mnt/tos_floppy
	sleep 1
	losetup -d /dev/loop0
	
run:
	qemu -fda floppy.img &	

install:
	mkdir /mnt/tos_floppy 
	
prepare:
	losetup /dev/loop0 floppy.img ; mount /dev/loop0 /mnt/tos_floppy;	

clean:
	rm -f $(OBJ) *.o
	make -C boot clean
	make -C kern clean

	
