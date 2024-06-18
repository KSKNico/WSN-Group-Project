#include "receiver.h"

#include <stdio.h>

#define MSG_QUEUE_SIZE  8

void receive_pkt(ipv6_addr_t *ip_addr, measurement_t *measurement, int16_t *rssi) {
    msg_t msg;
    msg_receive(&msg);
    uint8_t *ip_addr_buffer = ip_addr->u8;
    if (msg.type == GNRC_NETAPI_MSG_TYPE_RCV) {
        gnrc_pktsnip_t *pkt = msg.content.ptr;

        memcpy(measurement, pkt->data, pkt->size);
        gnrc_netif_hdr_t *netif_hdr = (gnrc_netif_hdr_t *)pkt->data;
        *rssi = netif_hdr->rssi;

        int addr_len = gnrc_netif_hdr_get_srcaddr(pkt, &ip_addr_buffer);

        if (addr_len != 16) {
            puts("Error: Address length is not 16 bytes.");
            return;
        }

        
        gnrc_pktbuf_release(pkt);
    }
} 

void* receiver_loop(void* arg) {
    (void) arg;
    printf("Starting receiver loop\n");

    msg_t msg_queue[MSG_QUEUE_SIZE];
    msg_init_queue(msg_queue, MSG_QUEUE_SIZE);

    gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(253, thread_getpid());
    gnrc_netreg_register(GNRC_NETTYPE_IPV6, &server);
    
    measurement_t measurement;   
    int16_t rssi;
    ipv6_addr_t ipv6_addr;
    while(1) {
        receive_pkt(&ipv6_addr, &measurement, &rssi);
        print_measurment(&measurement, &rssi, &ipv6_addr);
    }

    gnrc_netreg_unregister(GNRC_NETTYPE_IPV6, &server);
}

