#pragma once
#include "saul_reg.h"

typedef struct measurement {
    int Ax, Ay, Az, Gx, Gy, Gz;
} measurement;

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement *values);