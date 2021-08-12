#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include<stdlib.h>

int main()
{
	int FileDesc;

        char UserBuffer[] = "DATA DATA DATA DATA----------> KERNEL";
	char KernelBuffer[100];



	FileDesc=open("/dev/MyCharDevice", O_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Opening Device \n");
	       exit(1);
	       
	}

	write(FileDesc,UserBuffer,sizeof(UserBuffer));
	read(FileDesc,KernelBuffer,100);

	printf("\nData which is read from the kernel is : %s ",KernelBuffer);

	close(FileDesc);
}
