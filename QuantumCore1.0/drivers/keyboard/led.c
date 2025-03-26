#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define LED_PIN 17

static int __init led_driver_init(void) {
    int ret;

    ret = gpio_request(LED_PIN, "LED");
    if (ret) {
        printk(KERN_ERR "Failed to request GPIO for LED\n");
        return ret;
    }

    ret = gpio_direction_output(LED_PIN, 0);  // Изначально выключить LED
    if (ret) {
        gpio_free(LED_PIN);
        printk(KERN_ERR "Failed to set GPIO direction\n");
        return ret;
    }

    printk(KERN_INFO "LED driver initialized\n");

    // Порог для мигания LED
    while (1) {
        gpio_set_value(LED_PIN, 1);
        msleep(500);
        gpio_set_value(LED_PIN, 0);
        msleep(500);
    }

    return 0;
}

static void __exit led_driver_exit(void) {
    gpio_set_value(LED_PIN, 0);
    gpio_free(LED_PIN);
    printk(KERN_INFO "LED driver exited\n");
}

module_init(led_driver_init);
module_exit(led_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LED Driver using GPIO");
MODULE_VERSION("1.0");
