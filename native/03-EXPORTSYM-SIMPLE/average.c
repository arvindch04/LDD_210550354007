#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "Header.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");


static int HelloWorld_add(int a, int b);



int a_test=10, b_test=20;


static int __init hello_init(void)
{
	int Average;

	printk(KERN_ALERT "HelloWorld...In average module\n");

	printk(KERN_ALERT "In init module ...The module parameter is %d\n",a_test);
	printk(KERN_ALERT "In init module ...The module parameter is %d\n",b_test);
	Average=HelloWorld_add(a_test,b_test)/2;
	printk(KERN_ALERT "\n\n The Average is %d\n",  Average);
	return 0;
}

static void __exit hello_exit(void)
{

	printk(KERN_ALERT "GoodbyeWorld of average module\n");
}


module_init(hello_init);
module_exit(hello_exit);




