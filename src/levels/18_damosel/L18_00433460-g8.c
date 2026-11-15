#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern u16 D_L18_001B18FC __attribute__((sda));

extern float D_L18_001B191C __attribute__((sda));

extern void *CreateMoby(short a);

extern float mat_fast_helper_a(float a, float b);

extern void func_002A0F48(void *a);

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

/* A breakable object: it waits to be hit, then releases a burst of items and an explosion and disappears. */
void breakable_item_update(u8 *moby) {
    s32 state = moby[0x20];
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 one = 1;
    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) != 0 && *(s32 *)vars == 0) {
            moby_set_state(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        s32 mask = 0xFFFF;
        part_explode_object_into_pieces(moby, &D_L18_001B1D40, &D_L18_001B1D38,
                          &D_L18_001B1D30, 0xFFFF, 0, -1, 0, mask, 0xFF, 0);
        SpawnExplosion(moby + 0x10, 0, 5, 5, 5, 5, 5, 0,
                      *(float *)(moby + 0x2C) * 10.0f, 20.0f, one, 0, one, 0);
        moby_mark_spawned(moby);
        break;
    }
    }
}
