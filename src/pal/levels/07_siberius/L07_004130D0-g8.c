#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 fast_vec_dist(void *a, void *b);
extern void ship_build_joint_pointers(u8 *a);
extern void group_walk_entities(u8 *a);
extern void boss_place_attached_parts(u8 *a);
extern u8 *D_L07_001FDEC0[];
extern u16 *g_moby_l07_group_lists[];
extern f32 D_L07_001B1700 __attribute__((sda));
extern f32 D_L07_001B1704 __attribute__((sda));
extern f32 D_L07_001B1770[5] SDATA(D_L07_001B1770);
extern s32 D_L07_001B22F8;
extern u8 *g_moby_l07_array[] __attribute__((sda));
typedef struct {
    u8 pad[0xE0];
    f32 times[5];
    u8 *ents[5];
} SiberiusChain;

/* Starts the chain of the object's group: the rates at +0x1A0/+0x1A4 from 1 / the length of
   record D_L07_001FDEC0[state + 0x90] (its points at +0x10 and +0x20), then for i = 1 to 4 every
   entity of the group whose class is 0x11D9 + i: shown, scaled like the object, its time
   accumulated from D_L07_001B1770, stored as member i and set up. */
void func_PAL_L07_004138B8(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *base;
    f32 inv, slow, fast;
    f32 scale;
    s32 i;
    u16 *p;
    u8 *e;
    u8 *es;

    base = D_L07_001FDEC0[*(s32 *)(state + 0x90)];
    inv = 1.0f / fast_vec_dist(base + 0x10, base + 0x20);
    fast = inv * 0.020000001f * D_L07_001B1700;
    slow = inv * 0.00040000002f * D_L07_001B1704;
    *(s32 *)(state + 0x11C) = 0;
    *(u8 **)(state + 0xF4) = a0;
    *(s32 *)(state + 0x5C) |= 2;
    *(s32 *)(state + 0xE0) = 0;
    *(f32 *)(state + 0x1A4) = slow;
    *(f32 *)(state + 0x1A0) = fast;
    *(TI128 *)(state + 0x40) = *(TI128 *)(a0 + 0xF0);
    ship_build_joint_pointers(a0);
    *(u16 *)(a0 + 0x34) |= 1;
    a0[0x31] = 0;
    scale = *(f32 *)(a0 + 0x2C) / *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24);
    if (a0[0x21] != 0xFF) {
        for (i = 1; i < 5; i++) {
            for (p = g_moby_l07_group_lists[a0[0x21]];
                 a0[0x21] != 0xFF && a0[0x21] <= D_L07_001B22F8 && p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == g_moby_l07_group_lists[a0[0x21]]);
                 p++) {
                e = g_moby_l07_array[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(s16 *)(e + 0xAA) == i + 0x11D9) {
                    *(u16 *)(e + 0x34) |= 1;
                    e[0x31] = 0;
                    *(f32 *)(e + 0x2C) = *(f32 *)(*(u8 **)(e + 0x24) + 0x24) * scale;
                    es = *(u8 **)(e + 0x68);
                    *(u16 *)(e + 0x34) |= 0x22;
                    *(u8 **)(es + 8) = es + 0x20;
                    *(s32 *)(es + 0x5C) = 2;
                    *(TI128 *)(es + 0x40) = *(TI128 *)(e + 0xF0);
                    ((SiberiusChain *)state)->times[i] =
                        ((SiberiusChain *)state)->times[i - 1] + D_L07_001B1770[i];
                    ((SiberiusChain *)state)->ents[i] = e;
                    group_walk_entities(e);
                    boss_place_attached_parts(e);
                    ship_build_joint_pointers(e);
                }
            }
        }
    }
}
