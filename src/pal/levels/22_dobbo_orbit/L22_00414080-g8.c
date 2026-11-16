#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
extern int PlayMobySound(int, int, u8 *);
extern void moby_mark_spawned(u8 *object);
extern float g_homing_shot_turn_a __attribute__((sda));
extern float g_homing_shot_turn_b __attribute__((sda));
extern float g_homing_shot_limit_a __attribute__((sda));
extern float g_homing_shot_limit_b __attribute__((sda));
extern float g_homing_l22_shot_quat_scale __attribute__((sda));
extern float g_homing_shot_offset_scale __attribute__((sda));
extern float g_homing_shot_params[] __attribute__((sda));
extern u8 g_effect_position_params[] __attribute__((sda));
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L22Hit1C00C0;
extern L22Hit1C00C0 g_collision_l22_result;
typedef struct {
    float v[4] __attribute__((aligned(16)));
    u8 *obj;
    s32 flags;
    u8 b18;
    u8 b19;
    u16 h1A;
    float f1C;
    s32 f20;
} L22Rec;
extern void cam_compute_view_direction(void *, void *, s32);
extern float ApproachValue(float *, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float square_root(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern void vec_random_direction(void *, float, float);
extern s32 CollLine(void *, void *, s32, s32, void *);
extern s32 math_fast_float_d(void *);
extern void SpawnExplosionEffects_pal(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);
extern int coll_process_hit(void *, s32, s32, void *, float);
extern void vec_turn_toward_target(void *, void *, void *, void *, void *, void *, float, float, float, float);
extern void *part_spawn_gravity_fade(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

/* Updates a homing shot: speeds up, steers toward its target, trails particles and explodes on a hit or when its timer ends. (PAL) */
void homing_l22_shot_update_pal(u8 *moby) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    float vec_c[4] __attribute__((aligned(16)));
    L22Rec rec;
    u8 *vars;
    u8 *hit;
    u8 *hit_moby;
    float length;
    float size_rand;
    s32 color_rand;
    s32 flag;
    u16 hit_class;

    *(u16 *)(moby + 0x34) &= 0xFFBE;
    vars = *(u8 **)(moby + 0x68);
    cam_compute_view_direction(moby + 0x10, up, 0);
    ApproachValue((float *)(vars + 0x1C), 2.8000002f, 0.080000006f);
    vec_scale_to_length(vel, moby + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, moby + 0xE0, axis);
    FastVecScale(quat, quat, g_homing_l22_shot_quat_scale * 0.5f);
    length = FastVecLength(quat);
    quat[3] = -square_root(1.0f - length * length);
    quaternion_to_rotation_basis(quat, mtx);
    multiply_matrix3x3(moby + 0xC0, mtx, moby + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(vec_c, *(u8 **)(vars + 0x18) + 0xE0, g_homing_shot_offset_scale);
            FastVecAdd(vec_b, *(u8 **)(vars + 0x18) + 0x10, vec_c);
            vec_turn_toward_target(moby + 0x10, moby + 0xC0, vec_b, vars + 0x20, up, vec_a,
                              g_homing_shot_turn_a, g_homing_shot_turn_b, 0.0f, g_homing_shot_limit_b);
            vec_scale_to_length(moby + 0xC0, moby + 0xC0, 1.0f);
            FastVecScale(vel, moby + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x79) {
                FastVecSub(vec_a, moby + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(vec_a, vel) < 0.0f) {
                    vec_turn_toward_target(moby + 0x10, moby + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, vec_b,
                                      g_homing_shot_turn_a, g_homing_shot_turn_b, 0.0f, g_homing_shot_limit_a);
                    vec_scale_to_length(moby + 0xC0, moby + 0xC0, 1.0f);
                    FastVecScale(vel, moby + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            FastVecScale(vel, vars + 0x30, *(float *)(vars + 0x1C));
            vec_scale_to_length(vec_a, vel, 1.0f);
            qcopy(moby + 0xC0, vec_a);
        }
    }
    qcopy(vec_b, moby + 0x10);
    FastVecScale(vec_c, vel, 0.7f);
    size_rand = math_random_float_range(0.1f, 0.3f);
    color_rand = math_random_int_below(0xFF);
    vec_random_direction(vec_a, 0.0f, 0.1f);
    FastVecAdd(vec_a, vec_a, vec_b);
    part_spawn_gravity_fade(vec_a, g_effect_position_params, 0xC, 0x808080, color_rand, 0x20, 0, size_rand * 210000.0f, size_rand * 42000.0f, 0.0f, 0);
    FastVecAdd(vec_b, vec_b, vec_c);
    qcopy(vec_a, moby + 0x10);
    FastVecAdd(moby + 0x10, moby + 0x10, vel);
    if (*(float *)(moby + 0x10) < 0.0f || *(float *)(moby + 0x14) < 0.0f || *(float *)(moby + 0x18) < 0.0f) {
        moby_mark_spawned(moby);
        return;
    }
    rec.obj = moby;
    rec.flags = 0x8B0003;
    rec.f1C = g_homing_shot_params[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(moby + 0xAA);
    if (moby[0xBC] == 0 && CollLine(vec_a, moby + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        hit = g_collision_l22_result.f18;
        if (hit != 0) {
            if (hit != *(u8 **)(moby + 0xB8)) {
                moby[0xBC] = 2;
                qcopy(moby + 0x10, &g_collision_l22_result.f20);
            }
        } else if (g_collision_l22_result.f1C > 0) {
            moby[0xBC] = 1;
            qcopy(moby + 0x10, &g_collision_l22_result.f20);
        }
        flag = 0;
        hit_moby = g_collision_l22_result.f18;
        if (hit_moby != 0) {
            hit_class = *(u16 *)(hit_moby + 0xAA);
            if (hit_class == 0xF7E || hit_class == MOBY_CLASS_MOTHERSHIP_BOSS_PART || (s16)hit_class == 0x120F) {
                PlayMobySound(2, 0, moby);
                flag = 1;
            }
        }
        if (flag == 0) {
            PlayMobySound(0, 0, moby);
        }
    } else if (math_fast_float_d(vars + 0x14) != 0) {
        moby_mark_spawned(moby);
        return;
    }
    if (moby[0xBC] != 0) {
        SpawnExplosionEffects_pal(moby, g_effect_position_params, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        coll_process_hit(moby + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        moby_mark_spawned(moby);
    }
}
