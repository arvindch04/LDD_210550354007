#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");



static int HelloWorld_add(int a, int b);

static int __init hello_init(void)
{
	printk(KERN_ALERT "In init module");
	printk(KERN_ALERT "Hello World...In ADD module\n");
	return 0;
}


static int HelloWorld_add(int a,int b)
{
	printk(KERN_ALERT "\nIn function Helloworld_add of module ...ADD\n");
	return(a+b);
}

EXPORT_SYMBOL_GPL(HelloWorld_add);

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "In cleanupof ADD module");
	printk(KERN_ALERT "Goodbye,World\n");
}


module_init(hello_init);
module_exit(hello_exit);

	






