#pragma once

#include "net/gnrc/pkt.h"
#include "saul_reg.h"
#include "net/ipv6/addr.h"

// TODO: might also require the timestamp and some kind of identifier or we need a measurement_t struct AND
// a message_t struct that has all information
// what is with the precision of the values? Is int16_t enough? Can we do better?
typedef struct {
    int16_t Ax, Ay, Az, Gx, Gy, Gz;
    int pkt_number;
    // uint8_t mac[2];
} measurement_t;

// TODO: extract the RSSI value from the packet
void get_rssi_from_pkt(gnrc_pktsnip_t const *pkt);

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement_t *values);

bool find_saul(saul_reg_t **accel, saul_reg_t **gyro);

void print_measurment(measurement_t const *measurement, int16_t const *rssi, uint8_t const *lqi,
uint64_t const *timestamp, ipv6_addr_t const *addr);
