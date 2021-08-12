#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");




static int  a  = 20;
static int  b  = 10;
static char* str = "";

// each operator has been given a character pointer and later string comparison has been done for reuired operator parameter passing 
// now you can insert module as $sudo insmod param_operations.ko str="mul" for multiplication operation
//
//
static char* addp = "add";
static char* subp = "sub";
static char* mulp = "mul";
static char* divp = "div";


module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);
module_param(str, charp, S_IRUGO);

static int add(int a, int b)
{
        return a+b;	
}


static int sub(int a, int b)
{ 
	return a-b;
}

static int div(int a, int b)
{
 
	return a/b;
}

static int mul(int a, int b)
{
 
 
	return a*b;
}

static int __init param_init(void)
{
           
	printk(KERN_ALERT "In init function");

	if(strcmp(str,addp)==0)
	{
		printk("In %s function", str); 
		printk(KERN_ALERT "\n displaying the addition result on screen: %d\n", add(a,b)); 
        }
	else if(strcmp(str,subp)==0)
	{
	
		printk("In %s function", str); 
      		printk(KERN_ALERT "\n displaying the substraction result on screen: %d\n",sub(a,b)); 
 
	}
	else if(strcmp(str,mulp)==0)
	{
		printk("In %s function", str); 
		printk(KERN_ALERT "\n displaying the multiplication result on screen: %d\n", mul(a,b)); 

	}
	else if(strcmp(str,divp)==0)
	{
		printk("In %s function", str); 
		printk(KERN_ALERT "\n displaying the division result on screen: %d\n",div(a,b)); 
	
	}
	else 
	{
		printk(KERN_ALERT "\n Invalid Operator");
	}



		return 0;
}



static void __exit param_exit(void)
{

	printk(KERN_ALERT "Goodbye,int parameter printed\n");
}


module_init(param_init);
module_exit(param_exit);

	






