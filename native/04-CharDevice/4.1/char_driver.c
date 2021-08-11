//Q:Write a character driver with open and close functionality .Test the driver by writing an application that opens and closes the device driver.When open or closed the open and close calls in driver should be executed 
//



//Includes

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind Kumar");


#define NAME MyCharDevice


//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);




//operations that the driver would provide

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
        .release = NAME_release,
      	};



// character driver
struct cdev *my_cdev;



//Init Module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);//create a device number
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\n The major number is %d and the minor number is :%d\n", MAJOR,MINOR);

	//Device register
	result=register_chrdev_region(Mydev,1,"MyCharDevice");

	if(result<0)
	{
		printk(KERN_ALERT "\n The region requested for is not obtained\n");
		return(-1);

	}

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
	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
        MINOR=MINOR(Mydev);
	printk("\nThe major number is %d and the minor number is %d\n", MAJOR,MINOR);
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


module_init(CharDevice_init);
module_exit(CharDevice_exit);






