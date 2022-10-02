#ifndef VEMU_COMPILER_H
#define VEMU_COMPILER_H
#include <stdio.h>
#include "vemu/vga.h"

#ifdef __cplusplus
extern "C" {
#endif

char *make_cs_color(char *, vga_entry_t);
void compile_csharp(FILE *, FILE *);

#ifdef __cplusplus
}
#endif

#endif /* VEMU_COMPILER_H */