#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

extern int PlayMobySound(int, int, u8 *);

extern void moby_mark_spawned(u8 *object);

/* the steering constants of the homing shot */
extern float D_L22_001B1524 __attribute__((sda));

extern float D_L22_001B1528 __attribute__((sda));

extern float D_L22_001B152C __attribute__((sda));

extern float D_L22_001B1530 __attribute__((sda));

extern float D_L22_001B153C __attribute__((sda));

extern float D_L22_001B1540 __attribute__((sda));

/* Absolute scalar view; the surrounding object extent is unqualified. */
extern float D_L22_001A93E0[] __attribute__((sda));

extern u8 D_L22_001A8F20[] __attribute__((sda));

/* the last hit reported by the collision query */
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L22Hit1C00C0;

extern L22Hit1C00C0 D_L22_001C00C0;

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

extern void SpawnExplosionEffects(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);

extern void coll_process_hit(void *, s32, s32, void *, float);

extern void vec_turn_toward_target(void *, void *, void *, void *, void *, void *, float, float, float, float);

/* EE ABI: retain integer and float argument order within their register banks. */
extern void part_spawn_gravity_fade(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

/* Updates a homing shot: steers it toward its target, leaves a trail, and destroys it with an impact when it hits something or leaves the map. */
void homing_l22_shot_update(u8 *obj) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    L22Rec rec;
    u8 *vars;
    u8 *hit;
    u8 *other;
    float len;
    float r;
    s32 n;
    s32 flag;
    u16 cls;

    *(u16 *)(obj + 0x34) &= 0xFFBE;
    vars = *(u8 **)(obj + 0x68);
    cam_compute_view_direction(obj + 0x10, up, 0);
    ApproachValue((float *)(vars + 0x1C), 2.3333335f, 0.055555556f);
    vec_scale_to_length(vel, obj + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, obj + 0xE0, axis);
    FastVecScale(quat, quat, D_L22_001B153C * 0.5f);
    len = FastVecLength(quat);
    quat[3] = -square_root(1.0f - len * len);
    quaternion_to_rotation_basis(quat, mtx);
    multiply_matrix3x3(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(c, *(u8 **)(vars + 0x18) + 0xE0, D_L22_001B1540);
            FastVecAdd(b, *(u8 **)(vars + 0x18) + 0x10, c);
            vec_turn_toward_target(obj + 0x10, obj + 0xC0, b, vars + 0x20, up, a,
                              D_L22_001B1524, D_L22_001B1528, 0.0f, D_L22_001B1530);
            vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
            FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x91) {
                FastVecSub(a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(a, vel) < 0.0f) {
                    vec_turn_toward_target(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, b,
                                      D_L22_001B1524, D_L22_001B1528, 0.0f, D_L22_001B152C);
                    vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
                    FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            FastVecScale(vel, vars + 0x30, *(float *)(vars + 0x1C));
            vec_scale_to_length(a, vel, 1.0f);
            qcopy(obj + 0xC0, a);
        }
    }
    qcopy(b, obj + 0x10);
    FastVecScale(c, vel, 0.7f);
    r = math_random_float_range(0.1f, 0.3f);
    n = math_random_int_below(0xFF);
    vec_random_direction(a, 0.0f, 0.1f);
    FastVecAdd(a, a, b);
    part_spawn_gravity_fade(a, D_L22_001A8F20, 0xF, 0x808080, n, 0x20, 0, r * 210000.0f, r * 42000.0f, 0.0f, 0);
    FastVecAdd(b, b, c);
    qcopy(a, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, vel);
    if (*(float *)(obj + 0x10) < 0.0f || *(float *)(obj + 0x14) < 0.0f || *(float *)(obj + 0x18) < 0.0f) {
        moby_mark_spawned(obj);
        return;
    }
    rec.obj = obj;
    rec.flags = 0x8B0003;
    rec.f1C = D_L22_001A93E0[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(obj + 0xAA);
    if (obj[0xBC] == 0 && CollLine(a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        hit = D_L22_001C00C0.f18;
        if (hit != 0) {
            if (hit != *(u8 **)(obj + 0xB8)) {
                obj[0xBC] = 2;
                qcopy(obj + 0x10, &D_L22_001C00C0.f20);
            }
        } else if (D_L22_001C00C0.f1C > 0) {
            obj[0xBC] = 1;
            qcopy(obj + 0x10, &D_L22_001C00C0.f20);
        }
        flag = 0;
        other = D_L22_001C00C0.f18;
        if (other != 0) {
            cls = *(u16 *)(other + 0xAA);
            if (cls == 0xF7E || cls == MOBY_CLASS_MOTHERSHIP_BOSS_PART || (s16)cls == 0x120F) {
                PlayMobySound(2, 0, obj);
                flag = 1;
            }
        }
        if (flag == 0) {
            PlayMobySound(0, 0, obj);
        }
    } else if (math_fast_float_d(vars + 0x14) != 0) {
        moby_mark_spawned(obj);
        return;
    }
    if (obj[0xBC] != 0) {
        SpawnExplosionEffects(obj, D_L22_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        coll_process_hit(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        moby_mark_spawned(obj);
    }
}
