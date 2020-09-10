KERNELBIN=danos.bin
KERNELHD=danos.hd
HDSIZE=1G
SRCDIR=src
TEMPDIR=temp
RUNDIR= run

LIMINE_URL= https://github.com/limine-bootloader/limine.git
LIMINE_DIR= limine

CPU=x86_64
AS= nasm
CXX= $(HOME)/opt/cross/bin/$(CPU)-elf-g++
LD= $(CXX:g++=ld)

ASFLAGS=-felf64 -I$(SRCDIR)
CFLAGS=  -masm=intel  			    \
	-fno-pic					    \
	-mno-red-zone                   \
	-mcmodel=kernel                 \
	-ffreestanding                  \
	-fno-stack-protector            \
	-fno-omit-frame-pointer         \
	-I$(SRCDIR)
WARNINGS= #-Wall -Wextra
LFLAGS= -lgcc \
	-nostdlib \
	-no-pie   \
	-z max-page-size=0x1000 \
	-T $(SRCDIR)/link.ld

QEMU=qemu-system-x86_64
QEMUFLAGS= -m 2G -no-reboot -serial stdio -drive file=$(KERNELHD),format=raw

ifeq ($(testing), on)
CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp')
else
CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp' -not -path 'src/test/*')
endif

ASMFILES= $(shell find $(SRCDIR) -type f -name '*.asm')
DEPFILES= $(addprefix $(TEMPDIR)/,$(CFILES:.cpp=.cpp.d))
OBJ=$(addprefix $(TEMPDIR)/, $(CFILES:.cpp=.cpp.o) $(ASMFILES:.asm=.asm.o))


.PHONY: all clean clean-hd clean-loader clean-all new run

all: $(KERNELHD) run

$(KERNELBIN): $(OBJ)
	@echo -n "\nBuilding: $(KERNELBIN)"
	@$(CXX) $(OBJ) $(LFLAGS) -o $(KERNELBIN)
	@echo "  ..Done.\n"

$(TEMPDIR)/%.cpp.o: %.cpp
	@echo "Compiling: $<"
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -MMD -c $< -o $@

$(TEMPDIR)/%.asm.o: %.asm
	@echo "Compiling: $<"
	@$(AS) $(ASFLAGS)  $< -o $@

%.asm:

$(KERNELHD): $(LIMINE_DIR) $(KERNELBIN) clean-hd
	@echo -n "Building HDD image...\n"
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNELHD)
	@parted -s $(KERNELHD) mklabel msdos
	@parted -s $(KERNELHD) mkpart primary 1 100%
	@echfs-utils -m -p0 $(KERNELHD) quick-format 32768
	@echfs-utils -m -p0 $(KERNELHD) import $(KERNELBIN) $(KERNELBIN)
	@echfs-utils -m -p0 $(KERNELHD) import $(RUNDIR)/limine.cfg limine.cfg
	@make -C $(LIMINE_DIR)
	@$(LIMINE_DIR)/limine-install $(KERNELHD)
	@echo " ..Done."

$(LIMINE_DIR):
	git clone $(LIMINE_URL) $(LIMINE_DIR) --depth=1 --branch=v0.4

clean: 
	@echo -n "Cleaning temporary files..."
	@rm -f  $(OBJ) $(KERNELBIN) $(DEPFILES)
	@rm -d -r -f $(TEMPDIR)
	@echo "  ..Done.\n"

clean-hd:
	@echo -n "Cleaning hard disk..."
	@rm -f $(KERNELHD)
	@echo " ..Done.\n"

clean-loader:
	@echo -n "Cleaning bootloader files..."
	@rm -d -r -f $(LIMINE_DIR)
	@echo "  ..Done.\n"


clean-all: clean clean-hd

new: clean-all all

run: $(KERNELHD)
	@echo "Running...\n"
	@$(QEMU) $(QEMUFLAGS)
