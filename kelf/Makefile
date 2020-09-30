ARCH=arch/x86

COMPILER_OPTIONS := -Werror -Wall
#COMPILER_OPTIONS := -Werror -Wall \
#	-Wframe-larger-than=4608 -fno-stack-protector -z execstack
EXTRA_CFLAGS := -I.

SRC := kelf.c

$(OBJNAME)-objs = kelf.o

obj-m := kelf.o

all:
	make  -C  /lib/modules/$(shell uname -r)/build M=$(PWD) modules

lgtm:
	make  -C  /lib/modules/$(shell dpkg --status linux-headers-generic |grep ^Depends| \
		cut -d ":" -f2| sed 's/ linux-headers-//g')/build M=$(PWD) modules

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	@rm -f *.o
	@echo "Clean."

tags:
	find . -iname '*.c' -o -iname '*.h' -o -iname '*.i' -o -iname '*.S' | xargs etags -a

.PHONY: all clean tags
