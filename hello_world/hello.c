#include<linux/module.h>
int __init init_hello(void){
    printk("hello world .\n");
    return 0;
}

void __exit clean_up_hello(void){
    printk("hello world ee .\n");

}

module_init(init_hello);
module_exit(clean_up_hello);
MODULE_LICENSE("GPL");