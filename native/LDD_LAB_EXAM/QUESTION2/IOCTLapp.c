#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "IOCTL.h"





int main()
{
	int FileDesc;

	struct stats dat;
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
		printf("\n\nPress 1 for GETSTATS" );
		scanf("%d", &opt);

	
		switch(opt)
		{
			case 1:
				res=ioctl(fd, NAME_IOCTL_STAT);
				break;

				}
			printf("\n\nstats size :%d", dat.size);
			printf("\nstats buff : %s", dat.buff);
                        printf("\nstats r_w : %d", dat.r_w);
	}

	close(fd);
	return 0;
}

	

