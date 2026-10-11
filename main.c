#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include "project_config.h"
#include "ultrasonic.h"
#include "lcd_adapter.h"

/*
 * IMPORTANT:
 * Replace these motor adapter bodies with the verified Firebird V motor
 * library functions from your lab. The safe default is to keep motors stopped.
 */
static void motor_stop(void)
{
    /* TODO: call the actual Firebird V motor-stop function here. */
}

static void motor_forward(void)
{
    /* TODO: call the actual Firebird V forward-motion function here. */
}

static void buzzer_set(uint8_t on)
{
    if (on) {
        BUZZER_PORT |= (1U << BUZZER_PIN);
    } else {
        BUZZER_PORT &= (uint8_t)~(1U << BUZZER_PIN);
    }
}

static void show_distance(uint16_t cm, const char *status)
{
    char line[17];
    (void)snprintf(line, sizeof(line), "Distance:%3u cm", (unsigned int)cm);
    lcd_adapter_print_line(0U, line);
    lcd_adapter_print_line(1U, status);
}

int main(void)
{
    distance_reading_t reading;

    BUZZER_DDR |= (1U << BUZZER_PIN);
    buzzer_set(0U);
    motor_stop();

    lcd_adapter_init();
    lcd_adapter_clear();
    lcd_adapter_print_line(0U, "Obstacle Detect");
    lcd_adapter_print_line(1U, "Initializing...");
    _delay_ms(1000);

    while (1) {
        reading = ultrasonic_read_cm();

        if (!reading.valid) {
            /* Fail-safe: no valid distance means do not continue forward. */
            motor_stop();
            buzzer_set(1U);
            lcd_adapter_print_line(0U, "Sensor timeout");
            lcd_adapter_print_line(1U, "Motors stopped");
        } else if (reading.distance_cm <= OBSTACLE_THRESHOLD_CM) {
            motor_stop();
            buzzer_set(1U);
            show_distance(reading.distance_cm, "OBSTACLE!");
        } else {
            buzzer_set(0U);
            show_distance(reading.distance_cm, "Path clear");
            motor_forward();
        }

        _delay_ms(LCD_REFRESH_MS);
    }
}
