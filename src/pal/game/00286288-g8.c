#include "include_asm.h"

extern char D_L00_001B8FF0[];
extern void func_00283738(char *a, char *b, char *c);
extern void func_002ACE78(char *a, char *b, float f);
extern void func_00283958(char *a, char *b);
extern float D_L00_001A8DD0 __attribute__((sda));

void func_PAL_00288638(float *arg0) { char temp[0x40]; float value = *arg0 * 0.0003490659f * D_L00_001A8DD0; func_002ACE78(temp, D_L00_001B8FF0, value); func_00283958(temp, temp + 0x10); func_00283738(D_L00_001B8FF0, temp + 0x10, D_L00_001B8FF0); }
