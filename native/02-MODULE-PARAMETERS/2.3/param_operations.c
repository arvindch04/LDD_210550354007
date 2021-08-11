#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");



static int parameter1 = 20;
static int parameter2 = 10;
static char* string = "module";


module_param(parameter1, int, S_IRUGO);
module_param(parameter2, int, S_IRUGO);
module_param(string, charp, S_IRUGO);

static int add(int a, int b)
{
	
//	printk(KERN_ALERT "\n displaying the addition result on screen: %d\n", a+b); 
return a+b;	
}


static int sub(int a, int b)
{
//	printk(KERN_ALERT "\n displaying the substraction result on screen: %d\n",a-b); 
	return a-b;
}

static int div(int a, int b)
{
//	printk(KERN_ALERT "\n displaying the division  result on screen: %d\n",a/b); 
	return a/b;
}

static int mul(int a, int b)
{
 
//	printk(KERN_ALERT "\n displaying the multiplication  result on screen: %d\n",a*b); 
	return a*b;
}

static int __init param_init(void)
{
        int result;    
	printk(KERN_ALERT "In init function");

	switch(string)
	{ 
		case 'add':
		       result =	add(parameter1,parameter2);

			break;

		case 'sub':
		       result =	sub(parameter1,parameter2);
			break;

		case 'mul':
		      result = mul(parameter1,parameter2);
			break;

		case 'div':
		    result = div(parameter1,parameter2);
			break;

		default:
			printk(KERN_ALERT "\nInvalid operator");

	}
	
     printk(KERN_ALERT "\n Displaying the result of requested operations between 10 & 20 :%d\n", result); 



	return 0;
}




static void __exit param_exit(void)
{

	printk(KERN_ALERT "Goodbye,int parameter printed\n");
}


module_init(param_init);
module_exit(param_exit);

	






