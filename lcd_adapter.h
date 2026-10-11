#ifndef LCD_ADAPTER_H
#define LCD_ADAPTER_H

#include <stdint.h>

/*
 * Implement these functions in your own lcd_adapter.c by calling the
 * functions provided in your lab's lcd.c / lcd.h.
 * Their function names vary by LCD library, so this file intentionally
 * does not assume a particular LCD API.
 */
void lcd_adapter_init(void);
void lcd_adapter_clear(void);
void lcd_adapter_print_line(uint8_t row, const char *text);

#endif
