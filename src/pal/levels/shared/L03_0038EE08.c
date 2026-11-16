#include "include_asm.h"
#include "names.h"


extern unsigned char g_hero_l03_state_block[];
extern float func_2EF158(void *, void *);
extern void func_2B8300(int, int, void *);

/* Fires a trigger on the object when the hero is standing close to it. */
void moby_trigger_when_hero_near_pal(unsigned char *object) {
    unsigned char *hero = g_hero_l03_state_block;

    if (*(unsigned char *)(hero + 0x22B4) == 0)
        if (func_2EF158(hero + 0x80, object + 0x10) < 1.7f)
            func_2B8300(1, 0x3F, object);
}

