#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/seq_device.h>

static int __init sound_device_init(void) {
    printk(KERN_INFO "Sound device driver loaded\n");
    return 0;
}

static void __exit sound_device_exit(void) {
    printk(KERN_INFO "Sound device driver unloaded\n");
}

module_init(sound_device_init);
module_exit(sound_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Basic Sound Device Driver");
MODULE_VERSION("1.0");
