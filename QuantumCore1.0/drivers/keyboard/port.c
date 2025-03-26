#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/io.h>

#define PARALLEL_PORT_BASE 0x378  // Адрес базового порта LPT1

static int __init parallel_port_init(void) {
    unsigned long port_base = PARALLEL_PORT_BASE;

    if (!request_region(port_base, 3, "Parallel Port")) {
        printk(KERN_ALERT "Failed to acquire I/O region\n");
        return -EBUSY;
    }

    outb(0xFF, port_base);  // Отправляем значение на порт
    printk(KERN_INFO "Parallel port driver initialized\n");

    return 0;
}

static void __exit parallel_port_exit(void) {
    unsigned long port_base = PARALLEL_PORT_BASE;
    release_region(port_base, 3);  // Освобождаем порт
    printk(KERN_INFO "Parallel port driver exited\n");
}

module_init(parallel_port_init);
module_exit(parallel_port_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Parallel Port Driver");
MODULE_VERSION("1.0");
