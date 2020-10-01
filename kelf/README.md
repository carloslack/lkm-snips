## Kelf

## Build:
    make

## About
    Manipulating ELF elf objects in the kernel is not so usual 
    but in the kernel it is done a lot: for core
    dumps,  everytime you run a program and etc...

    This is useful, however, in security and debugging, extending from this
    code would be very feasible in creating a Elf injection module, fuzzer and
    IDS.

## Run
    insmod ./kelf.ko my_pid=<#pid>

## Example
    --- snip ---
    $ ps ax |grep gvim
     18846 ?        Ssl    0:06 gvim
    --- snip ---

    --- snip ---
     $ sudo insmod ./kelf.ko my_pid=18846 && sudo rmmod kelf ; dmesg
    [ 3769.004557] kelf loading...
    [ 3769.004558] Checking PID: 18846
    [ 3769.004560] [!] Retrieving Elf64 from 'vim.gtk'
    [ 3769.004562] page_addr=000000003510ff03
    [ 3769.004563] 0x7f
    [ 3769.004563] E
    [ 3769.004563] L
    [ 3769.004563] F
    [ 3769.004564] type=0x03
    [ 3769.004564] EICLASS=2
    [ 3769.013728] kelf unloaded
    [19225.039837] task unloaded
    --- snip ---

    --- snip ---
    $ file /usr/bin/vim.gtk
     /usr/bin/vim.gtk: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0
    --- snip ---

## Notes
    Running against kthread PID will fail as they to not have
    an associated executable file.

# Tests
    Whoa! example:
        --- snip ---
         $ ps -ax |awk '{print $1}'|grep  ^[0-9] |while read pid ; do \
            sudo insmod ./kelf.ko my_pid=$pid ; sudo rmmod kelf ; sudo dmesg -c ; done
        --- snip ---

