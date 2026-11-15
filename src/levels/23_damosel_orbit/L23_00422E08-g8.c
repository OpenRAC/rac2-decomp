#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

extern int PlayMobySound(int, int, u8 *);

extern void moby_mark_spawned(u8 *object);

/* the steering constants of the homing shot */
extern float D_L23_001B1914 __attribute__((sda));

extern float D_L23_001B1918 __attribute__((sda));

extern float D_L23_001B191C __attribute__((sda));

extern float D_L23_001B1920 __attribute__((sda));

extern float D_L23_001B192C __attribute__((sda));

extern float D_L23_001B1930 __attribute__((sda));

/* Absolute scalar view; the surrounding object extent is unqualified. */
extern float D_L23_001B3700[] __attribute__((sda));

extern u8 D_L23_001A8F20[] __attribute__((sda));

/* the last hit reported by the collision query */
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L23Hit1C0A80;

extern L23Hit1C0A80 g_last_ray_hit;

/* the record the collision query and the damage call read */
typedef struct {
    float v[4] __attribute__((aligned(16)));
    u8 *obj;
    s32 flags;
    u8 b18;
    u8 b19;
    u16 h1A;
    float f1C;
    s32 f20;
} L23Rec;

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

extern void SpawnExplosionEffects(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);

extern void coll_process_hit(void *, s32, s32, void *, float);

extern void vec_turn_toward_target(void *, void *, void *, void *, void *, void *, float, float, float, float);

/* EE ABI: retain integer and float argument order within their register banks. */
extern void part_spawn_gravity_fade(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

/* Per-frame update of a homing shot. It steers toward its target, leaves a spark trail,
   and blows up when it hits something or flies out of the level. */
void homing_l23_shot_update(u8 *obj) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    float vec_c[4] __attribute__((aligned(16)));
    L23Rec rec;
    u8 *vars;
    u8 *hit;
    u8 *other;
    float quat_len;
    float spark_size;
    s32 color_rand;
    s32 hit_boss;
    u16 other_class;

    *(u16 *)(obj + 0x34) &= 0xFFBE;
    vars = *(u8 **)(obj + 0x68);
    cam_compute_view_direction(obj + 0x10, up, 0);
    ApproachValue((float *)(vars + 0x1C), 2.3333335f, 0.055555556f);
    vec_scale_to_length(vel, obj + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, obj + 0xE0, axis);
    FastVecScale(quat, quat, D_L23_001B192C * 0.5f);
    quat_len = FastVecLength(quat);
    quat[3] = -square_root(1.0f - quat_len * quat_len);
    quaternion_to_rotation_basis(quat, mtx);
    multiply_matrix3x3(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(vec_c, *(u8 **)(vars + 0x18) + 0xE0, D_L23_001B1930);
            FastVecAdd(vec_b, *(u8 **)(vars + 0x18) + 0x10, vec_c);
            vec_turn_toward_target(obj + 0x10, obj + 0xC0, vec_b, vars + 0x20, up, vec_a,
                              D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B1920);
            vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
            FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x91) {
                FastVecSub(vec_a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(vec_a, vel) < 0.0f) {
                    vec_turn_toward_target(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, vec_b,
                                      D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B191C);
                    vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
                    FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            FastVecScale(vel, vars + 0x30, *(float *)(vars + 0x1C));
            vec_scale_to_length(vec_a, vel, 1.0f);
            qcopy(obj + 0xC0, vec_a);
        }
    }
    qcopy(vec_b, obj + 0x10);
    FastVecScale(vec_c, vel, 0.7f);
    spark_size = math_random_float_range(0.1f, 0.3f);
    color_rand = math_random_int_below(0xFF);
    vec_random_direction(vec_a, 0.0f, 0.1f);
    FastVecAdd(vec_a, vec_a, vec_b);
    part_spawn_gravity_fade(vec_a, D_L23_001A8F20, 0xF, 0x808080, color_rand, 0x20, 0, spark_size * 210000.0f, spark_size * 42000.0f, 0.0f, 0);
    FastVecAdd(vec_b, vec_b, vec_c);
    qcopy(vec_a, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, vel);
    if (*(float *)(obj + 0x10) < 0.0f || *(float *)(obj + 0x14) < 0.0f || *(float *)(obj + 0x18) < 0.0f) {
        moby_mark_spawned(obj);
        return;
    }
    rec.obj = obj;
    rec.flags = 0x8B0003;
    rec.f1C = D_L23_001B3700[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(obj + 0xAA);
    if (obj[0xBC] == 0 && CollLine(vec_a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        hit = g_last_ray_hit.f18;
        if (hit != 0) {
            if (hit != *(u8 **)(obj + 0xB8)) {
                obj[0xBC] = 2;
                qcopy(obj + 0x10, &g_last_ray_hit.f20);
            }
        } else if (g_last_ray_hit.f1C > 0) {
            obj[0xBC] = 1;
            qcopy(obj + 0x10, &g_last_ray_hit.f20);
        }
        hit_boss = 0;
        other = g_last_ray_hit.f18;
        if (other != 0) {
            other_class = *(u16 *)(other + 0xAA);
            if (other_class == 0xF7E /* moby class 3966 */ || other_class == MOBY_CLASS_MOTHERSHIP_BOSS_PART || (s16)other_class == 0x120F /* moby class 4623 */) {
                PlayMobySound(2, 0, obj);
                hit_boss = 1;
            }
        }
        if (hit_boss == 0) {
            PlayMobySound(0, 0, obj);
        }
    } else if (math_fast_float_d(vars + 0x14) != 0) {
        moby_mark_spawned(obj);
        return;
    }
    if (obj[0xBC] != 0) {
        SpawnExplosionEffects(obj, D_L23_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        coll_process_hit(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        moby_mark_spawned(obj);
    }
}
