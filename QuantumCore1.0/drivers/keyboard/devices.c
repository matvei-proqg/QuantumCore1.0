#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydevice"
static int major_number;
static struct cdev my_cdev;
static char message[256] = {0};
static int message_size = 0;

static ssize_t device_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    if (*offset >= message_size) {
        return 0;
    }

    if (len > message_size - *offset) {
        len = message_size - *offset;
    }

    if (copy_to_user(buf, message + *offset, len)) {
        return -EFAULT;
    }

    *offset += len;
    return len;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    if (len > sizeof(message) - 1) {
        return -ENOMEM;
    }

    if (copy_from_user(message, buf, len)) {
        return -EFAULT;
    }

    message[len] = '\0';
    message_size = len;
    return len;
}

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mydevice opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mydevice closed\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

static int __init my_device_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    cdev_init(&my_cdev, &fops);
    if (cdev_add(&my_cdev, MKDEV(major_number, 0), 1) < 0) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to add cdev\n");
        return -1;
    }

    printk(KERN_INFO "My device initialized with major number %d\n", major_number);
    return 0;
}

static void __exit my_device_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "My device cleaned up\n");
}

module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");
