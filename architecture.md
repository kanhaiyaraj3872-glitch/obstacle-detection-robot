# Architecture Notes

## Data path

1. Ultrasonic module receives a trigger pulse.
2. The echo pulse width is measured with a timeout.
3. Firmware estimates distance in centimetres.
4. Invalid readings cause a safe response (motors stopped).
5. Valid readings are compared with `OBSTACLE_THRESHOLD_CM`.
6. LCD displays distance/status; buzzer indicates warning.
7. Motor adapter commands forward motion or stop.

## Design decisions

- **Modular code:** sensor, LCD adapter, and motor control are separated.
- **Fail-safe default:** motor stop is called at startup and on invalid readings.
- **Configurable threshold:** change `OBSTACLE_THRESHOLD_CM` after safe bench testing.
- **Hardware-specific adaptation:** exact pins, LCD API, and motor API must be matched to the actual lab kit.

## Known limitations

- Polling-based echo measurement is approximate and can be affected by compiler timing and interrupt activity.
- HC-SR04-style conversion is not universal to every ultrasonic sensor.
- This code does not implement turning, encoder feedback, multi-sensor fusion, or certified collision avoidance.
