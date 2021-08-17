#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ch.Aravind kumar");
MODULE_DESCRIPTION("Kernel_timers");


//Timer Variable
#define TIMEOUT 5000    //milliseconds

static struct timer_list my_timer;
static unsigned int count = 0;


//Timer callback function which  is called when timer expires
static void my_timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO"in Timer callback function[%d]\n", count++);

    //re enable timer for periodic timer

     mod_timer(&my_timer,jiffies + msecs_to_jiffies(TIMEOUT));
}
  


static int __init my_init(void)
{


//	pr_info("%s: Timer module loaded\n", __func__);

	//TIMER SETUP:
	timer_setup(&my_timer,my_timer_callback,0);


	//Timer interval based on TIMEOUT
     mod_timer(&my_timer,jiffies + msecs_to_jiffies(TIMEOUT));

  

	return 0;

}

static void __exit my_exit(void)
{
    /* remove kernel timer when unloading module */
    del_timer(&my_timer);
   
}

module_init(my_init);
module_exit(my_exit);
