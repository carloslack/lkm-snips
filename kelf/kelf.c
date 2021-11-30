/*
 *  kelf.c
 *  Carlos Carvalho
 *  Linux ubuntu 5.4.0-42-generic
 *
 *  Access ELF headers from loaded/running executables
 *
 *  Example in 64 bits
 *
 */
#include <linux/module.h>
#include <linux/pagemap.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlos Carvalho");

static int my_pid;
module_param(my_pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

static void read_fs(pid_t pid)
{
    struct vm_area_struct *vma;
    struct page *page;
    const char *binary;
    void *page_addr;
    Elf64_Ehdr* ehdr;
    struct task_struct *tsk = get_pid_task(find_get_pid(my_pid), PIDTYPE_PID);

    if(!tsk || !tsk->mm)
        goto warn_tsk;

    vma = tsk->mm->mmap;
    if (!vma)
        goto error_vma;

    if (!vma->vm_file)
        goto error_file;

    binary = vma->vm_file->f_path.dentry->d_name.name;

    pr_info("[!] Retrieving Elf64 from '%s'\n", binary);

    page = find_get_page(vma->vm_file->f_mapping, 0);
    if (!page)
        goto error_page;

    page_addr = kmap_atomic(page);
    ehdr = (Elf64_Ehdr*)page_addr;

    // Parse ELF header
    pr_info("page_addr=%p\n", ehdr);
    pr_info("0x%02x\n", ehdr->e_ident[0]);
    pr_info("%c\n", ehdr->e_ident[1]);
    pr_info("%c\n", ehdr->e_ident[2]);
    pr_info("%c\n", ehdr->e_ident[3]);
    pr_info("type=0x%02x\n", ehdr->e_type);

    // ELFCLASS32 == 1
    // ELFCLASS64 == 2
    pr_info("EICLASS=%d\n", ehdr->e_ident[EI_CLASS]);

    kunmap_atomic(page_addr);
    return;

error_page:
    pr_info("Error: page error\n");
    return;

error_file:
    pr_info("Error: not a file\n");
    return;

error_vma:
    pr_info("Error: invalid vma\n");
    return;

    /*
     * It is either a kernel thread or
     * non existent PID
     */
warn_tsk:
    pr_info("No task found for PID %d\n", pid);
}

static int __init lkm_init(void) {
    pr_info("kelf loading...\n");
    pr_info("Checking PID: %d\n", my_pid);
    read_fs((pid_t)my_pid);

    return 0;
}

static void __exit lkm_cleanup(void) {
    pr_info("kelf unloaded\n");
}

module_init(lkm_init);
module_exit(lkm_cleanup);

