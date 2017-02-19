#include <linux/list.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct birthday *person;
	int i = 0;

	for(i = 0; i < 5; i++){
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 1 + i;
		person->month = 2 + i;
		person->year = 1995 + i;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list,&birthday_list);
	}
       printk(KERN_INFO "Loading Module\n");

	printk(KERN_INFO "The list beith made");

	list_for_each_entry(person,&birthday_list,list){
		printk(KERN_INFO "Day %d Month: %d Year: %d\n", person->day, person->month, person->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	struct birthday *person, *next;
	list_for_each_entry_safe(person,next,&birthday_list,list){
		printk(KERN_INFO "Freeing thy node");
		list_del(&person->list);
		kfree(person);
	}
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Kevin Dalle");

