#include "vemu/vga.h"

#include <stdint.h>
#include <stddef.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
	/* Reading: uint16_t ch = (entry & 0xff);
			 uint8_t color = ((entry & 0xff00) >> 8);
	 */
}
uint8_t vga_entry_color(vga_color fg, vga_color bg) {
	return fg | bg << 4;
	/* Reading: uint8_t fg = (entry & 0b0f);
	         uint8_t bg = (entry & 0xf0) >> 4;
	 */
}

vga_entry_t vga_read_entry(uint16_t entry) {
	vga_entry_t r;
	r.ch = (entry & 0xff);
	uint8_t color = ((entry & 0xff00) >> 8);
	r.bg = ((color & 0xf0) >> 4);
	r.fg = ((color & 0x0f));
	return r;
}

size_t vga_get_index(size_t x, size_t y) {
	return (y * VGA_WIDTH + x);
}