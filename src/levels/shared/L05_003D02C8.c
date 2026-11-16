#include "include_asm.h"
#include "names.h"

extern int g_spawn_list_table[];
#include "common.h"
extern int g_feltzin_target_mobys MACRO_ADDR;

/* Sets the active flag on every object listed in the object's link list. */
void func_L05_003D02C8(char *obj)
{
    int base = g_spawn_list_table[(unsigned char)obj[0x21]];
    unsigned short *p;

    if (base == 0)
        return;
    p = (unsigned short *)base;
    do {
        int tbl = g_feltzin_target_mobys;

        *(char *)(tbl + ((int)*p & 0x7FFF) * 256 + 0x20) = 1;
    } while (*(short *)p++ >= 0);
}
