#include <linux/kernel.h>
#include <linux/taskstats_kern.h>
#include <linux/tsacct_kern.h>
#include <linux/acct.h>
#include <linux/delayacct.h>
#include <linux/cpumask.h>
#include <linux/percpu.h>
#include <linux/slab.h>
#include <linux/cgroupstats.h>
#include <linux/cgroup.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/pid_namespace.h>
#include <net/genetlink.h>
#include <linux/atomic.h>
#include <linux/sched/cputime.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/anon_inodes.h>
#include <linux/slab.h>
#include <linux/sched/autogroup.h>
#include <linux/sched/mm.h>
#include <linux/sched/coredump.h>
#include <linux/sched/user.h>
#include <linux/sched/numa_balancing.h>
#include <linux/sched/stat.h>
#include <linux/sched/task.h>
#include <linux/sched/task_stack.h>
#include <linux/sched/cputime.h>
#include <linux/seq_file.h>
#include <linux/rtmutex.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/completion.h>
#include <linux/personality.h>
#include <linux/mempolicy.h>
#include <linux/sem.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/iocontext.h>
#include <linux/key.h>
#include <linux/binfmts.h>
#include <linux/mman.h>
#include <linux/mmu_notifier.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mm_inline.h>
#include <linux/nsproxy.h>
#include <linux/capability.h>
#include <linux/cpu.h>
#include <linux/cgroup.h>
#include <linux/security.h>
#include <linux/hugetlb.h>
#include <linux/seccomp.h>
#include <linux/swap.h>
#include <linux/jiffies.h>
#include <linux/futex.h>
#include <linux/compat.h>
#include <linux/kthread.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/rcupdate.h>
#include <linux/ptrace.h>
#include <linux/mount.h>
#include <linux/audit.h>
#include <linux/memcontrol.h>
#include <linux/ftrace.h>
#include <linux/proc_fs.h>
#include <linux/profile.h>
#include <linux/rmap.h>
#include <linux/ksm.h>
#include <linux/acct.h>
#include <linux/userfaultfd_k.h>
#include <linux/tsacct_kern.h>
#include <linux/cn_proc.h>
#include <linux/freezer.h>
#include <linux/delayacct.h>
#include <linux/taskstats_kern.h>
#include <linux/random.h>
#include <linux/tty.h>
#include <linux/fs_struct.h>
#include <linux/magic.h>
#include <linux/perf_event.h>
#include <linux/posix-timers.h>
#include <linux/user-return-notifier.h>
#include <linux/oom.h>
#include <linux/khugepaged.h>
#include <linux/sysctl.h>
#include <linux/kcov.h>
#include <linux/thread_info.h>
char buf[PATH_MAX];
static char *process = "blah";
char *path_command ;
module_param(process, charp, 0000);
MODULE_PARM_DESC(process, "A character string");
struct file *get_mm_exe_file(struct mm_struct *mm)
{
	struct file *exe_file;

	rcu_read_lock();
	exe_file = rcu_dereference(mm->exe_file);
	if (exe_file && !get_file_rcu(exe_file))
		exe_file = NULL;
	rcu_read_unlock();
	return exe_file;
}
struct file *get_task_exe_file(struct task_struct *task)
{
	struct file *exe_file = NULL;
	struct mm_struct *mm;

	task_lock(task);
	mm = task->mm;
	if (mm)
	{
		if (!(task->flags & PF_KTHREAD))
			exe_file = get_mm_exe_file(mm);
	}
	task_unlock(task);
	return exe_file;
}
int strcmp(const char *cs, const char *ct)
{
	unsigned char c1, c2;

	while (1)
	{
		c1 = *cs++;
		c2 = *ct++;
		if (!c1)
			break;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
	}
	return 0;
}
static int task_init(void)
{
	struct task_struct *task_list;
	struct file *exe_file;
	int flag = 0;
	for_each_process(task_list)
	{
		if (strcmp(process, task_list->comm) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		printk(KERN_INFO "Process not found");
	}
	else
	{
		exe_file = get_task_exe_file(task_list);
		if (exe_file == NULL)
		{
			printk(KERN_INFO "Command Path Not Found");
		}
		else
		{
			path_command= dentry_path_raw(exe_file->f_path.dentry, buf, PATH_MAX);
			if (path_command == NULL)
			{
				printk(KERN_INFO "Command Path Not Found");
			}
			else{
				printk("Process Details:%s\n Process Name: %s\n Process ID:%d\n User_ID: %d\n Process Group ID: %d\n Command Path: %s\n"," ",
				task_list->comm, task_list->pid, __kuid_val(task_list->cred->uid),pid_vnr(task_pgrp(task_list)),path_command);
			}
		}
	}
	return 0;
}
static void task_exit(void)
{
	pr_info("Exiting now\n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Deepanshu Dabas");
MODULE_DESCRIPTION("task_struct Print Module"); 
module_init(task_init);
module_exit(task_exit);
