#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F449178;
extern s32 D_L20_001B23A0 __attribute__((sda));
extern s32 D_L20_001B23A8 __attribute__((sda));
extern s32 D_L20_001B23B0 __attribute__((sda));
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern void *part_spawn_object_following_effect(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern void func_PAL_L00_0032C328(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(char *, void *, float, float, float);
extern char *func_PAL_L00_003FB330(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern char *moby_l00_spawn_child(char *, s32, s32);
extern void moby_mark_spawned(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then plays the burst and retires. */
void func_PAL_L20_0044EDF0(char *obj)
{
    V4_F449178 v;
    s32 *rec = *(s32 **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        v.q = 0;
        v.f[2] = 2.0f;
        part_spawn_object_following_effect(&v, obj, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x04010000, 0) != 0 && *rec == 0)
            moby_set_state(obj, 2, -1);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        func_PAL_L00_0032C328(obj, &D_L20_001B23B0, &D_L20_001B23A8, &D_L20_001B23A0, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_compute_local_point(obj, &v, 0.0f, 0.0f, 2.0f);
        func_PAL_L00_003FB330(&v, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        moby_l00_spawn_child(obj, 0x126A, 0);
        moby_mark_spawned(obj);
        return;
    }
}
