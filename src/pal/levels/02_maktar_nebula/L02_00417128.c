#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void moby_set_state();
extern float math_fast_sin_or_cos_b(float);
extern char D_L02_00188660[];
extern void snd_stop_voice(int);
extern int math_random_int_below(int);
extern float fast_vec_dist(void *, void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern char g_camera_l02_position[];
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);
extern void moby_mark_spawned(u8 *);
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_0019B2E8[];
extern u16 D_0018CFDC;
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern float ApproachValue(float *, float, float);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float FastAddRotations(float, float);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void func_PAL_L02_00417490(u8 *);
extern void func_PAL_L02_004176A8(u8 *);
extern int math_random_int_below(int);
extern s32 g_hovering_object_count __attribute__((sda));
extern void gfx_add_draw_callback_first(void *, void *);
extern u8 D_0019B4A8[];
extern int g_current_map_index __attribute__((sda));
extern int PlayMobySound(int, int, void *);

/* Steps the actor by its kind byte (+0x20). Kind 0 releases it (func_0029F338) when the table byte
   of its owner (D_0019B2E8, indexed by the byte at +0xB0 and D_001A79F0) has bit 7 set; otherwise
   it takes twice the size at +0x24 of its type record, sets or clears bit 15 of its flags at +0x34
   by func_002A77E0(2), starts state 1 and draws the block's two phases (+4 and +0x14) with
   func_002A7940. Kind 1 keeps its slot record (the index at +0x18 of the block) alive, eases the
   block's float at +0xC to 0 or 1 by whether func_00282E80 puts the actor farther than 64.0 from
   D_L02_001BA500, registers func_PAL_L02_004176A8 while it is nonzero, and when the entity found by
   func_002A9640 (a record whose halfword at +0xAA is 0x9C8) is within 5.0 starts state 2 and gives
   the slot up. Kind 2 only runs the common tail, which steps the two phases (func_00283B98), puts
   0.5 * sin(phase) + the base at +8 into the actor's float at +0x18 and runs the counter at +0x10
   down by 1/15, wrapping it into [-1, 1]. The first slot lookup is a separate block-local pointer
   from the one in the state-2 arm (retail keeps them in different registers). */
void func_PAL_L02_00417128(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *p;
    u8 *q;
    s32 slot;
    float f;

    switch (a0[0x20]) {
    case 0:
        if (D_0019B2E8[a0[0xB0] + g_current_map_index * 16] & 0x80) {
            moby_mark_spawned(a0);
            return;
        }
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 2.0f;
        if (math_random_int_below(2))
            *(u16 *)(a0 + 0x34) |= 0x8000;
        else
            *(u16 *)(a0 + 0x34) &= 0x7FFF;
        moby_set_state(a0, 1, -1);
        *(float *)(s1 + 8) = *(float *)(a0 + 0x18);
        *(float *)(s1 + 4) = math_random_angle();
        *(float *)(s1 + 0x14) = math_random_angle();
        break;
    case 1:
        if (a0[0x31] != 0)
            func_PAL_L02_00417490(a0);
        {
            u8 *r = (u8 *)D_L02_00188660 + *(s32 *)(s1 + 0x18) * 0x70;

            if (*(u8 **)(r + 0x88) != a0 || r[0x74] == 0)
                *(s32 *)(s1 + 0x18) = PlayMobySound(0, 4, a0);
        }
        f = vec_distance_xy(a0 + 0x10, g_camera_l02_position);
        if (f > 64.0f)
            ApproachValue((float *)(s1 + 0xC), 0.0f, 0.020000001f);
        else
            ApproachValue((float *)(s1 + 0xC), 1.0f, 0.020000001f);
        if (*(float *)(s1 + 0xC) != 0.0f)
            gfx_add_draw_callback_first((void *)func_PAL_L02_004176A8, a0);
        p = part_find_owned_effect_slot(a0, 0x10000, 0);
        if (p != 0) {
            q = *(u8 **)(p + 0x20);
            if (q != 0 && *(s16 *)(q + 0xAA) == 0x9C8 &&
                fast_vec_dist(a0 + 0x10, q + 0x10) < 5.0f) {
                D_0018CFDC = 0xFFFF;
                moby_set_state(a0, 2, -1);
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
                *(u32 *)(a0 + 0x98) = 0;
                slot = *(s32 *)(s1 + 0x18);
                if (slot != -1) {
                    u8 *rec = (u8 *)D_L02_00188660 + slot * 0x70;

                    if (*(u8 **)(rec + 0x88) == a0 && rec[0x74] != 0)
                        snd_stop_voice(slot);
                }
                *(s32 *)(s1 + 0x18) = -1;
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        break;
    }
    *(float *)(s1 + 4) = FastAddRotations(*(float *)(s1 + 4), 0.06981318f);
    *(float *)(s1 + 0x14) = FastAddRotations(*(float *)(s1 + 0x14), -0.12566373f);
    *(float *)(a0 + 0x18) = math_fast_sin_or_cos_b(*(float *)(s1 + 4)) * 0.5f + *(float *)(s1 + 8);
    f = *(float *)(s1 + 0x10) + -0.080000006f;
    *(float *)(s1 + 0x10) = f;
    if (f > 1.0f)
        *(float *)(s1 + 0x10) = f - 1.0f;
    else if (f < -1.0f)
        *(float *)(s1 + 0x10) = f + 1.0f;
}

