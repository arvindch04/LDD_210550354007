#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{
	int FileDesc;
	char Ubuff[] = "This is user buffer ...sending data to kernel ..";
        char kbuff[100];
	FildeDesc=open("/dev/MyCharDevice", 0_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Openinf Device \n");
	       exit(1);
	       
	}

//	write(FileDesc,Ubuff, sizeof(Ubuff));
//	read(FilDesc,kbuff,50);

	printf("\n The data read from the kernel is \n %s", kbuff);
	close(FileDesc);
}

