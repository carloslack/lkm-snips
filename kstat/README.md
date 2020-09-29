## Kstat

## Build:
    make

## Run
    insmod ./kstat.ko my_pid<#pid>

    This example shows a few useful use cases when writing
    a LKM:
        - How to pass arguments to a module at loading time
        - How to break down kernel structures and make sense of them
        - How to work with task_struct: arguably one of the key structures in Linux kernel

## Example
        --- snip ---
        $ ps ax |grep vim
        50425 ?        Ssl    0:06 gvim
        --- snip ---

        --- snip ---
        $ sudo insmod ./task.ko my_pid=50425 && sudo rmmod task ; sudo dmesg -c
        [19225.029711] Checking PID: 50425
        [19225.029713] task loading...
        [19225.029715] filename: vim.gtk
        [19225.029715] <stat>
        [19225.029716] 	major: 8
        [19225.029716] 	minor: 1
        [19225.029716] 	rmask: 0x800
        [19225.029717] 	mode: 0x81ed
        [19225.029717] 	attributes: 0x0
        [19225.029717] 	attributes_mask: 0x874
        [19225.029718] 	ino : 1190302
        [19225.029718] 	dev : 8388609
        [19225.029718] 	rdev : 0
        [19225.029719] 	uid: 0
        [19225.029719] 	gid: 0
        [19225.029719] 	size: 3182168
        [19225.029719] 	atime.tv_sec: 1601393888
        [19225.029720] 	atime.tv_usec: 63957856
        [19225.029757] 	mtime.tv_sec: 1584556155
        [19225.029758] 	mtime.tv_usec: 0
        [19225.029758] 	ctime.tv_sec: 1587465966
        [19225.029759] 	ctime.tv_usec: 467636063
        [19225.029759] 	btime.tv_sec: 1587465966
        [19225.029759] 	btime.tv_usec: 335609359
        [19225.029759] 	blocks: 6216
        [19225.029760] </stat>
        [19225.039837] task unloaded
        --- snip ---

        --- snip ---
        $ stat /usr/bin/vim.gtk
          File: /usr/bin/vim.gtk
          Size: 3182168   	Blocks: 6216       IO Block: 4096   regular file
        Device: 801h/2049d	Inode: 1190302     Links: 1
        Access: (0755/-rwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
        Access: 2020-09-29 08:38:08.063957856 -0700
        Modify: 2020-03-18 11:29:15.000000000 -0700
        Change: 2020-04-21 03:46:06.467636063 -0700
         Birth: -
        --- snip ---
