#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef int s32;
extern int moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern void moby_mark_spawned(void *);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32,
                              s32, s32, s32);
extern void SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, s32);
extern float D_L18_001B1D30 __attribute__((sda));
extern float D_L18_001B1D38 __attribute__((sda));
extern float D_L18_001B1D40 __attribute__((sda));

void func_PAL_L18_004467F8(u8 *s0) {
    s32 state = s0[0x20];
    u8 *s1 = *(u8 **)(s0 + 0x68);
    s32 one = 1;
    switch (state) {
    case 0:
        moby_set_state(s0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(s0, 0x04010000, 0) != 0 && *(s32 *)s1 == 0) {
            moby_set_state(s0, 2, -1);
        }
        s0[0xA8] = 0xFF;
        break;
    case 2: {
        s32 v = 0xFFFF;
        part_explode_object_into_pieces(s0, &D_L18_001B1D40, &D_L18_001B1D38,
                          &D_L18_001B1D30, 0xFFFF, 0, -1, 0, v, 0xFF, 0);
        SpawnExplosion(s0 + 0x10, 0, 5, 5, 5, 5, 5, 0,
                      *(float *)(s0 + 0x2C) * 10.0f, 20.0f, one, 0, one, 0);
        moby_mark_spawned(s0);
        break;
    }
    }
}
