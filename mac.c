#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/nsproxy.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
    int s = 10;
    struct net_device *dev = dev_get_by_name(current->nsproxy->net_ns,"eth0");
    printk(KERN_ALERT "Hello, world\n");
    //printk(KERN_ALERT "%s\n",dev->dev_addr[0]);
    //printk("HWaddr %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
    //dev->dev_addr[0], dev->dev_addr[1],
    //dev->dev_addr[2], dev->dev_addr[3],
    //dev->dev_addr[4], dev->dev_addr[5]);
    printk(KERN_INFO"%d,%d\n",(int)dev->dev_addr[0],(int)dev->dev_addr[1]);
    printk(KERN_INFO"%s\n",dev->dev_addr);
    printk(KERN_INFO"%cabcd\n",(char)s);
    return 0;
}
static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);
