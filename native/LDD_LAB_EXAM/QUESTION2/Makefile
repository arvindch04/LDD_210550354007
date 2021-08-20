obj-m := IOCTL.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o writeapp writeapp.c
	gcc -o IOCTLapp IOCTLapp.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm writeapp
	rm IOCTLapp

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	
