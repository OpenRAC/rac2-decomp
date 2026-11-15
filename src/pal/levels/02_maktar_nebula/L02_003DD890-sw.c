#include "include_asm.h"
#include "names.h"

extern int g_moby_l02_pool;
extern int D_L02_001B03F0 __attribute__((sda));
typedef struct { char pad[0x160]; float amount; int pad2; int time; int phase; } Shake;
extern Shake D_L02_001BA3C0;
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int func_PAL_002B5E30(char *, float);
extern float vec_step_toward_target_limited(void *, void *, float);
extern int arena_get_state_word(void *);
extern float *arena_get_camera_point(void *);
extern int coll_point_inside_record_volume(void *, void *);
extern int func_PAL_L01_00323068(char *, void *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void euler_rotation_basis(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int moby_start_effect_from_entry(char *, float);
extern float math_fast_float_g(float);
extern void turret_spawn_beam_hits(char *);
extern float ApproachValue(float *, float, float);

void func_PAL_L02_003DD890(char *self) {
    float before[4];
    float after[4];
    float delta[4];
    char *state = *(char **)(self + 0x68);
    float *target = (float *)(state + 0x230);
    float distance = vec_distance_xy(self + 0x10, target);
    float heading = mat_fast_helper_a(target[0] - *(float *)(self + 0x10), target[1] - *(float *)(self + 0x14));
    float frame = moby_get_anim_value(self);
    char *part = (char *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + g_moby_l02_pool);
    int saved = *(int *)(part + 0x98);
    unsigned int mode;
    float speed;
    *(int *)(part + 0x98) = 0;
    moby_set_controller_speed_limits(self, 0.0024f, 0.062000003f, 0.005026549f, 0.12566373f);
    mode = *(unsigned char *)(self + 0x42);
    switch (mode) {
    case 0:
    if (*(unsigned char *)(self + 0x20) != 4)
        func_PAL_002B5E30(self, *(float *)(self + 0xF8));
    else
        vec_step_toward_target_limited(self + 0x10, &D_L02_001B03F0, 0.20000002f);
    break;
    case 1:
    if (coll_point_inside_record_volume(self + 0x10, arena_get_state_word(*(void **)(self + 0xB8))))
        func_PAL_L01_00323068(self, target);
    else
        func_PAL_L01_00323068(self, arena_get_camera_point(*(void **)(self + 0xB8)));
    if ((frame > 0.0f && frame < 2.0f) || (frame > 15.0f && frame < 17.0f) ||
        (frame > 30.0f && frame < 32.0f) || (frame > 45.0f && frame < 47.0f)) {
        D_L02_001BA3C0.amount = 0.05f;
        D_L02_001BA3C0.time = 12;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 2:
    if (frame > 12.0f && frame < 25.0f) {
        moby_transform_joint_to_world(self, 4, before);
        func_PAL_002B5E30(self, heading);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        moby_transform_joint_to_world(self, 4, after);
        FastVecSub(delta, before, after);
        FastVecAdd(self + 0x10, self + 0x10, delta);
    } else if (frame > 42.0f && frame < 55.0f) {
        moby_transform_joint_to_world(self, 8, before);
        func_PAL_002B5E30(self, heading);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        moby_transform_joint_to_world(self, 8, after);
        FastVecSub(delta, before, after);
        FastVecAdd(self + 0x10, self + 0x10, delta);
    }
    if ((frame > 0.0f && frame < 2.0f) || (frame > 29.0f && frame < 31.0f)) {
        D_L02_001BA3C0.amount = 0.1f;
        D_L02_001BA3C0.time = 12;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 3:
        if (frame < 23.0f)
            break;
    case 4:
    moby_start_effect_from_entry(self, mat_fast_helper_a(*(float *)(state + 0xF0), *(float *)(state + 0xF4)));
    *(float *)(state + 0xF8) -= *(float *)(state + 0x7C);
    FastVecAdd(self + 0x10, self + 0x10, state + 0xF0);
    break;
    case 5:
    if (frame > 3.0f && frame < 5.0f) {
        D_L02_001BA3C0.amount = 0.4f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 6:
    if (frame > 20.0f && frame < 22.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 7:
    if ((unsigned int)(*(unsigned char *)(self + 0x20) - 10) >= 2) {
        *(float *)(self + 0xF8) += ((*(float *)(state + 0x20) / (float)*(short *)(state + 0x24)) * -90.0f + 160.0f) * 0.0003490659f;
        *(float *)(self + 0xF8) = math_fast_float_g(*(float *)(self + 0xF8));
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        turret_spawn_beam_hits(self);
        if (distance > 12.0f && *(unsigned char *)(self + 0x20) != 10) {
            if (coll_point_inside_record_volume(self + 0x10, arena_get_state_word(*(void **)(self + 0xB8)))) {
                speed = ((*(float *)(state + 0x20) / (float)*(short *)(state + 0x24)) * -2.2f + 3.0f) * 0.020000001f;
                ApproachValue((float *)(self + 0x10), target[0], speed);
                ApproachValue((float *)(self + 0x14), target[1], speed);
            } else {
                ApproachValue((float *)(self + 0x10), arena_get_camera_point(*(void **)(self + 0xB8))[0], 0.40000004f);
                ApproachValue((float *)(self + 0x14), arena_get_camera_point(*(void **)(self + 0xB8))[1], 0.40000004f);
            }
        }
    }
    break;
    case 8:
    if (frame > 30.0f && frame < 32.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    case 9:
        break;
    }
    if (*(float *)(self + 0x18) < arena_get_camera_point(*(void **)(self + 0xB8))[2])
        *(float *)(self + 0x18) = arena_get_camera_point(*(void **)(self + 0xB8))[2];
    *(int *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + g_moby_l02_pool + 0x98) = saved;
}
