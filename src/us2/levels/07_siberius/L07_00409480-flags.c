#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, s32, s32);
extern u8 *part_find_owned_effect_slot(void *, s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void PlayMobySound(s32, s32, void *);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void part_l07_spawn_spark_burst(void *);
extern void snd_play_from_global_bank(s32, s32, s32);
extern void func_US2_002B1880(s32, s32);
extern s32 math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern u8 D_L07_001B1540[16] __attribute__((sda));
extern u8 D_L07_001B1538[8] __attribute__((sda));
extern u8 D_L07_001B1530[8] __attribute__((sda));
extern s32 D_L07_001B1560 __attribute__((sda));
extern u8 D_001A7A70 __attribute__((nosda));
extern u8 D_001A7A70_read[] __asm__("D_001A7A70") __attribute__((sda));
extern s32 D_L07_001A903C[] __attribute__((sda));
extern f32 D_L07_001B3198 __attribute__((sda));
extern f32 D_L07_001AA698 __attribute__((sda));

void func_US2_L07_00409480(u8 *obj)
{
    f32 a[4], b[4];
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *hit;
    s32 blocked;
    switch (obj[0x20]) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (!*(s32 *)state) {
            hit = part_find_owned_effect_slot(obj, 0x4010000, 0);
            if (hit) {
                qcopy(a, obj + 0x10);
                a[2] += 0.5f;
                blocked = 1;
                if (*(u8 **)(hit + 0x20)) {
                    qcopy(b, *(u8 **)(hit + 0x20) + 0x10);
                    b[2] += 0.5f;
                    if (fast_vec_dist(b, a) < 64.0f) {
                        blocked = 0;
                        if (!CollLine(b, a, 2, obj, 0)) blocked = 1;
                    }
                }
                if (blocked) moby_set_state(obj, 2, -1);
            }
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, obj);
        part_explode_object_into_pieces(obj, D_L07_001B1540, D_L07_001B1538, D_L07_001B1530, 0xFFF, -1, D_L07_001B1560, 16, 0xFFFF, 0xFF, 0);
        part_l07_spawn_spark_burst(obj);
        *(s32 *)(state + 4) = 480;
        if (!D_001A7A70_read[0]) {
            D_001A7A70 = 1;
            snd_play_from_global_bank(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L07_001A903C[0] = 1;
        }
        if (D_L07_001B1560 >= 0) *(u16 *)(obj + 0x7C) = (1 << D_L07_001B1560) | 0x8000;
        else *(u16 *)(obj + 0x34) |= 0x41;
        moby_set_state(obj, 3, -1);
        break;
    case 3:
        if (math_fast_float_d(state + 4)) {
            D_L07_001AA698 = D_L07_001B3198;
            moby_mark_spawned(obj);
        }
        break;
    }
}
