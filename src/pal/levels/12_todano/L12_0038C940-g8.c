#include "include_asm.h"
#include "names.h"

typedef int Quadword89F80 __attribute__((mode(TI)));
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_set_state(void *, int, int);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int moby_is_state_two(char *);
extern char *ref_L12_00389F80_00 __attribute__((sda));
extern char *ref_L12_00389F80_01;
extern float ref_L12_00389F80_02 __attribute__((sda));
extern float ref_L12_00389F80_03 __attribute__((sda));

/* Per-state step of a homing object: state 0 starts it, state 1 steers it by the thing it
   follows (or just turns it) and then spins a short delay loop. */
void homing_follower_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float to_target[4];
    float forward[4];
    float side_vel[4];
    float dot;
    int i;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned int *)(vars + 0x5C) |= 4;
        *(short *)(moby + 0x7C) = 3;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0xE0) == -1 ||
            moby_is_state_two(ref_L12_00389F80_00 + (*(int *)(vars + 0xE0) << 8)) == 0) {
            vec_scale_to_length(vars + 0x30, moby + 0xD0, -(ref_L12_00389F80_02 * 0.020000001f));
            *(float *)(moby + 0x48) = ref_L12_00389F80_03;
        } else {
            moby_transform_point_and_rotation_by_parent(moby, ref_L12_00389F80_01 + (*(int *)(vars + 0xE0) << 8), moby + 0x10,
                          moby + 0xF0, to_target, forward);
            to_target[2] = 0.0f;
            FastVecSub(side_vel, to_target, moby + 0x10);
            *(Quadword89F80 *)to_target = *(Quadword89F80 *)side_vel;
            to_target[2] = 0.0f;
            forward[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8) + 4.7123895f);
            forward[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8) + 4.7123895f);
            forward[2] = 0.0f;
            dot = FastVecDot(to_target, forward);
            side_vel[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * dot * 0.1f;
            side_vel[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * dot * 0.1f;
            side_vel[2] = 0.0f;
            mat_combine_and_store(vars + 0x20, side_vel, moby + 0xF0, moby + 0xF0);
            *(float *)(moby + 0x48) = dot * 49.999996f;
        }
        i = 6;
        while (--i >= 0)
            ;
        break;
    }
}
