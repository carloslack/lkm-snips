/*
 *  stat.c
 *  Carlos Carvalho
 *  Linux ubuntu 5.4.0-42-generic
 *
 *  Print stat file attributes from given PID
 *
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/pid.h>
#include <linux/fs_struct.h>
#include <linux/version.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/mount.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlos Carvalho");

/*
 * insmod ./task.ko my_pid=<#pid>
 */
static int my_pid;
module_param(my_pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

#define _ST(mask, type) { \
    if (mask & STATX_ ## type) \
        pr_info("STATX_%s: true\n", #type); \
}

/**
 * Print basic kstat fields
 * For mask fields, one can inspect further
 * by checking the attributes. E.g.: var & mask
 */
static void print_kstat(struct kstat *stat)
{
    pr_info("<stat>\n");
    if (stat) {
        pr_info("\tmajor: %d\n", MAJOR(stat->dev));
        pr_info("\tminor: %d\n", MINOR(stat->dev));
        pr_info("\trmask: 0x%x\n", stat->result_mask);
        pr_info("\tmode: 0x%x\n", stat->mode);
        pr_info("\tattributes: 0x%llx\n", stat->attributes);
        pr_info("\tattributes_mask: 0x%llx\n", stat->attributes_mask);
        pr_info("\tino : %lld\n", stat->ino);
        pr_info("\tdev : %d\n", stat->dev);
        pr_info("\trdev : %d\n", stat->rdev);
        pr_info("\tuid: %d\n", stat->uid.val);
        pr_info("\tgid: %d\n", stat->gid.val);
        pr_info("\tsize: %lld\n", stat->size);
        pr_info("\tatime.tv_sec: %lld\n", stat->atime.tv_sec);
        pr_info("\tatime.tv_usec: %ld\n", stat->atime.tv_nsec);
        pr_info("\tmtime.tv_sec: %lld\n", stat->mtime.tv_sec);
        pr_info("\tmtime.tv_usec: %ld\n", stat->mtime.tv_nsec);
        pr_info("\tctime.tv_sec: %lld\n", stat->ctime.tv_sec);
        pr_info("\tctime.tv_usec: %ld\n", stat->ctime.tv_nsec);
        pr_info("\tbtime.tv_sec: %lld\n", stat->btime.tv_sec);
        pr_info("\tbtime.tv_usec: %ld\n", stat->btime.tv_nsec);
        pr_info("\tblocks: %lld\n", stat->blocks);
    }
    pr_info("</stat>\n");
}

/**
 * Most of read_fs was taken from
 * https://github.com/carloslack/ntsh
 */
static void read_fs(struct task_struct *tsk)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
    u32 req_mask = STATX_INO;
    unsigned int query_mask = AT_STATX_SYNC_AS_STAT;
#endif
    struct inode *i;
    struct kstat stat;
    struct file *f;
    const struct inode_operations *op;

    pr_info("task loading...\n");

    if (!tsk || !my_pid)
        goto fail;

    /**
     * Not error, it is kernel task
     * and there is no file associated with it.
     */
    if(!tsk->mm)
        goto fail;

    /*
     * It's regular task and there is
     * executable file.
     */
    f = tsk->mm->exe_file;
    if(!f)
        goto fail;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
    i = f->f_dentry->d_inode;
#else
    i = f->f_inode;
#endif
    if(!i)
        goto fail;

    op = i->i_op;
    if(!op || !op->getattr)
        goto fail;

    memset(&stat, 0, sizeof(struct kstat));

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
    op->getattr(&f->f_path, &stat, req_mask, query_mask);
#elif LINUX_VERSION_CODE < KERNEL_VERSION(4,11,0)
    op->getattr(task_active_pid_ns(current)->proc_mnt, f->f_path.dentry, &stat);
#elif LINUX_VERSION_CODE < KERNEL_VERSION(3,19,0)
    op->getattr(task_active_pid_ns(current)->proc_mnt, f->f_dentry, &stat);
#endif

    /**
     * Once you know the inode it number it is easy to get the
     * executable full path by relying to find command:
     *
     * # find /path/to/mountpoint -inum <inode number> 2>/dev/null
     */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,19,0)
    pr_info("filename: %s\n", (const char *)f->f_dentry->d_name.name);
#else
    pr_info("filename: %s\n", (const char *)f->f_path.dentry->d_name.name);
#endif
    print_kstat(&stat);

    return;

fail:
    /**
     * Among other reasons we can fail if attempting
     * to read from kernel threads
     */
    pr_info("Failed to read task\n");
}

static int __init lkm_init(void) {
    pr_info("Checking PID: %d\n", my_pid);
    read_fs(get_pid_task(find_get_pid(my_pid), PIDTYPE_PID));

    return 0;
}

static void __exit lkm_cleanup(void) {
    pr_info("task unloaded\n");
}

module_init(lkm_init);
module_exit(lkm_cleanup);

