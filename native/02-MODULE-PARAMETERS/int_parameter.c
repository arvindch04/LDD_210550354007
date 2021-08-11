#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");



static int parameter = 20;

module_param(parameter, int, S_IRUGO);

static int __init param_init(void)
{
	printk(KERN_ALERT "In init function");
	printk(KERN_ALERT "\n displaying the int parameter on screen: %d\n", parameter); 
	
	return 0;
}




static void __exit param_exit(void)
{

	printk(KERN_ALERT "Goodbye,int parameter printed\n");
}


module_init(param_init);
module_exit(param_exit);

	






