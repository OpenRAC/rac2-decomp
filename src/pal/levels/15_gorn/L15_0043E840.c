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
void gorn_group_aim_update_pal(unsigned char *moby)
{
    unsigned char *state = *(unsigned char **)(moby + 0x68);
    unsigned short *group_ptr;
    unsigned short *record_ptr;
    unsigned char *record;
    int i;
    int best_group;
    short record_class;
    float best_dist;
    float dist;
    float spin_b;

    switch (moby[0x20]) {
    case 0:
        best_group = -1;
        best_dist = 9999.0f;
        for (i = 0; i < g_gorn_group_count[0]; i++) {
            for (group_ptr = g_gorn_group_paths[0][i];
                 group_ptr != 0 && ((group_ptr != 0 && (short)group_ptr[-1] >= 0) || group_ptr == g_gorn_group_paths[0][i]);
                 group_ptr++) {
                record = g_gorn_group_record_base[0] + ((*group_ptr & 0x7FFF) << 6);
                if (record == 0)
                    break;
                dist = vec_distance_xy(record + 0x30, moby + 0x10);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_group = i;
                }
            }
        }
        *(int *)state = best_group;
        if (best_group == -1)
            return;
        *(float *)(state + 0x28) = 12.0f;
        *(float *)(state + 0x2C) = math_random_float_range(30.0f, 37.0f);
        *(float *)(state + 0x1C) = math_random_angle();
        *(float *)(state + 0xC) = math_fast_sin_or_cos_b(*(float *)(state + 0x1C)) * *(float *)(state + 0x28);
        math_update_wrapped_angle_offset(moby, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        moby[0x30] = 0xFF;
        BuildObjectAttachmentTransforms(moby, state + 0x40, 20, *(int *)(state + 4), *(int *)state,
                          *(int *)(state + 8), 7, 0);
        if (state[0x8A] == 0) {
            moby_mark_spawned(moby);
            return;
        }
        for (record_ptr = g_gorn_group_paths[0][*(int *)state];
             record_ptr != 0 && ((record_ptr != 0 && (short)record_ptr[-1] >= 0) || record_ptr == g_gorn_group_paths[0][*(int *)state]);
             record_ptr++) {
            record = g_gorn_aim_record_base[0] + ((*record_ptr & 0x7FFF) << 5);
            if (record == 0)
                break;
            record_class = g_gorn_group_class_table[record[0x1D]];
            if (record_class == 0xD34)
                level_set_record_payload_by_key(state + 0x40, 1, (short)*record_ptr, state + 0x680);
            if (record_class == 0xD33)
                level_set_record_payload_by_key(state + 0x40, 1, (short)*record_ptr, state + 0x6A0);
        }
        state[0x8D] = 1;
        *(unsigned short *)(moby + 0x34) |= 0x104;
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        *(float *)(state + 0x38) = math_random_signed_float_range(27.0f, 52.0f) * 0.0003490659f;
        spin_b = math_random_signed_float_range(25.0f, 37.0f) * 0.0003490659f;
        *(float *)(state + 0x3C) = spin_b;
        if (0.0f <= *(float *)(state + 0x38) * spin_b)
            *(float *)(state + 0x3C) = -spin_b;
        moby[0x20] = 1;
        break;
    case 1:
        math_update_wrapped_angle_offset(moby, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        *(float *)(state + 0x688) = FastAddRotations(*(float *)(state + 0x688), *(float *)(state + 0x38));
        *(float *)(state + 0x6A8) = FastAddRotations(*(float *)(state + 0x6A8), *(float *)(state + 0x3C));
        moby_update_attached_transforms(moby, state + 0x40);
        break;
    }
}

