#include "sender.h"

int send_packet(ipv6_addr_t *addr, netif_t **netif, measurement_t *measurement) {


    gnrc_pktsnip_t *payload, *ip;
    ipv6_hdr_t *ip_hdr;
    size_t payload_size = sizeof(measurement_t);

    /* start packet with payload */
    payload = gnrc_pktbuf_add(NULL, (void *) measurement, payload_size, GNRC_NETTYPE_UNDEF);
    if (payload == NULL) {
        puts("Unable to copy message to packet buffer");
        return 1;
    }

    /* add IPv6 header with payload as next header */
    ip = gnrc_ipv6_hdr_build(payload, NULL, addr);
    if (ip == NULL) {
        puts("Unable to allocate IPv6 header");
        gnrc_pktbuf_release(payload);
        return 1;
    }

    /* set IPv6 next header to experimental protocol number 253 */
    ip_hdr = ip->data;
    ip_hdr->nh = 253;
    if (*netif != NULL) {
        /* add link layer if netif is provided in argv[1] */
        gnrc_pktsnip_t *netif_hdr = gnrc_netif_hdr_build(NULL, 0, NULL, 0);
        if (netif_hdr == NULL) {
            puts("Unable to allocate netif header");
            gnrc_pktbuf_release(ip);
            return 1;
        }
        /* set GNRC specific network interface values */
        gnrc_netif_hdr_set_netif(netif_hdr->data,
                                container_of(*netif, gnrc_netif_t, netif));
        /* prepend link layer header to IP packet */
        ip = gnrc_pkt_prepend(ip, netif_hdr);

        if (!gnrc_netapi_dispatch_send(GNRC_NETTYPE_IPV6,
            GNRC_NETREG_DEMUX_CTX_ALL, ip)) {
            printf("Unable to locate IP thread");
            gnrc_pktbuf_release(ip);
            return 1;
        }
    }
    return 0;
}

void* sender_loop(void *arg) {
    ipv6_addr_t addr;
    netif_t *netif;
    if (netutils_get_ipv6(&addr, &netif, (char *) arg) < 0) {
        puts("Unable to parse IPv6 address\n");
        return NULL;
    }
    measurement_t current_measurement;
    while (1) {
        get_measurement(&current_measurement);
        send_packet(&addr, &netif, &current_measurement);
    }
}