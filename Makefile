KERNELBIN=danos.bin
SRCDIR = src

CPU=i686
AS= nasm
CXX= /opt/cross/bin/$(CPU)-elf-g++
LD= $(CXX:g++=ld)
WARNINGS= #-Wall -Wextra
ASFLAGS=-f elf32 -I$(SRCDIR)
CFLAGS= -m32 -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti $(WARNINGS) -I$(SRCDIR)
LFLAGS= -T $(SRCDIR)/link.ld

CFILES= $(shell find $(SRCDIR) -type f -name '*.cpp')
ASMFILES= $(shell find $(SRCDIR) -type f -name '*.asm')
OBJ=$(CFILES:.cpp=.cpp.o) $(ASMFILES:.asm=.asm.o)

.PHONY: all clean new

all: $(KERNELBIN) 

$(KERNELBIN): $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(KERNELBIN)

%.cpp.o: %.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

%.asm.o: %.asm
	$(AS) $(ASFLAGS)  $< -o $@

%.asm:

clean: 
	rm -f  $(OBJ) $(KERNELBIN)

new: clean all