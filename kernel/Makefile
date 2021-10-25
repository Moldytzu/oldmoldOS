KERNEL = mold.kernel

CC ?= gcc
LD ?= ld

CFLAGS  ?= -Wall -Wextra -pipe
LDFLAGS ?=

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

CFILES      := $(shell find ./ -type f -name '*.c')
OBJ         := $(CFILES:.c=.o)
HEADER_DEPS := $(CFILES:.c=.d)

all: $(KERNEL)

header:
	curl https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h -o stivale2.h

$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
	rm -rf $(OBJ) $(HEADER_DEPS)

-include $(HEADER_DEPS)

%.o: %.c header
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@
