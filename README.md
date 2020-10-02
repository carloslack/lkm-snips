## LKM code snippets

[![Total alerts](https://img.shields.io/lgtm/alerts/g/carloslack/lkm_snips.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/carloslack/lkm_snips/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/carloslack/lkm_snips.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/carloslack/lkm_snips/context:cpp)

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
        LKM's https://github.com/carloslack/beaengine/tree/hack-da-shit-out-of-it
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

### Gotchas
    All these modules have been tested only on 5.4.0-48-generic.
