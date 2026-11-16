#include "include_asm.h"
#include "names.h"


extern unsigned char g_hero_l03_state_block[];
extern float func_2EF158(void *, void *);
extern void func_2B8300(int, int, void *);

void moby_trigger_when_hero_near_pal(unsigned char *a0) {
    unsigned char *g = g_hero_l03_state_block;

    if (*(unsigned char *)(g + 0x22B4) == 0)
        if (func_2EF158(g + 0x80, a0 + 0x10) < 1.7f)
            func_2B8300(1, 0x3F, a0);
}

