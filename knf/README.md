## Knf

## About
    Show a very simple example on how to work with the netfilter.

## Build:
    make

## Run
    insmod ./knf.ko

## Example

    --- snip ---
     $ sudo insmod ./kelf.ko my_pid=18846 && sudo rmmod kelf ; dmesg
    --- snip ---

    --- snip ---
     $ sudo insmod ./knf.ko && dmesg -wH
    [  +0.000004] IP source 192.xxx.xxx.xxx, destination 192.xxx.xxx.xxx
    [  +0.036899] Ethernet MAC source 7a:76:61:bf:4b:6d, destination 01:00:5a:7f:ff:fa, proto=0x0800 [IP]
    [  +0.000008] IP source 192.xxx.xxx.xxx, destination 239.xxx.xxx.xxx
    [  +0.412396] Ethernet MAC source 48:d3:43:4a:d6:68, destination 78:0c:b8:7a:51:19, proto=0x0800 [IP]
    [  +0.000003] IP source 104.xxx.xxx.xxx, destination 192.xxx.xxx.xxx
    --- snip ---

    When you're done
    --- snip ---
     $ sudo rmmod knf.ko
    --- snip ---

