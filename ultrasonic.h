#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

typedef struct {
    uint16_t distance_cm;
    uint8_t valid;
} distance_reading_t;

/* Returns valid=0 if no echo is received before timeout. */
distance_reading_t ultrasonic_read_cm(void);

#endif
