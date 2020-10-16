ARCH=arch/x86

COMPILER_OPTIONS := -Werror -Wall
EXTRA_CFLAGS := -I.

SRC := knf.c

$(OBJNAME)-objs = knf.o

obj-m := knf.o

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
