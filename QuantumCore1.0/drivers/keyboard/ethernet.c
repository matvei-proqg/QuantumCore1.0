#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

static struct net_device *my_net_dev;

static int my_open(struct net_device *dev) {
    printk(KERN_INFO "Ethernet device opened\n");
    return 0;
}

static int my_stop(struct net_device *dev) {
    printk(KERN_INFO "Ethernet device stopped\n");
    return 0;
}

static netdev_tx_t my_start_xmit(struct sk_buff *skb, struct net_device *dev) {
    printk(KERN_INFO "Data transmitted\n");
    dev_kfree_skb(skb);
    return NETDEV_TX_OK;
}

static const struct net_device_ops my_netdev_ops = {
    .ndo_open = my_open,
    .ndo_stop = my_stop,
    .ndo_start_xmit = my_start_xmit,
};

static int __init net_device_init(void) {
    my_net_dev = alloc_etherdev(0);
    if (!my_net_dev) {
        printk(KERN_ALERT "Failed to allocate network device\n");
        return -ENOMEM;
    }

    my_net_dev->netdev_ops = &my_netdev_ops;
    if (register_netdev(my_net_dev)) {
        printk(KERN_ALERT "Failed to register network device\n");
        free_netdev(my_net_dev);
        return -ENODEV;
    }

    printk(KERN_INFO "Network device registered\n");
    return 0;
}

static void __exit net_device_exit(void) {
    unregister_netdev(my_net_dev);
    free_netdev(my_net_dev);
    printk(KERN_INFO "Network device unregistered\n");
}

module_init(net_device_init);
module_exit(net_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Basic Ethernet Device Driver");
MODULE_VERSION("1.0");
