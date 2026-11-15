#include "include_asm.h"

#include "common.h"
extern int D_L20_001A8F00;
extern struct {
    u8 reserved[0x2D8];
    float height;
} D_00189E20;
extern struct {
    u8 reserved[0x158];
    float yaw;
} D_L20_001B9E80;
extern u32 D_L20_001B2AC8;
extern float D_L20_001B2420 __attribute__((sda));
extern float D_L20_001B2430[4] SDATA(D_L20_001B2430);
extern void moby_mark_spawned(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float ApproachValue(float *, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_L20_004502D0(char *);
extern int flag_set_first_pending(u8 *);
extern int PlayMobySound(int, int, char *);
extern float func_PAL_L20_00450568(char *);
extern void moby_set_state(u8 *, int, int);
extern void func_PAL_002A7E68(u8 *, int, int, int);
extern u8 *FindLastGroupMemberInRange(u8 *, u8 *);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float coll_probe_ground_height_below(void *, int, float);
extern char *func_PAL_L20_0039F488(u8 *, void *, void *, float);
extern void func_PAL_L20_004504B0(char *);

/* Alternates between target selection and directed projectile bursts. */
void func_PAL_L20_0044FE40(u8 *moby)
{
    float target[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *selected;
    float *aim;
    float angle, radius, savedHeight, x;
    func_PAL_L20_004502D0((char *)moby);
    if (D_L20_001A8F00 == 2) { moby_mark_spawned(moby); return; }
    switch (moby[0x20]) {
    case 2:
        if (flag_set_first_pending(moby)) *(int *)(state + 0x1b8) = PlayMobySound(0, 4, (char *)moby);
        *(int *)(*(u8 **)(moby + 0xb8) + 0x98) = 0;
        if (func_PAL_L20_00450568((char *)moby) < 0.1f) moby_set_state(moby, 3, -1);
        *(int *)(*(u8 **)(moby + 0xb8) + 0x98) = *(int *)(*(u8 **)(*(u8 **)(moby + 0xb8) + 0x24) + 0x10);
        break;
    case 3:
        if (*(unsigned short *)(moby + 0x96) > 50) moby_set_state(moby, 4, -1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 12);
            selected = FindLastGroupMemberInRange(*(u8 **)(moby + 0xb8), moby);
            *(u8 **)(state + 0x1b0) = selected;
            if (math_random_int_below(2)) *(u8 **)(state + 0x1b0) = 0;
            selected = *(u8 **)(state + 0x1b0);
            aim = (float *)(state + 0x140);
            if (selected) {
                *(u8 **)(state + 0x150) = selected;
                qcopy(aim, selected + 0x10);
            }
            angle = FastAddRotations(D_L20_001B9E80.yaw, math_random_signed_float_range(20.0f, 70.0f) * 0.017453294f);
            radius = math_random_float_range(5.0f, 15.0f);
            savedHeight = *(float *)(state + 0x198);
            *(float *)(state + 0x190) = math_fast_sin_or_cos_a(angle) * radius;
            *(float *)(state + 0x194) = math_fast_sin_or_cos_b(angle) * radius;
            *(float *)(state + 0x198) = 0.0f;
            FastVecAdd(state + 0x190, state + 0x190, aim);
            if (g_hero_state.height != 0.0f) {
                g_hero_state.height += math_random_float_range(1.5f, 2.5f);
                *(float *)(state + 0x198) = g_hero_state.height;
            } else *(float *)(state + 0x198) = savedHeight;
        }
        if (func_PAL_L20_00450568((char *)moby) < 0.1f) moby_set_state(moby, 5, -1);
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != 1) func_PAL_002A7E68(moby, 1, 0, 12);
            if (*(int *)(state + 0x1b0)) *(float *)(state + 0x1b4) = 0.0f;
            else *(float *)(state + 0x1b4) = -math_random_float_range(4.0f, 6.0f);
            PlayMobySound(1, 0, (char *)moby);
        }
        if ((D_L20_001B2AC8 & 15) == (((int)moby >> 8) & 15)) {
            FastVecSub(target, state + 0x140, moby + 0x10);
            target[2] = 0.0f;
            x = vec_length_xy(target) + *(float *)(state + 0x1b4);
            if (x < 1.0f) x = 1.0f;
            vec_fast_normalize_helper(target, target, x);
            FastVecAdd(target, target, moby + 0x10);
            target[2] = coll_probe_ground_height_below(target, 0, 0.5f);
            if (target[2] == 0.0f) target[2] = *(float *)(state + 0x148);
            matrix_mul_vec3(origin, D_L20_001B2430, moby + 0xc0);
            FastVecAdd(origin, origin, moby + 0x10);
            FastVecSub(velocity, target, origin);
            vec_scale_to_length(velocity, velocity, D_L20_001B2420 * 0.020000001f);
            func_PAL_L20_0039F488(moby, origin, velocity, (float)state[0x34]);
            ApproachValue((float *)(state + 0x1b4), 4.0f, 1.0f);
        }
        if (*(float *)(state + 0x1b4) >= 4.0f) moby_set_state(moby, 4, -1);
        break;
    }
    func_PAL_L20_004504B0((char *)moby);
}
