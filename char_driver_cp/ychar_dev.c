#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>

#define BUFFER_MAX 64
#define OK 0
#define ERROR -1

struct cdev *gDev;
struct file_operations *gFile;
dev_t dev_num;
unsigned int sub_dev_num = 1;
int reg_major = 233;
int reg_minor = 0;

char buffer[BUFFER_MAX];

int y_char_open(struct inode *p, struct file *f){
    printk(KERN_INFO, "[LOG] Message from y_char_open.");
    return 0;
}

ssize_t y_char_write(struct file *f, const char __user*u, size_t s, loff_t *l){
    printk(KERN_INFO, "[LOG] Message from y_char_write.");
    int write_len = 0;
    write_len = BUFFER_MAX>s?s:BUFFER_MAX;
    if (copy_from_user(buffer, u, write_len)){
        return -EFAULT;
    }
    return write_len;
}

ssize_t y_char_read(struct file *f, char __user*u, size_t s, loff_t *l){
    printk(KERN_INFO, "[LOG] Message from y_char_read.");
    int read_len = 0;
    read_len = BUFFER_MAX>s?s:BUFFER_MAX;
    if (copy_to_user(u, buffer, read_len)){
        return -EFAULT;
    }
    return read_len;
}

int y_char_init(void){
	dev_num = MKDEV(reg_major, reg_minor);
	if(OK == register_chrdev_region(dev_num, sub_dev_num, "y_char")){
	    printk(KERN_INFO "register_chrdev_region ok \n");
	}else {
	    printk(KERN_INFO "register_chrdev_region error n");
	    return ERROR;
	}
	printk(KERN_INFO " y_char driver init \n");
	gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
	gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);
	gFile->open = y_char_open;
	gFile->read = y_char_read;
	gFile->write = y_char_write;
	gFile->owner = THIS_MODULE;
	cdev_init(gDev, gFile);
	cdev_add(gDev, dev_num, 1);
	return 0;
}

void __exit y_char_exit(void){
	printk(KERN_INFO " y_char driver exit \n");
	cdev_del(gDev);
	kfree(gFile);
	kfree(gDev);
	unregister_chrdev_region(dev_num, sub_dev_num);
	return;
}
module_init(y_char_init);
module_exit(y_char_exit);
MODULE_LICENSE("GPL");





