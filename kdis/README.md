Kdis

    Build:
	make

    POC showing a simple use case for
    BeaEngine (https://github.com/BeaEngine/beaengine)
    patched to compile on Linux kernel:
        https://github.com/carloslack/beaengine/tree/use_in_kernel_patch

    In this example it displays up to JMPLEN bytes of given kernel function, broken down
    by instruction sets - useful if you want to function trampoline in kernel.

    Output for vfs_rmdir

        --- snip ---
        [ ubuntu<!!! VM !!!> * 14:53:28 (run_example) ~/lkm_snips/kdis ]
         $ sudo insmod ./kdis.ko 
        [ ubuntu<!!! VM !!!> * 14:53:35 (run_example) ~/lkm_snips/kdis ]
         $ dmesg
        [57070.589538] instr_size: 5
        [57070.589540] 0f
        [57070.589541] 1f
        [57070.589541] 44
        [57070.589541] 00
        [57070.589542] 00

        [57070.589543] instr_size: 1
        [57070.589543] 55

        [57070.589545] instr_size: 5
        [57070.589545] ba
        [57070.589545] 01
        [57070.589546] 00
        [57070.589546] 00
        [57070.589546] 00

        [57070.589548] instr_size: 3
        [57070.589548] 48
        [57070.589548] 89
        [57070.589548] e5

        [57070.589549] instr_size: 2
        [57070.589550] 41
        [57070.589550] 56

        [57070.589550] total=16
        --- snip ---

    So then we have the first 16 bytes of instructions
    for vfs_rmdir (syscall implementation for rmdir):

        0F 1F 44 00 00    nop  dword ptr [rax + rax]
        55                push rbp
        BA 01 00 00 00    mov  edx, 1
        48 89 E5          mov  rbp, rsp
        41 56             push r14

