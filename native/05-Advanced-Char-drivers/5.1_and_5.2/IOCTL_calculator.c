//Q:Write a character driver with open and close functionality .Test the driver by writing an application that opens and closes the device driver.When open or closed the open and close calls in driver should be executed. 
//



//Includes

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#include "ioctl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind Kumar");
MODULE_DESCRIPTION("character driver that implements the ioctl functionality to demonstrate the calculator functionality");


#define NAME MyCharDevice_stat


//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
static long NAME_ioctl(struct file *file, unsigned int cmd, unsigned long arg);




//operations that the driver would provide

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
        .release = NAME_release,
	.unlocked_ioctl = NAME_ioctl,
      	};

//creating the dev with our given major and minor number
dev_t Mydev= MKDEV(230,0);

// character driver
struct cdev *my_cdev;



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

static long NAME_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
        {
		case NAME_IOCTL_ADD:
		{
                	struct calc addition;
			memset(&addition, 0, sizeof(struct calc));
			if (copy_from_user(&addition, (struct calc*)arg,sizeof(struct calc)))
				return -EFAULT;

			addition.result = addition.integer1 + addition.integer2;
			if (copy_to_user((struct calc*)arg, &addition,sizeof(struct calc)))
				return -EFAULT;
			printk(KERN_ALERT "\n Kernel :: Add . \n");
			return 0;
		}

		case NAME_IOCTL_SUB:
		{
			struct calc sub;
			memset(&sub, 0, sizeof(struct calc));
			if (copy_from_user(&sub, (struct calc*)arg,sizeof(struct calc)))
				return -EFAULT;
			sub.result = sub.integer1 - sub.integer2;
			if (copy_to_user((struct calc*)arg, &sub,sizeof(struct calc)))
				return -EFAULT;
			printk(KERN_ALERT "\n Kernel :: Sub . \n");
			return 0;
		}

		case NAME_IOCTL_MUL:
		{
			struct calc mul;
			memset(&mul, 0, sizeof(struct calc));
			if (copy_from_user(&mul, (struct calc*)arg,sizeof(struct calc)))
				return -EFAULT;

			mul.result = mul.integer1 * mul.integer2;
			if (copy_to_user((struct calc*)arg, &mul,sizeof(struct calc)))
				return -EFAULT;

			printk(KERN_ALERT "\n Kernel :: MUL . \n");
			return 0;
		}

		case NAME_IOCTL_DIV:
		{
			struct calc div;
			memset(&div, 0, sizeof(struct calc));
			if (copy_from_user(&div, (struct calc*)arg,sizeof(struct calc)))
				return -EFAULT;

			if(div.integer2 == 0)
				return 0;

			div.result = div.integer1 / div.integer2;
			if (copy_to_user((struct calc*)arg, &div,sizeof(struct calc)))
				return -EFAULT;
			printk(KERN_ALERT "\n Kernel :: Div . \n");
			return 0;
		}
		default:
			return -EINVAL;
	}
}



module_init(CharDevice_init);
module_exit(CharDevice_exit);






