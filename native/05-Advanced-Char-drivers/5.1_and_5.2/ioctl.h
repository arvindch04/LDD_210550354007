#define NAME_MAGIC 'O'



struct calc
{
	int integer1;
	int integer2;
	int result;
};



#define NAME_IOCTL_ADD             _IOWR(NAME_MAGIC, 8, struct calc)
#define NAME_IOCTL_SUB             _IOWR(NAME_MAGIC, 9, struct calc)
#define NAME_IOCTL_DIV             _IOWR(NAME_MAGIC, 10, struct calc)
#define NAME_IOCTL_MUL             _IOWR(NAME_MAGIC, 11, struct calc)

