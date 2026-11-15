#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;

/* multiplies the index by 20 and adds it to a base; byte-identical across all 27 levels. */
char *func_PAL_00344418(u8 *a0) { return *(s32 *)(a0 + 0x260) + *(s32 *)(a0 + 0x16C) * 20; }

