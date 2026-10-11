#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include <avr/io.h>
#include <stdint.h>

/* Verify this clock against the actual Firebird V board configuration. */
#ifndef F_CPU
#define F_CPU 14745600UL
#endif
#define F_CPU_HZ F_CPU

/*
 * REQUIRED: Set these macros to the actual trigger and echo pins you wired.
 * Example format only (NOT a recommendation): TRIG_DDR = DDRx,
 * TRIG_PORT = PORTx, TRIG_PIN = PxN. Do not leave these placeholders.
 */
#ifndef TRIG_DDR
#error "Define TRIG_DDR in project_config.h for your actual ultrasonic trigger pin"
#endif
#ifndef TRIG_PORT
#error "Define TRIG_PORT in project_config.h for your actual ultrasonic trigger pin"
#endif
#ifndef TRIG_PIN
#error "Define TRIG_PIN in project_config.h for your actual ultrasonic trigger pin"
#endif
#ifndef ECHO_DDR
#error "Define ECHO_DDR in project_config.h for your actual ultrasonic echo pin"
#endif
#ifndef ECHO_PIN_REG
#error "Define ECHO_PIN_REG in project_config.h for your actual ultrasonic echo pin register"
#endif
#ifndef ECHO_PIN
#error "Define ECHO_PIN in project_config.h for your actual ultrasonic echo pin"
#endif

#define OBSTACLE_THRESHOLD_CM  20U
#define SENSOR_TIMEOUT_US      30000UL
#define LCD_REFRESH_MS         250U

/* Confirm buzzer wiring on your actual robot before enabling. */
#define BUZZER_DDR   DDRC
#define BUZZER_PORT  PORTC
#define BUZZER_PIN   PC3

#endif
