#
#		Specify Build Parameters
KERNEL= danos

BUILD_DIR= build

KERNEL_BIN= $(BUILD_DIR)/$(KERNEL).bin
KERNEL_HD= $(BUILD_DIR)/$(KERNEL).hd

SRC_DIR= src
RUN_DIR= run

#		Bootloader Definitions
LIMINE_URL= https://github.com/limine-bootloader/limine.git
LIMINE_DIR= $(BUILD_DIR)/limine
LIMINE_BIN= limine.bin

#		WSL Switch
# If you're running in WSL specify here otherwise leave blank
ENV= wsl

ifeq ($(ENV),wsl)
# Filter console junk from HAXM
HAXM_FILTER= | grep -Ev "^(HAX is working|VCPU shutdown).*"

# QEMU flags windows
QEMU=qemu-system-x86_64.exe
QEMUFLAGS= -m 2G -no-reboot -no-shutdown -accel hax -serial stdio -drive file=$(KERNEL_HD),format=raw  $(HAXM_FILTER)
else

# QEMU flags Linux
QEMU=qemu-system-x86_64
QEMUFLAGS= -m 2G -no-reboot -serial stdio -drive file=$(KERNEL_HD),format=raw
endif

#		Target Architecture
CPU= x86_64

#		Cross Compiler Location
AS= nasm
CXX= $(HOME)/opt/cross/bin/$(CPU)-elf-g++
LD= $(CXX:g++=ld)

#		Compiler Flags
ASFLAGS= -felf64 -I$(SRC_DIR)
CFLAGS= -masm=intel  				    \
		-fno-pic					    \
		-mno-red-zone                   \
		-mcmodel=kernel                 \
		-ffreestanding                  \
		-fno-stack-protector            \
		-fno-omit-frame-pointer         \
		-I$(SRC_DIR)
	
WARNINGS= #-Wall -Wextra
LFLAGS= -lgcc					 \
		-nostdlib				 \
		-no-pie					 \
		-z max-page-size=0x1000	 \
		-T $(SRC_DIR)/link.ld

#		File Locations
CFILES= $(shell find $(SRC_DIR) -type f -name '*.cpp')
ASMFILES= $(shell find $(SRC_DIR) -type f -name '*.asm')
DEPFILES= $(addprefix $(BUILD_DIR)/,$(CFILES:.cpp=.cpp.d))
OBJ=$(addprefix $(BUILD_DIR)/, $(CFILES:.cpp=.cpp.o) $(ASMFILES:.asm=.asm.o))

# Housekeeping Macros
QUIET= 2> /dev/null
DONE= @echo "\r \e[32m✓\e[39m"
GAP=@echo ""

define STAGE
@echo -n " \e[33m?\e[39m $(1)"
endef


.PHONY: all clean clean-hd clean-loader clean-sys-h clean-all stub-headers new run

all: $(KERNEL_HD) run

#		Link Binary
$(KERNEL_BIN): $(OBJ)
	$(GAP)
	$(call STAGE, Building: $(KERNEL_BIN))
	@$(CXX) $(OBJ) $(LFLAGS) -o $(KERNEL_BIN)
	$(DONE)

#		Compile C++
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(call STAGE, Compiling: $<)
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -MMD -c $< -o $@
	$(DONE)

#		Complie ASM
$(BUILD_DIR)/%.asm.o: %.asm
	$(call STAGE, Compiling: $<)
	@$(AS) $(ASFLAGS)  $< -o $@
	$(DONE)

# tie loose end
%.asm:

#		Build Kernel Image
$(KERNEL_HD): $(LIMINE_DIR) $(KERNEL_BIN) clean-hd
	$(call STAGE, Building HDD image.)
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNEL_HD) $(QUIET)
	@parted -s $(KERNEL_HD) mklabel msdos  $(QUIET)
	@parted -s $(KERNEL_HD) mkpart primary 1 100%  $(QUIET)
	@echfs-utils -m -p0 $(KERNEL_HD) quick-format 32768 
	@echfs-utils -m -p0 $(KERNEL_HD) import $(KERNEL_BIN) $(KERNEL).bin
	@echfs-utils -m -p0 $(KERNEL_HD) import $(RUN_DIR)/limine.cfg limine.cfg 
# install bootloader 
	@$(LIMINE_DIR)/limine-install $(LIMINE_DIR)/$(LIMINE_BIN) $(KERNEL_HD) 
	$(DONE)

#		Build Bootloader
$(LIMINE_DIR):
	$(call STAGE, Building Bootloader.)
	@git clone $(LIMINE_URL) $(LIMINE_DIR)  $(QUIET)
	@make limine-install -C $(LIMINE_DIR) --silent $(QUIET)
	$(DONE)
	$(GAP)


#		Cleaning
clean: 
	$(call STAGE, Cleaning temporary files.)
	@rm -f  $(OBJ) $(KERNEL_BIN) $(DEPFILES)
	@rm -d -r -f $(BUILD_DIR)/$(SRC_DIR)
	$(DONE)

clean-hd:
	$(call STAGE, Cleaning hard disk.)
	@rm -f $(KERNEL_HD)
	$(DONE)
	

clean-loader:
	$(call STAGE, Cleaning bootloader files.)
	@rm -d -r -f $(LIMINE_DIR)
	$(DONE)



clean-all: 
	$(call STAGE, Cleaning All Build files.)
	@rm -d -r -f $(BUILD_DIR)
	$(DONE)
	$(GAP)

#		Clean and Build
new: clean all

#		Run!
run: $(KERNEL_HD)
	@echo "\nRunning...\n"
	@$(QEMU) $(QEMUFLAGS)
