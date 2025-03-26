#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#define MOUSE_DEVICE_NAME "simple_mouse_device"

static struct input_dev *mouse_input_dev;

static irqreturn_t mouse_irq_handler(int irq, void *dev_id) {
    unsigned char data;
    // Тут нужно получать данные от устройства, но для примера будем использовать фиктивные данные
    data = 0x01; // фиктивное значение для кнопки мыши

    // Отправляем событие для кнопки мыши
    input_report_key(mouse_input_dev, BTN_LEFT, data & 0x01);
    input_sync(mouse_input_dev);

    return IRQ_HANDLED;
}

static int __init mouse_device_init(void) {
    int ret;

    // Регистрация устройства ввода
    mouse_input_dev = input_allocate_device();
    if (!mouse_input_dev) {
        printk(KERN_ERR "Failed to allocate input device\n");
        return -ENOMEM;
    }

    mouse_input_dev->name = MOUSE_DEVICE_NAME;
    mouse_input_dev->phys = "mouse/input0";
    mouse_input_dev->id.bustype = BUS_HOST;

    set_bit(EV_KEY, mouse_input_dev->evbit);
    set_bit(BTN_LEFT, mouse_input_dev->keybit);

    ret = input_register_device(mouse_input_dev);
    if (ret) {
        printk(KERN_ERR "Failed to register input device\n");
        input_free_device(mouse_input_dev);
        return ret;
    }

    // Подключаем обработчик прерываний (для примера будем использовать фиктивный IRQ)
    ret = request_irq(IRQ_MOUSE, mouse_irq_handler, IRQF_SHARED, "mouse_irq", NULL);
    if (ret) {
        printk(KERN_ERR "Failed to request IRQ for mouse\n");
        input_unregister_device(mouse_input_dev);
        return ret;
    }

    printk(KERN_INFO "Mouse device initialized\n");
    return 0;
}

static void __exit mouse_device_exit(void) {
    free_irq(IRQ_MOUSE, NULL);
    input_unregister_device(mouse_input_dev);
    printk(KERN_INFO "Mouse device exited\n");
}

module_init(mouse_device_init);
module_exit(mouse_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Mouse Device Driver");
MODULE_VERSION("1.0");
