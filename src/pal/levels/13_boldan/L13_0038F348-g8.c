#include "include_asm.h"

#include "common.h"
extern f32 D_L13_001AEBF0 __attribute__((sda));
extern f32 D_L13_001AEBD0 __attribute__((sda));
extern f32 D_L13_001AEBC8 __attribute__((sda));
extern f32 D_L13_001AEBC0 __attribute__((sda));
extern f32 D_L13_001AEBF4 __attribute__((nosda));
extern f32 D_L13_001AEBF8 __attribute__((nosda));
extern void *part_find_owned_effect_slot(u8 *, s32, s32);
extern void moby_set_state(u8 *, s32, s32);
extern void moby_mark_spawned(u8 *);
extern void *part_spawn_object_following_effect(float, float, void *, u8 *, s32, s32, s32, s32, s32, s32);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(u8 *, f32 *, f32, f32, f32);
extern char *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                        float, float);

void func_PAL_L13_0038F348(u8 *a0) {
    s32 *s1 = *(s32 **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        part_spawn_object_following_effect(210000.0f, 0.75f, &D_L13_001AEBF0, a0, 0x50204040, -1, 1, -1, 0, -1);
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) != 0 && *s1 == 0)
            moby_set_state(a0, 2, -1);
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        f32 buf[4];
        func_PAL_L00_0032C328(a0, &D_L13_001AEBD0, &D_L13_001AEBC8, &D_L13_001AEBC0,
                    0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        {
            f32 first = D_L13_001AEBF8;
            f32 x = D_L13_001AEBF0;
            f32 second = D_L13_001AEBF4;
            moby_compute_local_point(a0, buf, x, second, first);
        }
        func_PAL_L00_003FB330(buf, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0, 0.3f, 20.0f);
        moby_mark_spawned(a0);
        break;
    }
    }
}
