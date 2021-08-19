obj-m := IOCTL.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o readapp readapp.c
	gcc -o IOCTLapp IOCTLapp.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm readapp
	rm IOCTLapp

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	
