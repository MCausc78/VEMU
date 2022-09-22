#include "vemu/tty.h"
#include "vemu/vga.h"
#include <string.h>

#include <stddef.h>
#include <stdint.h>

size_t tty_row;
size_t tty_col;
uint8_t tty_color;
uint16_t tty_buf[2080];

void tty_set_default_color(void) {
	tty_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void tty_set_row(size_t nrow) {
	tty_row = nrow;
}

void tty_set_col(size_t ncol) {
	tty_col = ncol;
}

void tty_clear(void) {
	tty_row = 0;
	tty_col = 0;
	for(size_t y = 0; y < VGA_HEIGHT; y++)
		for(size_t x = 0; x < VGA_WIDTH; x++)
			tty_putchar_at(' ', x, y);
}

void tty_scroll(void) {
	memmove(tty_buf, tty_buf + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1) * sizeof(uint16_t));
	size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH;
	for(size_t x = 0; x < VGA_WIDTH; ++x)
		tty_buf[index + x] = vga_entry(' ', tty_color);
	--tty_row;
}

void tty_setcolor(uint8_t color) {
	tty_color = color;
}

void tty_putcchar_at(char c, uint8_t color, size_t x, size_t y) 
{
	if(c == '\a' || c == '\b' || c == 'f' || c == '\n' || c == '\r') return;
	tty_buf[(vga_get_index(x, y))] = vga_entry(c, color);
}

void tty_putchar_at(char c, size_t x, size_t y) {
	tty_putcchar_at(c, tty_color, x, y);
}

void tty_putchar(char c) 
{
	unsigned char uc = c;
	tty_putchar_at(uc, tty_col, tty_row);
	if(++tty_col == VGA_WIDTH) {
		tty_col = 0;
		if (++tty_row == VGA_HEIGHT)
			tty_scroll();
	}
	// first, check for control character, so we didnt display non-printable ASCII
	// also, we making logic for control character!
	switch(uc) {
		case '\a':
			// this is VGA emulator!
			tty_col--;
			break;
		case '\b':
			if(tty_col > 1)
				tty_col -= 2;
			break;
		case '\t':
			// 4 times
			for(int i=0; i<5; i++)
				tty_putchar(' ');
			break;
		case '\n':
			// new line
			tty_col = 0;
			tty_row++;
			break;
		case '\f':
			tty_clear();
			break;
		case '\r':
			tty_col = 0;
			break;
	}
}

void tty_putcchar(char c, uint8_t color) {
	uint8_t oldColor = tty_color | 0;
	tty_setcolor(color);
	tty_putchar(c);
	tty_setcolor(oldColor);
}