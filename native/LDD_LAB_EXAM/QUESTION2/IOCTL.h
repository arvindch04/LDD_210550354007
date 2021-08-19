#define NAME_MAGIC 'O'



struct stats
{
int size;
int r_w;
char buff[];
};



#define NAME_IOCTL_STAT             _IOWR(NAME_MAGIC, 12, struct stats)

