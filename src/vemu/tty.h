#ifndef VEMU_TTY_H
#define VEMU_TTY_H

#include<stddef.h>
#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern size_t tty_row;
extern size_t tty_col;
extern uint8_t tty_color;
extern uint16_t tty_buf[];

/**
 *
 * Returns default color.
 *
 */
void tty_set_default_color(void);

void tty_set_row(size_t);

void tty_set_col(size_t);

/**
 *
 * Clears TTY.
 *
 */
void tty_clear(void);

/**
 *
 * Scroll.
 *
 */
void tty_scroll(void);

/**
 *
 * Set color.
 *
 * @param color
 *
 */
void tty_setcolor(uint8_t);

/**
 *
 * Draw colored character in `x` and `y`.
 *
 * @param character
 * @param color
 * @param pos x
 * @param pos y
 *
 */
void tty_putcchar_at(char, uint8_t, size_t, size_t);

/**
 *
 * Draw character in `x` and `y`.
 *
 * @param character
 * @param x
 * @param y
 *
 */
void tty_putchar_at(char, size_t, size_t);


/**
 *
 * Display the character.
 *
 * @param character
 *
 */
void tty_putchar(char);

/**
 *
 * Display the colored character.
 *
 * @param character
 *
 */
void tty_putcchar(char, uint8_t);

#ifdef __cplusplus
}
#endif

#endif /* VEMU_TTY_H */