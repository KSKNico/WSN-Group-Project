#pragma once

#include "net/gnrc/pkt.h"

typedef struct {
    // What are we measuring?
}
measurement_t;

typedef struct {
    measurement_t measurement;
    
} result_t;

void get_rssi(gnrc_pktsnip_t const * pkt);

void get_measurement(measurement_t *measurement);
