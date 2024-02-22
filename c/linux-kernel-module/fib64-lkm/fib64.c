#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Thompson");
MODULE_DESCRIPTION("Implements a character device that continuously "
		   "generates 64-bit unsigned Fibonacci numbers");

/** Name of kernel module/device, associated class */
#define DEV_NAME "fib64"
#define DEV_CLASS DEV_NAME "class"

/** DEV_MAJ - extract major device number from dev_t */
#define DEV_MAJ(n) ((n) >> 20)

/** DEV_MIN - extract minor device number from dev_t */
#define DEV_MIN(n) ((n) & (~0u >> 12))

/** Fibonacci calculation variables */
static u64 current_val = 0;
static u64 last_val = 1;
static int open_count = 0;

/** Device number */
static dev_t dev_num;
/** Pointer to created device class */
static struct class *class_ptr;
/** Structure representing the character device */
static struct cdev cdev_instance;

/* Module functions */
static int __init fib64_init(void);
static void __exit fib64_exit(void);

/* System-call implementations */
static int dev_open(struct inode *dev_file, struct file *instance);
static int dev_close(struct inode *dev_file, struct file *instance);
static ssize_t dev_read(struct file *file, char *ubuf, size_t count, loff_t *offs);

/* Mapping of syscalls to implementations */
static struct file_operations fib64_fops = {
	.owner = THIS_MODULE,
	.open = dev_open,
	.release = dev_close,
	.read = dev_read
};

/**
 * fib64_init - Tells the kernel what to do when our module is loaded
 * 
 * Return: 0 on success, negative for error
 */
static int __init fib64_init(void)
{
	/**
	 * Log info: Module initializing
	 */
	pr_info("Initializing '%s' module...\n", DEV_NAME);

	/**
	 * Call `alloc_chrdev_region` to register character-device region
	 * If negative returned, log error and goto failure
	 */
	if (alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME) < 0) {
		pr_err("Failed to assign '%s' device region\n", DEV_NAME);
		goto failure;
	}

	/**
	 * Log info: Device number
	 */
	pr_info("'%s' device number: MAJOR=%d MINOR=%d\n",
		DEV_NAME, DEV_MAJ(dev_num), DEV_MIN(dev_num));

	/**
	 * Call `class_create` to define a custom device type
	 * Store in `class_ptr` (static global)
	 * If NULL returned, unregister device region and exit
	 */
	class_ptr = class_create(DEV_CLASS);

	if (!class_ptr) {
		pr_err("Failed to create device class '%s'\n", DEV_CLASS);
		goto unregister_region;
	}

	/**
	 * Call `device_create` 
	 * If NULL returned, destroy device class and all previous cleanup
	 */
	if (!device_create(class_ptr, NULL, dev_num, NULL, DEV_NAME)) {
		pr_err("Failed to create device '%s'\n", DEV_NAME);
		goto destroy_class;
	}

	/**
	 * Call `cdev_init` to register file operations (void, does not fail)
	 */
	cdev_init(&cdev_instance, &fib64_fops);

	/**
	 * Call `cdev_add` to add the device to the system
	 * If negative returned, destroy device and all previous cleanup
	 */
	if (cdev_add(&cdev_instance, dev_num, 1) < 0) {
		pr_err("Failed to add device '%s'\n", DEV_NAME);
		goto destroy_device;
	}

	/**
	 * Log info: Device file /dev/fib64 registered with system
	 * Return 0 for success
	 */
	pr_info("Registered device '%s' with system\n", DEV_NAME);
	return 0;

	/**
	 * Failure cleanup operations (with fallthrough)
	 * Return -1 for failure
	 */
destroy_device:
	device_destroy(class_ptr, dev_num);

destroy_class:
	class_destroy(class_ptr);

unregister_region:
	unregister_chrdev_region(dev_num, 1);
failure:
	return -1;
}

/**
 * fib64_exit - Tells the kernel what to do when unloading the module
 */
static void __exit fib64_exit(void)
{
	/**
	 * Log info: This LKM is being unloaded
	 */
	pr_info("Kernel module '%s' is being unloaded...\n", DEV_NAME);

	/**
	 * Call `cdev_del` to remove the device from the system
	 */
	cdev_del(&cdev_instance);

	/**
	 * Call `device_destroy` to free device resources
	 */
	device_destroy(class_ptr, dev_num);

	/**
	 * Call `class_destroy` to free device-class resources
	 */
	class_destroy(class_ptr);

	/**
	 * Call `unregister_chrdev_region` to free device-class resources
	 */
	unregister_chrdev_region(dev_num, 1);
}

/**
 * dev_open - Tells the kernel what to do when `open()` called on /dev/fib64
 * @dev_file: Pointer to inode structure
 * @instance: Pointer to file structure associated with a user process's fd
 * 
 * Return: 0 for success, negative on failure
 */
static int dev_open(struct inode *dev_file, struct file *instance)
{
	if (open_count > 0) {
		pr_warn("Concurrent access to '%s' attempted...\n", DEV_NAME);
		return -EBUSY;
	}

	++open_count;
	pr_info("Device '%s' opened successfully\n", DEV_NAME);
	current_val = 0;
	last_val = 1;
	return 0;
}

/**
 * dev_close - Tells the kernel what to do when `close()` called on /dev/fib64
 * @dev_file: Pointer to inode structure
 * @instance: Pointer to file structure associated with a user process's fd
 * 
 * Return: 0 for success, negative on failure
 */
static int dev_close(struct inode *dev_file, struct file *instance)
{
	--open_count;
	pr_info("Device '%s' closed\n", DEV_NAME);
	return 0;
}

/**
 * dev_read - Tells the kernel what to do when `read()` called for /dev/fib64
 * @file: Pointer to file structure associated with a user process's fd
 * @ubuf: Pointer to the userland buffer to write into
 * @offs: Pointer to loff_t stucture that manages open file offsets
 * 
 * Return: Number of bytes written to userland buffer, -1 on error
 */
static ssize_t dev_read(struct file *file, char *ubuf, size_t count, loff_t *offs)
{
	size_t val_count, i;
	u64 tmp, *ubuf_pos = NULL;

	if (!ubuf)
		return -EFAULT;

	val_count = count >> 3;
	ubuf_pos = (u64 *)ubuf;

	for (i = 0; i < val_count; ++i, ++ubuf_pos) {
		put_user(current_val, ubuf_pos);

		if (check_add_overflow(current_val, last_val, &tmp)) {
			current_val = 0;
			last_val = 1;
		}
		else {
			last_val = current_val;
			current_val = tmp;
		}
	}

	return (ssize_t)(val_count << 3);
}

/* Register module init and exit functions */
module_init(fib64_init);
module_exit(fib64_exit);
