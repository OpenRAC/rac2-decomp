#include "include_asm.h"
#include "names.h"

extern void moby_set_state(char *a0, int a1, int a2);
extern int part_find_owned_effect_slot(char *a0, int a1, int a2);
extern void func_PAL_L00_003281C0(char *a0, int a1, float f12);
extern void PlayMobySound(int a0, int a1, char *a2);
extern void debris_spawn_ring(char *a0, int a1, float f12, float f13, float f14, float f15);
extern void moby_mark_spawned(char *a0);

void func_PAL_L04_0045C388(char *s0)
{
    char *s1 = *(char **)(s0 + 0x68);

    switch (*(unsigned char *)(s0 + 0x20)) {
    case 0:
        moby_set_state(s0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(s0, 0x4010000, 0) != 0 && *(int *)s1 == 0)
            moby_set_state(s0, 2, -1);
        *(unsigned char *)(s0 + 0xA8) = 0xFF;
        break;
    case 2:
        func_PAL_L00_003281C0(s0, 1, 0.0f);
        PlayMobySound(0, 0, s0);
        debris_spawn_ring(s0, 0x1E, 0.4f, 4.4f, 1.0f, 0.10000001f);
        moby_mark_spawned(s0);
        break;
    }
}

