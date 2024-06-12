#pragma once

#include "net/gnrc/netapi.h"
#include "net/gnrc/netif.h"
#include "net/ipv6/addr.h"
#include "net/gnrc.h"
#include "net/gnrc/ipv6/hdr.h"
#include "net/utils.h"
#include "net/netif.h"

#include "measurements.h"

/* Should be run in a separate thread */
void* sender_loop(void *arg);

/* Sends a packet with the given measurement to the given address */
int send_packet(ipv6_addr_t *addr, netif_t **netif, measurement_t *measurement);
