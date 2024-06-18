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

int record_all_values(saul_reg_t* accel_sensor, saul_reg_t *gyro_sensor, measurement_t *values) {
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
    *values = (measurement_t){accel.val[0], accel.val[1], accel.val[2], gyro.val[0], gyro.val[1], gyro.val[2]};
    return 0;
}

bool find_saul(saul_reg_t **accel, saul_reg_t **gyro) {
    *accel = saul_reg_find_type(SAUL_SENSE_ACCEL);
    if(!*accel) {
        puts("Error retrieving accelerometer sensor.");
        return false;
    }
    
    *gyro = saul_reg_find_type(SAUL_SENSE_GYRO);
    if(!*gyro) {
        puts("Error retrieving gyroscope sensor.");
        return false;
    }

    return true;
}

void print_measurment(measurement_t const *measurement, int16_t const *rssi, ipv6_addr_t const *addr) {
        // convert ip addr to string
        char ip_addr_str[IPV6_ADDR_MAX_STR_LEN];
        ipv6_addr_to_str(ip_addr_str, addr, IPV6_ADDR_MAX_STR_LEN);
        printf("IP: %s, RSSI: %hd, Ax: %d, Ay: %d, Az: %d, Gx: %d, Gy: %d, Gz: %d\n",
        ip_addr_str,
        *rssi,
        measurement->Ax, measurement->Ay, measurement->Az, 
        measurement->Gx, measurement->Gy, measurement->Gz);
}