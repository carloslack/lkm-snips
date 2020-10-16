/*
 *  knetfilter.c
 *  Carlos Carvalho
 *  Linux ubuntu 5.4.0-42-generic
 *
 *  Simple netfilter example
 */
#include <linux/module.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlos Carvalho");

/* operations struct for the callback */
static struct nf_hook_ops ops;

/* cosmetics */
typedef struct packet_descriptors{
    int type;
    const char *desc;
}packet_descriptors_t;

static packet_descriptors_t descriptor[]=
{
    {0x0800, "IP"},
    {0x0806, "Address Resolution"},
    {0x8035, "Reverse Arp"},
    {0x0200, "Xerox PUP"},
    {0x0060, "Ethernet loopback"},
    {0x0201, "Xeror PUP Addr"},
    {-1, ""}
};

/**
 * Just try to resolve some
 * ethernet packet type names
 */
static const char *translate_arp_id(int id) {
    int i;
    for (i = 0; descriptor[i].type != -1; ++i) {
        if (id == descriptor[i].type)
            return descriptor[i].desc;
    }
    return "Unhandled";
}

static unsigned int hook_cb(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    /* skb_* functions will do the hard work of selecting the correct buffers */
    struct ethhdr *eth = (struct ethhdr *)skb_mac_header(skb);
    struct iphdr *iph = (struct iphdr *)skb_network_header(skb);

    uint16_t ethproto = ntohs(eth->h_proto);

    /*
     * print some fields and that's it
     * check output with: dmesg -wH
     */
    pr_info("Ethernet MAC source %pM, destination %pM, proto=0x%04x [%s]\n",
            eth->h_source, eth->h_dest, ethproto, translate_arp_id(ethproto));
    pr_info("IP source %pI4, destination %pI4, checksum=0x%04x\n", &iph->saddr, &iph->daddr, ntohs(iph->check));

    return NF_ACCEPT;
}

static int __init lkm_init(void) {

    ops.hook = hook_cb;
    ops.pf = PF_INET;
    /* We'll get the packets before they are routed */
    ops.hooknum = NF_INET_PRE_ROUTING;
    /* High priority in relation to other existent hooks */
    ops.priority = NF_IP_PRI_FIRST;

    /* Does the magic */
    nf_register_net_hook(&init_net, &ops);

    return 0;
}

static void __exit lkm_cleanup(void) {
    /* do not miss this */
    nf_unregister_net_hook(&init_net, &ops);
}

module_init(lkm_init);
module_exit(lkm_cleanup);

