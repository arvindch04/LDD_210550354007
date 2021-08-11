#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include<stdlib.h>

int main()
{
	int FileDesc;

	FileDesc=open("/dev/MyCharDevice", O_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Opening Device \n");
	       exit(1);
	       
	}

	close(FileDesc);
}

