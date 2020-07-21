KERNELBIN=danos.bin
KERNELHD=danos.hd
HDSIZE=1G
SRCDIR=src
TEMPDIR=temp

INCLUDE_TEST= false

CPU=i686
AS= nasm
CXX= /opt/cross/bin/$(CPU)-elf-g++
LD= $(CXX:g++=ld)
WARNINGS= #-Wall -Wextra
ASFLAGS=-f elf32 -I$(SRCDIR)
CFLAGS= -m32 -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti $(WARNINGS) -I$(SRCDIR)
LFLAGS= -T $(SRCDIR)/link.ld

QEMU=qemu-system-x86_64
QEMUFLAGS= -m 2G -smp 4 -no-reboot -serial stdio -kernel $(KERNELBIN) -hda $(KERNELHD)

ifeq ($(INCLUDE_TEST), false)
CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp' -not -path 'src/test/*')
else
CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp')
endif

ASMFILES= $(shell find $(SRCDIR) -type f -name '*.asm')
DEPFILES= $(addprefix $(TEMPDIR)/,$(CFILES:.cpp=.cpp.d))
OBJ=$(addprefix $(TEMPDIR)/, $(CFILES:.cpp=.cpp.o) $(ASMFILES:.asm=.asm.o))


.PHONY: all clean clean-hd new run

all: $(KERNELBIN) run

$(KERNELBIN): $(OBJ)
	@echo "Building: $(KERNELBIN)"
	@$(LD) $(OBJ) $(LFLAGS) -o $(KERNELBIN)
	@echo "Done."

$(TEMPDIR)/%.cpp.o: %.cpp
	@echo "Compiling: $<"
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -MMD -c $< -o $@

$(TEMPDIR)/%.asm.o: %.asm
	@echo "Compiling: $<"
	@$(AS) $(ASFLAGS)  $< -o $@

%.asm:

$(KERNELHD):
	qemu-img create -f qcow2 $(KERNELHD) $(HDSIZE)

clean: 
	@echo "Cleaning temporary files..."
	@rm -f  $(OBJ) $(KERNELBIN) $(DEPFILES)
	@rm -d -r -f temp
	@echo "Done."

clean-hd:
	@echo "Cleaning hard disk..."
	@rm -f $(OBJ) $(KERNELHD)
	@echo "Done."

clean-all: clean clean-hd

new: clean-all all

run: $(KERNELBIN) $(KERNELHD)
	@echo "Running...\n"
	@$(QEMU) $(QEMUFLAGS)
