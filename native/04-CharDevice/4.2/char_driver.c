//Q:Write a character driver with open,read,write, close functionality .Test the driver by writing an application by reading data from the driver  and writing data to the driver



//Includes

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h> //device time
#include<linux/types.h>  //Opaque data types
#include<linux/fs.h>     //file operations structure
#include<linux/cdev.h>   //cdev
#include<linux/uaccess.h>  //handler functions

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind Kumar");
MODULE_DESCRIPTION("character driver with open,read,write,functionality");


#define NAME my_char_device


//Function Prototypes
//
//for OPEN AND RELEASE
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);

//for READ AND WRITE
ssize_t NAME_write(struct file *filp, const char __user *UserBuffer, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *UserBuffer, size_t count, loff_t *offp);





//operations that the driver would provide

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
        .release = NAME_release,
	.write = NAME_write,
	.read = NAME_read,
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

	//Device registering
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

//functionality for writing
ssize_t NAME_write(struct file *filp, const char __user *UserBuffer, size_t count, loff_t *offp)
{
     char KernelBuffer[100];
     int res;
     ssize_t value;

     res = copy_from_user((char *)KernelBuffer, (char *)UserBuffer , count);

     if(res == 0)
     {
	     printk(KERN_ALERT"\nUser's Message : %s\n",KernelBuffer);
	     printk(KERN_ALERT "\n Number of Bytes written: %d\n",count);
	     value = count ;
	     return value;
     
     }
     else
     {
	     printk(KERN_ALERT "\n ERROR WRITING ");
	     value = EFAULT;
	     return value;




//functionality for read
ssize_t NAME_read(struct file *filp, char __user *UserBuffer, size_t count, loff_t *offp)
{
 char KernelBuffer[] = "It's me Kernel Buffer";
 int res;
 ssize_t value;

    res = copy_to_user((char *)UserBuffer,(const char *)KernelBuffer,sizeof(KernelBuffer));
    if(res ==0)
    {
	    printk(KERN_ALERT "\ndata copied to user's space\n");
	    value = count;
	    return value;
    }

    else
    {
	    printk(KERN_ALERT "\nIt's an error ,could not write data to user\n");
	    value = EFAULT;
	    return value;
    }
  
}





module_init(CharDevice_init);
module_exit(CharDevice_exit);






