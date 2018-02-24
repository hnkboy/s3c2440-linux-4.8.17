#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regmap.h>
#include <linux/fs.h>

#include <linux/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio-samsung.h> 

 
#define SMDK2440_LEDS_MAJOR     111    /* 主设备号 */


static int smdk2440_drv_open(struct inode *inode, struct file *file)
{
    printk("smdk2440_drv_open");
    return 0;
}

static int smdk2440_drv_close(struct inode *inode, struct file *file)
{
    printk("smdk2440_drv_close");
    return 0;    
}

static ssize_t smdk2440__drv_read(struct file *file, char __user * buf, size_t count, loff_t * ppos)
{
    printk("smdk2440__drv_read");
    return 0;
}

static ssize_t smdk2440_drv_write(struct file *file, const char __user * buf, size_t count, loff_t * ppos)
{
	gpio_direction_output(S3C2410_GPB(6), 0);  //设置GPIO为输出
	gpio_direction_output(S3C2410_GPB(5), 0);  //设置GPIO为输出  
	
	gpio_set_value(S3C2410_GPB(6), 0);     //GPIO为0
	gpio_set_value(S3C2410_GPB(5), 1);     //GPIO为1
    	printk("smdk2440_drv_write");
    	return 0;
}

static struct file_operations smdk2440_leds_ops = {
    .owner = THIS_MODULE,
    .read = smdk2440__drv_read,
    .open = smdk2440_drv_open,
    .write = smdk2440_drv_write,
    .release = smdk2440_drv_close,
};

static int __init smdk2440_drv_leds_init(void)
{
    register_chrdev(SMDK2440_LEDS_MAJOR,"smdk2440_drv_leds",&smdk2440_leds_ops);//注册驱动程序，即告诉内核
    return 0;
}

static void __exit smdk2440_drv_leds_exit(void)
{
    unregister_chrdev(SMDK2440_LEDS_MAJOR,"smdk2440_drv_leds");
}

//指向入口函数 smdk2440_drv_leds_init
module_init(smdk2440_drv_leds_init);
//出口函数 卸载驱动
module_exit(smdk2440_drv_leds_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("smdk2440 leds driver");
