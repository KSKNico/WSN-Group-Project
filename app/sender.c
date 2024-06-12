#include "sender.h"
#include "saul_reg.h"
#include "measurements.h"
#include <stdio.h>


void *retrieve_values(void) {
    saul_reg_t *accel = saul_reg_find_type(SAUL_SENSE_ACCEL);
    if(!accel) {
        puts("Error retrieving accelerometer sensor.");
        return NULL;
    }
    
    saul_reg_t *gyro = saul_reg_find_type(SAUL_SENSE_GYRO);
    if(!gyro) {
        puts("Error retrieving gyroscope sensor.");
        return NULL;
    }
    
    measurement result;
    int pkt_number = 0;

    while(1) {
        record_all_values(accel, gyro, &result);
        pkt_number = pkt_number + 1;
        printf("Ax: %d, Ay: %d, Az: %d, Gx: %d, Gy: %d, Gz: %d\n",
            result.Ax, result.Ay, result.Az, result.Gx, result.Gy, result.Gz);
    }
}