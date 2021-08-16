#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "ioctl.h"





int main()
{
	int FileDesc;

	struct calc dat;
	int opt;
	int fd, res=0;

	fd = open("/dev/MyCharDevice_stat", O_RDWR);
	if(fd < 0)
	{
		perror("open:");
		return -1;
	}

	while(1)
	{
		printf("\n\n1 for Add\n2 for Sub\n3 for Mul\n4 for Div\n\n5.ExitApp\n\nChoose Operation:" );
		scanf("%d", &opt);

		if(opt == 5)
			break;

		if(opt < 1 || opt > 4)
		{
  			printf("\n Invalid Option... ");
			continue;
		}

		printf("\n\nEnter integer1:");
		scanf("%d", &dat.integer1);

		printf("\n\nEnter integer2:");
		scanf("%d", &dat.integer2);

		switch(opt)
		{
			case 1:
				res=ioctl(fd, NAME_IOCTL_ADD, &dat);
				break;

			case 2:
				res=ioctl(fd, NAME_IOCTL_SUB, &dat);
				break;
			case 3:
				res=ioctl(fd, NAME_IOCTL_MUL, &dat);
				break;
			case 4:
				res= ioctl(fd, NAME_IOCTL_DIV, &dat);
				break;
		}
			printf("\n\nResult is :%d", dat.result);
	}

	close(fd);
	return 0;
}

	

