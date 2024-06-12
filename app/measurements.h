#pragma once

#include "net/gnrc/pkt.h"
#include "saul_reg.h"

void get_rssi(gnrc_pktsnip_t const * pkt);

void get_measurement(measurement_t *measurement);


typedef struct {
    int Ax, Ay, Az, Gx, Gy, Gz;
} measurement_t;

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement_t *values);
