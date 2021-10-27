KERNEL = mold.kernel

CC ?= gcc
LD ?= ld
ASM ?= nasm

CFLAGS  ?=
LDFLAGS ?=
ASMFLAGS ?= 

INTERNALLDFLAGS :=         \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static                \
	-pie                   \
	--no-dynamic-linker    \
	-ztext

INTERNALCFLAGS :=        \
	-I.                  \
	-ffreestanding       \
	-fno-stack-protector \
	-fpie                \

INTERNALASMFLAGS :=		 \
	-felf64				 \

CFILES      := $(shell find ./ -type f -name '*.c')
ASMFILES    := $(shell find ./ -type f -name '*.asm')
OBJ         := $(CFILES:.c=.o)
OBJ			+= $(ASMFILES:.asm=.o_asm)
HEADER_DEPS := $(CFILES:.c=.d)
HEADER_DEPS += $(ASMFILES:.asm=.d)

all: $(KERNEL)

header:
	curl https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h -o stivale2.h

$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
	rm -rf $(OBJ) $(HEADER_DEPS)

-include $(HEADER_DEPS)

%.o: %.c header
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o_asm: %.asm
	$(ASM) $< $(ASMFLAGS) $(INTERNALASMFLAGS) -o $@