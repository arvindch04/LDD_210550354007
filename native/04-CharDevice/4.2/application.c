#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int FileDesc;

        char UserBuffer[] = "It's me user buffer";
	char KernelBuffer[100];



	FileDesc=open("/dev/my_char_device_stat", O_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Opening Device \n");
	       exit(1);
	       
	}

	write(FileDesc,UserBuffer,sizeof(UserBuffer));
	read(FileDesc,KernelBuffer,100);

	printf("\nData which is read from the kernel is : %s\n ",KernelBuffer);

	close(FileDesc);
}

