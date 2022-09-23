#ifndef VEMU_COMPILER_H
#define VEMU_COMPILER_H
#include <stdio.h>
#include "vemu/vga.h"

char *make_cs_color(char *, vga_entry_t);
void compile(FILE *, FILE *);

#endif /* VEMU_COMPILER_H */