KERNELBIN=danos.bin
KERNELHD=danos.hd
HDSIZE=1G
SRCDIR=src
TEMPDIR=temp
RUNDIR= run

LIMINE_URL= https://github.com/limine-bootloader/limine.git
LIMINE_DIR= limine
LIMINE_BIN= limine.bin

#Provides a switch to run qemu on windows rather than in wsl
ENV=wsl

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

QUIET= 2> /dev/null
DONE= @echo "\r \e[32m✓\e[39m"
GAP=@echo ""

define STAGE
@echo -n " \e[33m?\e[39m $(1)"
endef

# when using wsl it make no sense to emulate an emulator so qemu flags change
ifeq ($(ENV),wsl)
HAXM_FILTER= | findstr.exe /bv /c:"VCPU" /c:"HAX"
QEMU=qemu-system-x86_64.exe
QEMUFLAGS= -m 2G -no-reboot -accel hax -serial stdio -drive file=$(KERNELHD),format=raw $(HAXM_FILTER)
else
QEMU=qemu-system-x86_64
QEMUFLAGS= -m 2G -no-reboot -serial stdio -drive file=$(KERNELHD),format=raw
endif


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
	$(GAP)
	$(call STAGE, Building: $(KERNELBIN))
	@$(CXX) $(OBJ) $(LFLAGS) -o $(KERNELBIN)
	$(DONE)

$(TEMPDIR)/%.cpp.o: %.cpp
	$(call STAGE, Compiling: $<)
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -MMD -c $< -o $@
	$(DONE)

$(TEMPDIR)/%.asm.o: %.asm
	$(call STAGE, Compiling: $<)
	@$(AS) $(ASFLAGS)  $< -o $@
	$(DONE)

%.asm:

$(KERNELHD): $(LIMINE_DIR) $(KERNELBIN) clean-hd
	$(call STAGE, Building HDD image.)
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNELHD) $(QUIET)
	@parted -s $(KERNELHD) mklabel msdos  $(QUIET)
	@parted -s $(KERNELHD) mkpart primary 1 100%  $(QUIET)
	@echfs-utils -m -p0 $(KERNELHD) quick-format 32768 
	@echfs-utils -m -p0 $(KERNELHD) import $(KERNELBIN) $(KERNELBIN) 
	@echfs-utils -m -p0 $(KERNELHD) import $(RUNDIR)/limine.cfg limine.cfg 
	
	@$(LIMINE_DIR)/limine-install $(LIMINE_DIR)/$(LIMINE_BIN) $(KERNELHD) 
	$(DONE)

$(LIMINE_DIR):
	$(call STAGE, Building Bootloader.)
	@git clone $(LIMINE_URL) $(LIMINE_DIR)  $(QUIET)
	@make limine-install -C $(LIMINE_DIR) --silent $(QUIET)
	$(DONE)
	$(GAP)

clean: 
	$(call STAGE, Cleaning temporary files.)
	@rm -f  $(OBJ) $(KERNELBIN) $(DEPFILES)
	@rm -d -r -f $(TEMPDIR)
	$(DONE)

clean-hd:
	$(call STAGE, Cleaning hard disk.)
	@rm -f $(KERNELHD)
	$(DONE)
	

clean-loader:
	$(call STAGE, Cleaning bootloader files.)
	@rm -d -r -f $(LIMINE_DIR)
	$(DONE)


clean-all: clean clean-hd clean-loader
	$(GAP)


new: clean-all all

run: $(KERNELHD)
	@echo "\nRunning...\n"
	@$(QEMU) $(QEMUFLAGS)
