#include "receiver.h"

#include <stdio.h>

#define MSG_QUEUE_SIZE  8

void receive_pkt(measurement_t *measurement, int16_t *rssi, ipv6_addr_t *addr) {
    msg_t msg;
    msg_receive(&msg);
   /* uint8_t *ip_addr_buffer = ip_addr->u8;*/
    if (msg.type == GNRC_NETAPI_MSG_TYPE_RCV) {
        gnrc_pktsnip_t *pkt = msg.content.ptr;

        gnrc_pktsnip_t* netif_snip = gnrc_pktsnip_search_type(pkt, GNRC_NETTYPE_NETIF);
        gnrc_pktsnip_t* ipv6_snip = gnrc_pktsnip_search_type(pkt, GNRC_NETTYPE_IPV6); 

        memcpy(measurement, pkt->data, pkt->size);
        gnrc_netif_hdr_t *netif_hdr = (gnrc_netif_hdr_t *)netif_snip->data;
        ipv6_hdr_t *ipv6_hdr = (ipv6_hdr_t *) ipv6_snip->data;

        memcpy(addr, &(ipv6_hdr->src), sizeof(ipv6_addr_t));


        *rssi = netif_hdr->rssi;
        
        // timestamp does not work!
        // *timestamp = netif_hdr->timestamp;

        /*
        if (addr_len != 16) {
            puts("Error: Address length is not 16 bytes.");
            return;
        }
        */
        
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
    uint64_t timestamp;
    ipv6_addr_t addr;
    
    while(1) {
        timestamp = (uint64_t) ztimer_now(ZTIMER_MSEC);
        receive_pkt(&measurement, &rssi, &addr);
        print_measurment(&measurement, &rssi, &timestamp, &addr);
    }

    gnrc_netreg_unregister(GNRC_NETTYPE_IPV6, &server);
}

