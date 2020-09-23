OBJNAME=kdisas
ARCH=arch/x86
engine=${PWD}/beaengine

COMPILER_OPTIONS := -Werror -Wall \
	-Wframe-larger-than=4608 -fno-stack-protector -z execstack
EXTRA_CFLAGS := -I. -I${engine}/include \
	-I${engine}/include/beaengine -I${engine}/src ${COMPILER_OPTIONS}

SRC := kdis.c

$(OBJNAME)-objs = kdis.o

obj-m := kdis.o


all:
	make  -C  /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	@rm -f *.o
	@echo "Clean."

tags:
	find . -iname '*.c' -o -iname '*.h' -o -iname '*.i' -o -iname '*.S' | xargs etags -a

.PHONY: all clean tags
