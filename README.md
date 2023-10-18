## LKM code snippets

<p align="left">
    <a href="https://github.com/carloslack/lkm_snips/blob/master/LICENSE"><img alt="Software License" src="https://img.shields.io/badge/MIT-license-green.svg?style=flat-square"></a>
</p>

## Run
    $ git submodule update --init
    $ make

    Each module has a README file with more details.

## Modules summary

### Kdis
    Disassembler that uses Beaengine engine,
    patched to load from kernel modules:
        https://github.com/carloslack/beaengine/tree/use_in_kernel_patch
    to dump the first bytes that make up of a kernel object, like a syscall,
    API or structure.
    Use cases e.g.: kernel function trampoline, rootkits, anti-rootkits and IDS's ...

### Kelf
    Read running ELF objects from kernel memory in similar fashion a userland ELF
    parser would.
    The ELF file is always the one that originated the PID. E.g.: ./a.out &
    Use cases e.g.: ELF runtime infection, IDS's ...

### Kstat
    Read inode stats from given running process.
    Again, the file is always the one that originate the PID.

### Knf
    Kernel netfilter usage example.

### Gotchas
    All these modules have been tested only on 5.4.0-48-generic.
