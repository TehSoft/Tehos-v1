AS = nasm
CC = g++
LD = ld
USB = /dev/sda

BOOT = boot/boot.asm
LINKER = boot/linker.ld
GRUBCFG = boot/grub.cfg

ASFLAGS = -f elf64

CFLAGS = \
-m64 \
-std=c++11 \
-ffreestanding \
-fno-builtin \
-fno-exceptions \
-fno-rtti \
-fno-stack-protector \
-fcf-protection=none \
-mno-red-zone \
-O2 \
-c \
-Isystem\
-Itehlibs

all: myos.iso

boot.o:
	$(AS) $(ASFLAGS) $(BOOT) -o boot.o

kernel.o:
	$(CC) $(CFLAGS) system/kernel.cc -o kernel.o

tehdisk.o:
	$(CC) $(CFLAGS) tehlibs/tehdisk.cc -o tehdisk.o

tehmbr.o:
	$(CC) $(CFLAGS) tehlibs/tehmbr.cc -o tehmbr.o

tehfs.o:
	$(CC) $(CFLAGS) system/tehfs.cc -o tehfs.o

tehlang.o:
	$(CC) $(CFLAGS) system/tehlang.cc -o tehlang.o

tehconsole.o:
	$(CC) $(CFLAGS) system/tehconsole.cc -o tehconsole.o

tehstr.o:
	$(CC) $(CFLAGS) tehlibs/tehstr.cc -o tehstr.o

tehsound.o:
	$(CC) $(CFLAGS) tehlibs/tehsound.cc -o tehsound.o

tehwait.o:
	$(CC) $(CFLAGS) tehlibs/tehwait.cc -o tehwait.o

tehoutput.o:
	$(CC) $(CFLAGS) tehlibs/tehoutput.cc -o tehoutput.o

tehinput.o:
	$(CC) $(CFLAGS) tehlibs/tehinput.cc -o tehinput.o

myos.bin: boot.o kernel.o tehinput.o tehoutput.o tehdisk.o tehmbr.o tehfs.o tehlang.o tehconsole.o tehstr.o tehwait.o tehsound.o
	$(LD) \
	-m elf_x86_64 \
	-T $(LINKER) \
	-o myos.bin \
	boot.o \
	kernel.o \
	tehdisk.o \
	tehmbr.o \
	tehfs.o \
	tehlang.o \
	tehconsole.o \
	tehstr.o \
	tehwait.o \
	tehsound.o \
	tehinput.o \
	tehoutput.o

myos.iso: myos.bin
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/
	cp $(GRUBCFG) isodir/boot/grub/grub.cfg
	grub-mkrescue \
	-o myos.iso \
	isodir
	rm -f *.o *.bin
	rm -rf isodir

run: myos.iso
	qemu-system-x86_64 \
        -audiodev alsa,id=snd0 \
        -machine pc,pcspk-audiodev=snd0 \
        -cdrom myos.iso \
        -m 512M \
        -drive file=disk.img,format=raw,index=0,media=disk

log: myos.iso
	qemu-system-x86_64 \
        -audiodev alsa,id=snd0 \
        -machine pc,pcspk-audiodev=snd0 \
        -cdrom myos.iso \
        -m 512M \
        -drive file=disk.img,format=raw,index=0,media=disk \
        -no-reboot \
        -no-shutdown \
        -D qemu.log \
        -d guest_errors,cpu_reset

clean:
	rm -rf *.o *.bin *.iso isodir

save: myos.iso
	sudo dd if=myos.iso of=$(USB) bs=4M status=progress oflag=sync
	sync
