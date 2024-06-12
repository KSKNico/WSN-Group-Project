#include "measurements.h"
#include "saul_reg.h"
#include "phydat.h"
#include <stdio.h>
#include "board.h"


int record_value(saul_reg_t* sensor, phydat_t *results) {
    int dim = saul_reg_read(sensor, results);
     if(dim < 1) {
        puts("Error reading a value from the device");
        return 1;      
    }
    phydat_dump(results, dim); /* print value*/
    return 0;
}

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement *values) {
    phydat_t accel;
    int res = record_value(accel_sensor, &accel);
    if(res != 0) {
        puts("Error reading a value from the accelerometer.");
        return 1;
    }
    phydat_t gyro;
    res = record_value(gyro_sensor, &gyro);
    if(res != 0) {
        puts("Error reading a value from the gyroscope.");
        return 1;
    }
    *values = (measurement){accel.val[0], accel.val[1], accel.val[2], gyro.val[0], gyro.val[1], gyro.val[2]};
    return 0;
}

