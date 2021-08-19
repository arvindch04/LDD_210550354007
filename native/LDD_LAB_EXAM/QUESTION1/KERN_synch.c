#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind Kumar");
MODULE_DESCRIPTION("Kernel Synchronization Mechanisms for Multiple devices");

#define MAX_DEV 2
#define NAME my_char_device_stat

static int NAME_open(struct inode *inode, struct file *file);
static int NAME_release(struct inode *inode, struct file *file);
static ssize_t NAME_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t NAME_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

static const struct file_operations mychardev_fops = {
    .owner      = THIS_MODULE,
    .open       = NAME_open,
    .release    = NAME_release,
    .read       = NAME_read,
    .write       = NAME_write
};

struct mychar_device_data {
    struct cdev cdev;
};

static int dev_major = 0;
static struct mychar_device_data mychardev_data[MAX_DEV];



 char KernelBuffer[] = "It's me Kernel Buffer";


static int __init mychardev_init(void)
{
    int err, i;
    dev_t dev;

    err = alloc_chrdev_region(&dev, 0, MAX_DEV, "mychardev");

    dev_major = MAJOR(dev);

    for (i = 0; i < MAX_DEV; i++) {
        cdev_init(&mychardev_data[i].cdev, &mychardev_fops);
        mychardev_data[i].cdev.owner = THIS_MODULE;

        cdev_add(&mychardev_data[i].cdev, MKDEV(dev_major, i), 1);

    }

    return 0;
}

static void __exit mychardev_exit(void)
{
    int i;


    unregister_chrdev_region(dev,MAX_DEV);
}

static int mychardev_open(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device open\n");
    return 0;
}

static int mychardev_release(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device close\n");
    return 0;
}


static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    printk("In the read module");
    return count;
}

static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	printk("In the write module");
    return count;
}



module_init(mychardev_init);
module_exit(mychardev_exit);
