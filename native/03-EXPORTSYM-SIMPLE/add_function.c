#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");


int HelloWorld_type=1;

static int HelloWorld_add(int a, int b);

static int __init hello_init(void)
{
	printk(KERN_ALERT "In init module .... The module parameter is %d\n", HelloWorld_type);
	
	printk(KERN_ALERT "Hello World\n");
	return 0;
}


static int HelloWorld_add(int a,int b)
{
	printk(KERN_ALERT "\nIn function Hello world_add of module ...ADD\n");
	return(a+b);
}

EXPORT_SYMBOL_GPL(HelloWorld_add);

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "In cleanup module .... The module parameter is %d\n", HelloWorld_type);
	printk(KERN_ALERT "Goodbye,World\n");
}


module_init(hello_init);
module_exit(hello_exit);

	






