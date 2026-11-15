#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

void func_PAL_0028E7B8(char *object) { extern void hud_init_counter_values(u8 *); *(int *)(object + 0x58) = 0x20; *(int *)(object + 0x7C) = 0x82; *(int *)(object + 0x5C) = 0x20; hud_init_counter_values((u8 *)object); }

