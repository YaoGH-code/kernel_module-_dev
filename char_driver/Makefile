ifneq ($(KERNELRELEASE),)
obj-m := hellodev.o
else
PWD := $(CURDIR) 
#KDIR:= /lib/modules/4.4.0-31-generic/build
KDIR := /lib/modules/`uname -r`/build
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
clean:
	rm -rf *.o *.ko *.mod.c *.symvers *.c~ *~
endif
