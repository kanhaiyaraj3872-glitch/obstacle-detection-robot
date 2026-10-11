#include "project_config.h"
#include "ultrasonic.h"
#include <util/delay.h>

/*
 * Simple blocking HC-SR04-style interface.
 * Verify your sensor's trigger pulse and echo timing requirements.
 * This uses a polling loop; for a production design, timer/input-capture
 * measurement is preferable when precise timing or low latency is required.
 */
static uint8_t wait_for_level(uint8_t level, uint32_t timeout_us)
{
    while (((ECHO_PIN_REG & (1U << ECHO_PIN)) != 0U) != (level != 0U)) {
        if (timeout_us == 0U) {
            return 0U;
        }
        _delay_us(1);
        timeout_us--;
    }
    return 1U;
}

distance_reading_t ultrasonic_read_cm(void)
{
    distance_reading_t result = {0U, 0U};
    uint32_t pulse_us = 0UL;

    /* Trigger pin output; echo pin input. */
    TRIG_DDR |= (1U << TRIG_PIN);
    ECHO_DDR &= (uint8_t)~(1U << ECHO_PIN);

    TRIG_PORT &= (uint8_t)~(1U << TRIG_PIN);
    _delay_us(3);
    TRIG_PORT |= (1U << TRIG_PIN);
    _delay_us(10);
    TRIG_PORT &= (uint8_t)~(1U << TRIG_PIN);

    if (!wait_for_level(1U, SENSOR_TIMEOUT_US)) {
        return result;
    }

    while ((ECHO_PIN_REG & (1U << ECHO_PIN)) != 0U) {
        if (pulse_us >= SENSOR_TIMEOUT_US) {
            return result;
        }
        _delay_us(1);
        pulse_us++;
    }

    /*
     * Approximate conversion for a typical ultrasonic module:
     * distance_cm ~= echo_pulse_us / 58.
     * Validate against the exact sensor datasheet and clock/timing setup.
     */
    result.distance_cm = (uint16_t)(pulse_us / 58UL);
    result.valid = 1U;
    return result;
}
