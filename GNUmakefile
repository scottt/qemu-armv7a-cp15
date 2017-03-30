IMAGE     := cp15.elf
S_OBJS    := $(addsuffix .o,$(basename $(filter-out link.ld.S,$(wildcard *.S))))
C_OBJS    := $(addsuffix .o,$(basename $(wildcard *.c)))
H_DEPS    := cp15.h
LD_SCRIPT := link.ld.S

LIBS := $(shell $(CC) $(CCFLAGS) -print-libgcc-file-name)
CFLAGS := -fno-builtin -Os -g3
CFLAGS += -march=armv7-a
LDFLAGS := -nostdlib

CROSS_COMPILE ?= arm-non-eabi-

# qemu-system-arm -M virt
export ARCH := ARCH_ARM
export UART_PHYS := 0x09000000
export ENTRY_POINT := 0x4000000
export BOARD_MODEL := VIRT

all: $(IMAGE)

clean:
	rm -rf $(IMAGE) $(S_OBJS) $(C_OBJS) link.ld $(IMAGE).map

$(IMAGE): $(S_OBJS) $(C_OBJS) $(H_DEPS) link.ld GNUmakefile
	$(CC) -o $@ $(S_OBJS) $(C_OBJS) $(LIBS) $(LDFLAGS) \
		-Wl,--script=link.ld \
		-Wl,-Map=$(IMAGE).map

link.ld: $(LD_SCRIPT)
	$(CC) -DENTRY_POINT=$(ENTRY_POINT) -D$(ARCH) $(CPPFLAGS) -E -P -C -o $@ $<

%.o: %.c $(H_DEPS)
	$(CC) -DENTRY_POINT=$(ENTRY_POINT) -D$(BOARD_MODEL) \
          -DUART_PHYS=$(UART_PHYS) -D$(ARCH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.S $(H_DEPS)
	$(CC) -D$(ARCH) $(CPPFLAGS) -c -o $@ $<

.PHONY: all clean

.PHONY: qemu
qemu:
	qemu-system-arm -M virt -cpu cortex-a15 -s -S

.PHONY: gdb
gdb: $(IMAGE)
	$(GDB) -q -x qemu-connect.gdb -x cp15-demo.gdb
