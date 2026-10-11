# Pin Map (Complete from your actual board and wiring)

Do not assume pin assignments. Fill this table after checking the Firebird V manual, schematic, and sensor wiring.

| Function | MCU port/pin | Direction | Voltage level | Verified? |
|---|---|---|---|---|
| Ultrasonic trigger | TO FILL | Output | TO CHECK | No |
| Ultrasonic echo | TO FILL | Input | TO CHECK | No |
| LCD interface | From supplied `lcd.c` / `lcd.h` | Mixed | TO CHECK | No |
| Buzzer | PC3 only if confirmed for this setup | Output/driver | TO CHECK | No |
| Motor driver control | From Firebird V motor library | Output | TO CHECK | No |
| Ground reference | Board/system ground as specified | — | — | No |

## Verification checklist

- [ ] Exact controller board confirmed.
- [ ] Sensor module model confirmed.
- [ ] Sensor echo output is compatible with MCU input.
- [ ] LCD function names and pin mapping checked against supplied library.
- [ ] Motor control function names checked against lab code.
- [ ] Buzzer pin confirmed on the actual board.
