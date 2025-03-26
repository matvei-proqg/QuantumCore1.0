#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/err.h>

#define DEVICE_NAME "i2c_device"

static struct i2c_client *my_i2c_client;

static int i2c_device_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    printk(KERN_INFO "I2C device detected: %s\n", client->dev.of_node->name);
    my_i2c_client = client;
    return 0;
}

static int i2c_device_remove(struct i2c_client *client) {
    printk(KERN_INFO "I2C device removed\n");
    return 0;
}

static const struct i2c_device_id i2c_device_id[] = {
    { DEVICE_NAME, 0 },
    {}
};

static struct i2c_driver my_i2c_driver = {
    .driver = {
        .name = DEVICE_NAME,
        .owner = THIS_MODULE,
    },
    .probe = i2c_device_probe,
    .remove = i2c_device_remove,
    .id_table = i2c_device_id,
};

static int __init i2c_device_init(void) {
    int ret = i2c_add_driver(&my_i2c_driver);
    if (ret) {
        printk(KERN_ALERT "Failed to register I2C driver\n");
        return ret;
    }
    printk(KERN_INFO "I2C driver registered\n");
    return 0;
}

static void __exit i2c_device_exit(void) {
    i2c_del_driver(&my_i2c_driver);
    printk(KERN_INFO "I2C driver removed\n");
}

module_init(i2c_device_init);
module_exit(i2c_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple I2C device driver");
MODULE_VERSION("1.0");
