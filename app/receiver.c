#include "receiver.h"

#include <stdio.h>

#define MSG_QUEUE_SIZE  8

void receive_pkt(measurement_t *measurement, int16_t *rssi) {
    msg_t msg;

    msg_receive(&msg);
    if (msg.type == GNRC_NETAPI_MSG_TYPE_RCV) {
        gnrc_pktsnip_t *pkt = msg.content.ptr;

        memcpy(measurement, pkt->data, pkt->size);
        *rssi = pkt->data->rssi;
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
    while(1) {
        receive_pkt(&measurement, &rssi);
        print_measurment(&measurement, &rssi);
    }

    gnrc_netreg_unregister(GNRC_NETTYPE_IPV6, &server);
}

