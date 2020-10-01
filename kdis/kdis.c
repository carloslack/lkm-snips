/*
 *  kdis.c
 *  Carlos Carvalho
 *  Linux ubuntu 5.4.0-42-generic
 *
 *  POC showing a simple use case for
 *  BeaEngine <https://github.com/BeaEngine/beaengine>
 *  but patched to run on Linux kernel
 *      <https://github.com/carloslack/beaengine/tree/hack-da-shit-out-of-it>
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kallsyms.h>
#include <linux/kernel_stat.h>

#include "BeaEngine.h"
#include "BeaEngine.c"

/*
 * 64b jmp instruction size. Ex:
 *      mov %rax, 0xffff95f900000000
 *      mov %rax, %rax
 *      jmpq *%rax
 */
#define JMPLEN 15

static int disas(void *nr)
{
    int total = 0;
    int instr_size = 0;
    int i;
    DISASM MyDisasm;

    if (!nr)
        goto error;

    memset(&MyDisasm, 0, sizeof(DISASM));
    MyDisasm.EIP = (UIntPtr)nr;
    /*
     * Run through opcodes up to JMPLEN
     * displaying each instruction blocks
     */
    for(i = 0; i < 12 && total < JMPLEN ; i++) {
        int j;
        instr_size = Disasm(&MyDisasm);
        if (instr_size <= 0)
            goto error;
        pr_info("instr_size: %d\n", instr_size);
        for(j = 0; j < instr_size; j++)
            pr_info("%02x ", *(((unsigned char *)MyDisasm.EIP)+j));
        total += instr_size;
        MyDisasm.EIP += instr_size;

        pr_info("\n");
    }
    pr_info("total=%d\n", total);
    return total;
error:
    pr_info("kdis error\n");
    return 0;
}

static int __init lkm_init(void) {
    /*
     * Use vfs_rmmdir as example.
     * Could be any /proc/kallsyms
     */
    int (*fp)(struct inode*, struct dentry*) =
        (int (*)(struct inode*, struct dentry*))kallsyms_lookup_name("vfs_rmdir");
    disas(fp);

    return 0;
}

static void __exit lkm_cleanup(void) {
    pr_info("kdis unloaded\n");
}

module_init(lkm_init);
module_exit(lkm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlos Carvalho");

