#include "include_asm.h"


#include "common.h"
extern float math_fast_sin_or_cos_b(float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);
extern f32 math_random_float_range(f32 a, f32 b);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int g_gorn_group_count[] __attribute__((sda));
extern unsigned short **g_gorn_group_paths[] __attribute__((sda));
extern unsigned char *g_gorn_group_record_base[] __attribute__((sda));
extern unsigned char *g_gorn_aim_record_base[] __attribute__((sda));
extern short g_gorn_group_class_table[];
extern float vec_distance_xy(void *, void *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_b(float);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void BuildObjectAttachmentTransforms(void *, void *, int, int, int, int, int, int);
extern void level_set_record_payload_by_key(void *, int, int, void *);
extern void moby_update_attached_transforms(void *, void *);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
void gorn_group_aim_update_pal(unsigned char *a0)
{
    unsigned char *state = *(unsigned char **)(a0 + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *e;
    int i;
    int best;
    short cls;
    float bestd;
    float d;
    float f2;

    switch (a0[0x20]) {
    case 0:
        best = -1;
        bestd = 9999.0f;
        for (i = 0; i < g_gorn_group_count[0]; i++) {
            for (p = g_gorn_group_paths[0][i];
                 p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_gorn_group_paths[0][i]);
                 p++) {
                e = g_gorn_group_record_base[0] + ((*p & 0x7FFF) << 6);
                if (e == 0)
                    break;
                d = vec_distance_xy(e + 0x30, a0 + 0x10);
                if (d < bestd) {
                    bestd = d;
                    best = i;
                }
            }
        }
        *(int *)state = best;
        if (best == -1)
            return;
        *(float *)(state + 0x28) = 12.0f;
        *(float *)(state + 0x2C) = math_random_float_range(30.0f, 37.0f);
        *(float *)(state + 0x1C) = math_random_angle();
        *(float *)(state + 0xC) = math_fast_sin_or_cos_b(*(float *)(state + 0x1C)) * *(float *)(state + 0x28);
        math_update_wrapped_angle_offset(a0, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        a0[0x30] = 0xFF;
        BuildObjectAttachmentTransforms(a0, state + 0x40, 20, *(int *)(state + 4), *(int *)state,
                          *(int *)(state + 8), 7, 0);
        if (state[0x8A] == 0) {
            moby_mark_spawned(a0);
            return;
        }
        for (q = g_gorn_group_paths[0][*(int *)state];
             q != 0 && ((q != 0 && (short)q[-1] >= 0) || q == g_gorn_group_paths[0][*(int *)state]);
             q++) {
            e = g_gorn_aim_record_base[0] + ((*q & 0x7FFF) << 5);
            if (e == 0)
                break;
            cls = g_gorn_group_class_table[e[0x1D]];
            if (cls == 0xD34)
                level_set_record_payload_by_key(state + 0x40, 1, (short)*q, state + 0x680);
            if (cls == 0xD33)
                level_set_record_payload_by_key(state + 0x40, 1, (short)*q, state + 0x6A0);
        }
        state[0x8D] = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x104;
        euler_rotation_basis(a0 + 0xC0, a0 + 0xF0);
        *(float *)(state + 0x38) = math_random_signed_float_range(27.0f, 52.0f) * 0.0003490659f;
        f2 = math_random_signed_float_range(25.0f, 37.0f) * 0.0003490659f;
        *(float *)(state + 0x3C) = f2;
        if (0.0f <= *(float *)(state + 0x38) * f2)
            *(float *)(state + 0x3C) = -f2;
        a0[0x20] = 1;
        break;
    case 1:
        math_update_wrapped_angle_offset(a0, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        *(float *)(state + 0x688) = FastAddRotations(*(float *)(state + 0x688), *(float *)(state + 0x38));
        *(float *)(state + 0x6A8) = FastAddRotations(*(float *)(state + 0x6A8), *(float *)(state + 0x3C));
        moby_update_attached_transforms(a0, state + 0x40);
        break;
    }
}

