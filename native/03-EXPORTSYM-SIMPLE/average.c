#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "Header.h"

MODULE_LICENSE("GPL");


static int HelloWorld_add(int a, int b);



int a_test=10, b_test=20;


static int __init hello_init(void)
{
	int Average;
	printk(KERN_ALERT "In init module ...The module parameter is %d\n",a_test);

	printk(KERN_ALERT "Hello,World\n");
	Average=HelloWorld_add(a_test,b_test)/2;
	printk(KERN_ALERT "\n The Average is %d\n",  Average);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "In cleanup Module...The module Parameter is %d\n", a_test);
	printk(KERN_ALERT "Goodbye,World\n");
}


module_init(hello_init);
module_exit(hello_exit);




