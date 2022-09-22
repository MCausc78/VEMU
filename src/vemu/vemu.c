#include "vemu/vemu.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "vemu/vga.h"
#include "vemu/tty.h"

int vemu_is_dir(const char *path) {
	struct stat s;
	stat(path, &s);
	return S_ISREG(s.st_mode);
}

char *make_char(char *txt, vga_entry_t entry) {
	char bg = 0;
	char fg = 0;
	switch(entry.bg) {
		case 0x00: bg = 40; break;
		case 0x01: bg = 44; break;
		case 0x02: bg = 42; break;
		case 0x03: bg = 46; break;
		case 0x04: bg = 41; break;
		case 0x05: bg = 45; break;
		case 0x06: bg = 43; break;
		case 0x07: bg = 47; break;
		case 0x08: bg = 100; break;
		case 0x09: bg = 104; break;
		case 0x0A: bg = 102; break;
		case 0x0B: bg = 106; break;
		case 0x0C: bg = 101; break;
		case 0x0D: bg = 105; break;
		case 0x0E: bg = 103; break;
		case 0x0F: bg = 107; break;
	}
	switch(entry.fg) {
		case 0x00: fg = 30; break;
		case 0x01: fg = 34; break;
		case 0x02: fg = 32; break;
		case 0x03: fg = 36; break;
		case 0x04: fg = 31; break;
		case 0x05: fg = 35; break;
		case 0x06: fg = 33; break;
		case 0x07: fg = 37; break;
		case 0x08: fg = 90; break;
		case 0x09: fg = 94; break;
		case 0x0A: fg = 92; break;
		case 0x0B: fg = 96; break;
		case 0x0C: fg = 91; break;
		case 0x0D: fg = 95; break;
		case 0x0E: fg = 93; break;
		case 0x0F: fg = 97; break;
	}
	sprintf(txt, "\033[%d;%dm%c\033[0m", bg, fg, (entry.ch == 0 ? ' ' : entry.ch));
	return txt;
}

#define VGA_FILE ((argc <= 1 ? "vga.bin" : argv[1]))

int main(int argc, char **argv) {
	tty_set_default_color();
	tty_clear();
	FILE *fp;
	fp = fopen(VGA_FILE, "r");
	if(fp == NULL) {
		perror(VGA_FILE);
		return 1;
	}
	if(vemu_is_dir(VGA_FILE) == 0) {
		fprintf(stderr, "vemu: %s: Is a directory\n", VGA_FILE);
		fclose(fp);
		return 2;
	}
	for(int c, ch; ch != EOF; ) {
		c = getc(fp);
		ch = getc(fp);
		if(c == EOF || ch == EOF)
			break;
		tty_putcchar(ch, c);
	}
	fclose(fp);
	/*
	 *
	 * Signature of bytes in file:
	 *	1 byte => 8 bits <- color
	 *	2 byte => 8 bits <- character
	 * "Hi!" program on black background and white foreground look like this:
	 *	0F 48 0F 69 0F 21
	 * And "Hello, world!":
	 *	0F 48 0F 65 0F 6C 0F 6C 0F 6F 0F 2C 0F 20 0F 77 0F 6F 0F 72 0F 6C 0F 64 0F 21
	 *
	 */
	puts("+--------------------------------------------------------------------------------+");
	char txt[32];
	for(size_t y=0; y < VGA_HEIGHT; y++) {
		putchar('|');
		for(size_t x=0; x < VGA_WIDTH; x++) {
			/*
			 * (&txt) = warning: passing argument 1 of 'make_char' from incompatible pointer type
			 * (&txt[0]) = no compiler warning
			 */
			printf("%s", make_char((&txt[0]),
				vga_read_entry(
					tty_buf[vga_get_index(x, y)]
				)
			));
		}
		puts("\033[0m|");
	}
	puts("+--------------------------------------------------------------------------------+");
	return 0;
}