#ifndef VEMU_VGA_H
#define VEMU_VGA_H

#include<stddef.h>
#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;

typedef enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_YELLOW = 14,
	VGA_COLOR_WHITE = 15,
} vga_color;

typedef struct {
	unsigned char ch;
	vga_color bg;
	vga_color fg;
} vga_entry_t;

/**
 *
 * Returns number with color and character.
 *
 * @param character
 * @param color
 *
 */

uint16_t vga_entry(unsigned char, uint8_t);

/**
 *
 * Returns joined colors.
 *
 * @param color #1
 * @param color #2
 *
 */
uint8_t vga_entry_color(vga_color, vga_color);

/**
 *
 * Reads the VGA entry.
 *
 */
vga_entry_t vga_read_entry(uint16_t);

size_t vga_get_index(size_t, size_t);

#ifdef __cplusplus
}
#endif

#endif /* VEMU_VGA_H */
