#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#include "IOCTL.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind Kumar");
MODULE_DESCRIPTION("character driver that implements the ioctl functionality to check stats of read write operations");


#define NAME MyCharDevice_stat


//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
static long NAME_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
ssize_t NAME_write(struct file *filp, const char __user *UserBuffer, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *UserBuffer, size_t count, loff_t *offp);




//operations that the driver would provide

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
        .release = NAME_release,
	.unlocked_ioctl = NAME_ioctl,
	.write = NAME_write,
	.read = NAME_read,
      	};

//creating the dev with our given major and minor number
dev_t Mydev= MKDEV(230,0);

// character driver
struct cdev *my_cdev;



struct stats write;


//Init Module
static int __init CharDevice_init(void)
{
	int result;

	//Device register
	result=register_chrdev_region(Mydev,1,"MyCharDevice_stat");

	if(result<0)
	{
		printk(KERN_ALERT "\n The region requested for is not obtained\n");
		return(-1);
	}

        printk("\n The major number is: %d and the minor number is: %d\n", MAJOR(Mydev), MINOR(Mydev));

        my_cdev = cdev_alloc();//Allocate memory to char device structure
        my_cdev->ops = &fops;//link our file operations to char device

        result = cdev_add(my_cdev,Mydev,1);//Notify the kernel about the new device
    
       if(result<0)
       {
	    printk(KERN_ALERT "\n the Char Device has not been created ...\n");
	    unregister_chrdev_region(Mydev, 1);
	    return(-1);
       }
    return 0;
}



//cleanup
void __exit CharDevice_exit(void)
{
	
        printk("\n The major number is: %d and the minor number is: %d\n", MAJOR(Mydev), MINOR(Mydev));
	unregister_chrdev_region(Mydev,1);
	cdev_del(my_cdev);
	printk(KERN_ALERT "\nunregistered that allocated ..Bye ..\n");
	return;
}


//system open call
int NAME_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "\n This is kernel open call \n");
	return 0;
}


//system close call
int NAME_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "\n This is the release method of my character driver \n");
	return 0;
}




ssize_t NAME_read(struct file *filp, char __user *UserBuffer, size_t count, loff_t *offp)
{
  char KernelBuffer[] = "It's me Kernel Buffer";
 int res;
 ssize_t value;
 struct stats read;

    res = copy_to_user((char *)UserBuffer,(const char *)KernelBuffer,sizeof(KernelBuffer));
    if(res ==0)
    {
	    printk(KERN_ALERT "\ndata read successfully\n");

	     read.size = count;
	   strcpy(read.buff, KernelBuffer);
	     read.r_w = 0;

	    return value;
    }
    else if(res > 0)
    {
	    printk(KERN_ALERT "\n Part data available\n");
	    value = (count-res);
	    return value;
    }

    else
    {
	    printk(KERN_ALERT "\nIt's an error ,could not write data to user\n");
	    value = EFAULT;
	    return value;
    }

}


ssize_t NAME_write(struct file *filp, const char __user *UserBuffer, size_t count, loff_t *offp)
{
     char KernelBuffer[100];
     int res;
     ssize_t value;
   //  struct stats write;

     res = copy_from_user((char *)KernelBuffer, (char *)UserBuffer , count);

     if(res == 0)
     {
	     printk(KERN_ALERT"\nUser's Message : %s\n",KernelBuffer);
	     printk(KERN_ALERT "\n Number of Bytes written: %d\n",count);
	     write.size = count ;
	     strcpy(write.buff, KernelBuffer);
             write.r_w = 1;
	     return value;
     
     }
     else if(res > 0)
     {
	     printk(KERN_ALERT "\n Part Data Copied");
	     value = (count - res);
	     return value;
     }
     else
     {
	     printk(KERN_ALERT "\n ERROR WRITING ");
	     value = EFAULT;
	     return value;
     }
}

static long NAME_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
        {
		case NAME_IOCTL_STAT:
		{
                //	struct stats write;
		

	
			if (copy_to_user((struct stats*)arg, &write,sizeof(struct stats)))
				return -EFAULT;
			printk(KERN_ALERT "\n stats sent to IOCTL functionality \n");
			return 0;
		}

	

			default:
			return -EINVAL;
	}
}



module_init(CharDevice_init);
module_exit(CharDevice_exit);
