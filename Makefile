KERNELBIN=danos.bin
KERNELHD=danos.hd
HDSIZE=1G
SRCDIR = src

CPU=i686
AS= nasm
CXX= /opt/cross/bin/$(CPU)-elf-g++
LD= $(CXX:g++=ld)
WARNINGS= #-Wall -Wextra
ASFLAGS=-f elf32 -I$(SRCDIR)
CFLAGS= -m32 -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti $(WARNINGS) -I$(SRCDIR)
LFLAGS= -T $(SRCDIR)/link.ld

QEMU=qemu-system-x86_64
QEMUFLAGS=-m 2G -enable-kvm -smp 4 -debugcon stdio -kernel $(KERNELBIN) -hda $(KERNELHD)

CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp')
ASMFILES= $(shell find $(SRCDIR) -type f -name '*.asm')
DEPFILES= $(CFILES:.cpp=.cpp.d)
OBJ=$(CFILES:.cpp=.cpp.o) $(ASMFILES:.asm=.asm.o)

.PHONY: all clean new run

all: $(KERNELBIN) 

$(KERNELBIN): $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(KERNELBIN)

%.cpp.o: %.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

%.asm.o: %.asm
	$(AS) $(ASFLAGS)  $< -o $@

%.asm:

$(KERNELHD):
	qemu-img create -f qcow2 $(KERNELHD) $(HDSIZE)

clean: 
	rm -f  $(OBJ) $(KERNELBIN) $(DEPFILES)

clean-hd:
	rm -f $(OBJ) $(KERNELHD)

new: clean all

run: $(KERNELBIN) $(KERNELHD)
	$(QEMU) $(QEMUFLAGS) 
