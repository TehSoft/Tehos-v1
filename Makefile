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
-std=c++17 \
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

OBJ_DIR = objs

all: myos.iso

SRCS := $(wildcard system/*.cc) \
        $(wildcard system/apps/*.cc) \
        $(wildcard tehlibs/*.cc)

OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cc=.o)))


$(OBJ_DIR)/boot.o: $(BOOT)
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.o: system/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: tehlibs/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: system/apps/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

appcollector.ii:
	@echo "// Automatikusan generalt .ii fejlec - NE MODOSITSD!" > system/app_includes.ii
	@for file in system/apps/*.hh; do \
		if [ -f "$$file" ]; then \
			basename=$$(basename $$file); \
			echo "#include \"apps/$$basename\"" >> system/appcollector.ii; \
		fi \
	done

myos.bin: appcollector.ii $(OBJ_DIR)/boot.o $(OBJS)
	$(LD) \
	-m elf_x86_64 \
	-T $(LINKER) \
	-o myos.bin \
	$(OBJ_DIR)/boot.o \
	$(OBJS)

myos.iso: myos.bin
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/
	cp $(GRUBCFG) isodir/boot/grub/grub.cfg
	grub-mkrescue \
	-o myos.iso \
	isodir
	rm -f myos.bin
	rm -rf isodir

run: myos.iso
	qemu-system-x86_64 \
        -audiodev alsa,id=snd0 \
        -machine pc,pcspk-audiodev=snd0 \
        -cdrom myos.iso \
        -m 512M \
        -drive file=disk.img,format=raw,index=0,media=disk
	rm -rf $(OBJ_DIR)

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
	rm -rf $(OBJ_DIR) *.iso

save: myos.iso
	sudo dd if=myos.iso of=$(USB) bs=4M status=progress oflag=sync
	sync
