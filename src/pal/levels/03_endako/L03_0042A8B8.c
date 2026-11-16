#include "include_asm.h"

#include "common.h"
extern s32 g_object_group_count[] __attribute__((sda));
extern u8 *g_moby_record_base[] __attribute__((sda));
extern u16 *g_entity_id_lists[];
extern void moby_mark_spawned(void *);
extern float math_fast_float_g(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern s32 FastTweenColor(s32, s32, float);
#define GROUP (*(s32 *)state)

/* State 0 checks the group word of the state block (a group that is out of range, empty or -1
   removes the object); otherwise it sets the step to -3 degrees, turns the +8 word from degrees
   to radians, gives every entity of the group the flag 0x10 and a fresh state block (colour
   words 0x80A0A0A0 and 0x80000000, the angle func_00283C28 wraps from 30 degrees times its
   first word) and moves on to state 1. State 1 advances each entity's angle by the step and
   tints the entity with the two colours blended by the sine of that angle. Both walks keep the
   second `p != 0` guard before the `p[-1]` read. Retail's step is 0xBD567752: the literal
   0.05235988f encodes one ulp less, and the stores of the fresh state block and of the entity's
   flags go in the order below, which is the order retail has them in. */
void func_PAL_L03_0042A8B8(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u16 *p;
    u8 *e;
    u8 *s0;

    switch (a0[0x20]) {
    case 0:
        if (GROUP >= g_object_group_count[0] || g_entity_id_lists[GROUP] == 0 || GROUP == -1) {
            moby_mark_spawned(a0);
        } else {
            *(f32 *)(state + 4) = -0.062831864f;
            *(f32 *)(state + 8) = *(f32 *)(state + 8) * 0.017453294f;
            a0[0x30] = 0xFF;
            for (p = g_entity_id_lists[GROUP];
                 (GROUP & 0xFF) != 0xFF && GROUP <= g_object_group_count[0] && p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == g_entity_id_lists[GROUP]);
                 p++) {
                e = g_moby_record_base[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                *(u16 *)(e + 0x34) |= 0x10;
                s0 = *(u8 **)(e + 0x68);
                *(s32 *)(s0 + 4) = 0x80A0A0A0;
                *(s32 *)(s0 + 8) = 0x80000000;
                *(f32 *)(s0 + 0xC) = math_fast_float_g((f32)(*(s32 *)s0 * 30) * 0.017453294f);
                *(u16 *)(e + 0x32) = 0x1FF;
                e[0x30] = 0xFF;
            }
            a0[0x20] = 1;
        }
        break;
    case 1:
        for (p = g_entity_id_lists[GROUP];
             (GROUP & 0xFF) != 0xFF && GROUP <= g_object_group_count[0] && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == g_entity_id_lists[GROUP]);
             p++) {
            e = g_moby_record_base[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            s0 = *(u8 **)(e + 0x68);
            *(f32 *)(s0 + 0xC) = FastAddRotations(*(f32 *)(s0 + 0xC), *(f32 *)(state + 4));
            *(s32 *)(e + 0x78) =
                FastTweenColor(*(s32 *)(s0 + 4), *(s32 *)(s0 + 8),
                              math_fast_sin_or_cos_b(*(f32 *)(s0 + 0xC)) * 0.5f + 0.5f);
        }
        break;
    }
}

