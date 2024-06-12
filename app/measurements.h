#pragma once

#include "net/gnrc/pkt.h"
#include "saul_reg.h"

// TODO: might also require the timestamp and some kind of identifier or we need a measurement_t struct AND
// a message_t struct that has all information
// what is with the precision of the values? Is int16_t enough? Can we do better?
typedef struct {
    int16_t Ax, Ay, Az, Gx, Gy, Gz;
} measurement_t;

// TODO: extract the RSSI value from the packet
void get_rssi_from_pkt(gnrc_pktsnip_t const *pkt);

// TODO: extract the measurement from the packet
void get_measurement_from_pkt(gnrc_pktsnip_t const *pkt, measurement_t *measurement);

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement_t *values);

bool find_saul(saul_reg_t **accel, saul_reg_t **gyro);
