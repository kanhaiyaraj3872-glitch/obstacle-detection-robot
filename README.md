# Firebird V Obstacle Detection and Distance Display

A starter embedded-C project for an ATmega2560-based Firebird V robot. It is intended to measure distance with a compatible ultrasonic module, display the reading on the robot's LCD, and stop the robot / activate the buzzer when an obstacle is closer than a configurable threshold.

> **Hardware honesty note:** This repository is a project starter, not a claim that the code has been tested on your exact robot. Firebird V versions, sensor interfaces, pin mappings, and the supplied `lcd.c` / `lcd.h` APIs can differ. Verify the exact board and sensor documentation before connecting or powering hardware. The LCD adapter and sensor pin mapping must be matched to your lab setup.

## Features planned

- Ultrasonic echo timing with a bounded timeout.
- Distance conversion to centimetres for a typical HC-SR04-style module.
- Configurable obstacle threshold.
- LCD status output through a small adapter interface.
- Buzzer output on `PC3` (consistent with the lab setup described for this project; verify your board wiring).
- Safe response to invalid readings: stop the motors and show a sensor error.
- Clear separation between sensing, display, and motor-control functions.

## Repository layout

```text
firebirdv-obstacle-detection/
├── README.md
├── .gitignore
├── LICENSE
├── src/
│   ├── main.c
│   └── ultrasonic.c
├── include/
│   ├── project_config.h
│   ├── ultrasonic.h
│   └── lcd_adapter.h
├── docs/
│   ├── architecture.md
│   ├── pin-map-template.md
│   └── test-plan.md
└── tests/
    └── bench-test-checklist.md
```

## Architecture

```text
Ultrasonic sensor
   | trigger / echo
   v
ATmega2560 firmware
   |----> LCD adapter ----> 16x2 LCD: distance + status
   |----> PC3 output ------> buzzer / buzzer driver
   |----> motor adapter ---> motor driver ---> DC motors
```

The motor adapter is deliberately isolated because the exact Firebird V motor-control library and wiring must be taken from your lab files. Until `motor_stop()` and `motor_forward()` are connected to the correct robot functions, do not run the robot with wheels on the floor.

## Before building

1. Confirm the exact ultrasonic module (for example, an HC-SR04-compatible module) and its operating voltage.
2. Fill in the trigger and echo port/pin definitions in `include/project_config.h`.
3. Check whether the echo output is safe for the ATmega2560 input voltage. Use suitable level shifting if required by the sensor/module.
4. Inspect the `lcd.c` and `lcd.h` supplied with your lab. Implement the functions declared in `include/lcd_adapter.h` using that library's actual function names.
5. Implement the motor adapter functions in `src/main.c` using the Firebird V motor-control library provided in your lab.
6. Verify the buzzer connection before using `PC3`; do not assume a pin mapping solely from this starter project.
7. Test the sensor and outputs with the motors disconnected or wheels lifted first.

## Build environment

Install AVR-GCC and AVR Libc on Linux (Debian/Ubuntu example):

```bash
sudo apt update
sudo apt install gcc-avr avr-libc binutils-avr make
```

The intended MCU is `atmega2560`. The project clock is set to `14.7456 MHz`, matching the clock used in the user's previous AVR lab code. **Verify this against the actual board** before compiling or relying on timing.

After configuring the pins and implementing the LCD/motor adapters, a typical compile command is:

```bash
avr-gcc -mmcu=atmega2560 -DF_CPU=14745600UL \
  -Iinclude -Os -Wall -Wextra \
  src/main.c src/ultrasonic.c path/to/your/lcd_adapter.c \
  -o obstacle_detection.elf
avr-objcopy -O ihex -R .eeprom obstacle_detection.elf obstacle_detection.hex
```

The adapter implementation and the appropriate motor library source files must be added to the command. This starter is not expected to link until those hardware-specific adapter functions are implemented.

## Configuration

Edit `include/project_config.h`:
- `F_CPU_HZ`: verified CPU clock.
- `TRIG_DDR`, `TRIG_PORT`, `TRIG_PIN`: ultrasonic trigger pin.
- `ECHO_DDR`, `ECHO_PIN_REG`, `ECHO_PIN`: ultrasonic echo input pin.
- `OBSTACLE_THRESHOLD_CM`: threshold used by the decision logic.
- `SENSOR_TIMEOUT_US`: maximum echo wait time.

The default trigger/echo pins are intentionally **not selected**. You must enter the pins that match your actual wiring. The code uses compile-time checks to make accidental use of unconfigured pins visible.

## Suggested demonstration

1. Show the LCD displaying a plausible distance with no nearby obstacle.
2. Move a flat target slowly toward the sensor.
3. Confirm the status changes when the reading falls below the configured threshold.
4. Confirm the buzzer activates and the motors stop using your verified motor adapter.
5. Repeat with the target removed and record results.
6. Test sensor disconnection / timeout safely with the motors disabled.

## Evidence to add after testing

Add your own real photos and results, for example:
- `docs/photos/robot_setup.jpg`
- `docs/photos/lcd_distance.jpg`
- `docs/test-results.md`

Do not add fabricated test results or claim a feature works until you have tested it on the hardware.

## GitHub upload

See the step-by-step instructions in the chat response. Create a new repository, upload this folder's contents, and copy the actual repository URL from GitHub. Do not use a made-up URL.
