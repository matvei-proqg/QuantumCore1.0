#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>

#define DEVICE_NAME "simple_block_device"
#define BLOCK_SIZE 512

static int major_number;
static struct block_device_operations simple_block_ops = {
    .owner = THIS_MODULE,
};

static int __init block_device_init(void) {
    major_number = register_blkdev(0, DEVICE_NAME);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register block device\n");
        return major_number;
    }

    printk(KERN_INFO "Block device registered with major number %d\n", major_number);
    return 0;
}

static void __exit block_device_exit(void) {
    unregister_blkdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Block device unregistered\n");
}

module_init(block_device_init);
module_exit(block_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Block Device Driver");
MODULE_VERSION("1.0");
