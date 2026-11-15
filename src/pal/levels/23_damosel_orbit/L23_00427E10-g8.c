#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
typedef struct View_00422A30 {
    u8 pad0[0x188C];
    u8 *f188C;
    u8 pad1[0x2290 - 0x1890];
    u8 *f2290;
    s32 f2294;
} View_00422A30;
extern View_00422A30 g_hero_state;
extern float D_L23_001B1910 __attribute__((sda));
extern float D_L23_001B1928 __attribute__((sda));
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern s32 D_L23_001B36E0;
extern TI16 D_L23_001B1FB0 MACRO_ADDR;
extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern void mothership_project_point_onto_surface(void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float gravity_get_center_distance(void *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern s32 mothership_is_held(void);
extern s32 PlayMobySound(s32, s32, u8 *);

/* Creates the follower object for `src` (the effect that tracks `target`, or the hero, or nothing): copies
   the pose rows, fills the state, and when it has a live target works out the direction, the distance and
   the aim test, dropping the target when the aim, the range or the helper says so. */
u8 *func_PAL_L23_00427E10(u8 *src, TI16 *pos, u8 *target, s32 a3, s32 a4) {
    u8 *obj;
    u8 *st;
    TI16 loc[4];
    float f20;
    float f21;
    float f22;
    float dot;
    s32 flag;
    u8 *hero;
    TI16 c0;
    TI16 c1;
    TI16 c2;
    TI16 *reverse;

    obj = CreateMoby(0x118F);
    if (obj != 0) {
        st = *(u8 **)(obj + 0x68);
        moby_init_child_from_parent(obj, src);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * D_L23_001B1910;
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(float *)(st + 0x1C) = 0.40000004f;
        c0 = *(TI16 *)(src + 0xC0);
        *(TI16 *)(obj + 0xC0) = c0;
        c1 = *(TI16 *)(src + 0xD0);
        *(TI16 *)(obj + 0xD0) = c1;
        c2 = *(TI16 *)(src + 0xE0);
        *(TI16 *)(obj + 0xE0) = c2;
        *(u8 **)(st + 0x10) = src;
        qcopy(obj + 0x10, pos);
        *(s32 *)(st + 0x14) = 0x7D;
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) + *(float *)(obj + 0x2C);
        st[0x28] = a3;
        st[0x29] = a4;
        hero = g_mothership_boss_moby;
        if (target != 0) {
            *(u8 **)(st + 0x18) = target;
            *(s32 *)(st + 0x24) = 0x890000;
        } else {
            if (hero != 0) {
                *(u8 **)(st + 0x18) = hero;
                if (*(s16 *)(hero + 0xAA) == 0xF7F) {
                    *(s32 **)(st + 0x2C) = &D_L23_001B36E0;
                } else {
                    *(u8 **)(st + 0x2C) = hero + 0x10;
                }
                *(s32 *)(st + 0x24) = 0x890000;
            } else {
                *(s32 *)(st + 0x18) = 0;
                *(s32 *)(st + 0x24) = 0x890000;
                st[0x29] = 0;
                st[0x28] = 0;
            }
        }
        if (src == g_hero_state.f2290) {
            st[0x29] = 1;
        }
        if (st[0x28] == 0 && *(s32 *)(st + 0x18) != 0) {
            qcopy(&loc[0], *(void **)(st + 0x2C));
            mothership_project_point_onto_surface(&loc[0], 0.0f);
            FastVecSub(st + 0x30, *(u8 **)(st + 0x2C), obj + 0x10);
            qcopy(&loc[1], obj + 0x10);
            mothership_project_point_onto_surface(&loc[1], 0.0f);
            FastVecSub(&loc[2], &loc[0], &loc[1]);
            flag = 0;
            vec_scale_to_length(&loc[2], &loc[2], 1.0f);
            vec_scale_to_length(st + 0x30, st + 0x30, 1.0f);
            f21 = gravity_get_center_distance(src + 0x10);
            f20 = gravity_get_center_distance(*(u8 **)(st + 0x2C));
            f22 = fast_vec_dist(&loc[0], &loc[1]);
            if (f22 < 5.0f) {
                if (math_fabs(f21 - f20) > 10.0f) {
                    flag = 1;
                }
            }
            qcopy(&loc[3], obj + 0xC0);
            dot = FastVecDot(&loc[2], &loc[3]);
            if ((src == g_hero_state.f2290 && *(*(u8 **)(st + 0x18) + 0x31) == 0) ||
                dot < D_L23_001B1928 || 50.0f < f22 || flag != 0 || mothership_is_held() != 0) {
                *(s32 *)(st + 0x18) = 0;
            }
            if (src == g_hero_state.f2290) {
                if (*(s32 *)(st + 0x18) != 0) {
                    g_hero_state.f188C = st + 0x30;
                } else if (g_hero_state.f2294 == 0x5B) {
                    reverse = (TI16 *)(src + 0xE0);
                    qcopy(&D_L23_001B1FB0, reverse);
                    FastVecScale(&D_L23_001B1FB0, &D_L23_001B1FB0, -1.0f);
                    g_hero_state.f188C = (u8 *)&D_L23_001B1FB0;
                    qcopy(st + 0x30, &D_L23_001B1FB0);
                    st[0x28] = 0;
                    *(s32 *)(st + 0x18) = 1;
                    st[0x29] = 0;
                }
            }
        }
        *(s32 *)(st + 0x20) = 0;
        PlayMobySound(1, 0, obj);
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x41;
        obj[0xBC] = 0;
    }
    return obj;
}

extern int PlayMobySound(int, int, u8 *);
extern void moby_mark_spawned(u8 *object);
extern float D_L23_001B1914 __attribute__((sda));
extern float D_L23_001B1918 __attribute__((sda));
extern float D_L23_001B191C __attribute__((sda));
extern float D_L23_001B1920 __attribute__((sda));
extern float D_L23_001B192C __attribute__((sda));
extern float D_L23_001B1930 __attribute__((sda));
extern float D_L23_001B3700[] __attribute__((sda));
extern u8 D_L23_001A8F20[] __attribute__((sda));
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L23Hit1C0A80;
extern L23Hit1C0A80 g_last_ray_hit;
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
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float square_root(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern void vec_random_direction(void *, float, float);
extern s32 CollLine(void *, void *, s32, s32, void *);
extern s32 math_fast_float_d(void *);
extern void func_PAL_002AC718(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);
extern void coll_process_hit(void *, s32, s32, void *, float);
extern void vec_turn_toward_target(void *, void *, void *, void *, void *, void *, float, float, float, float);
extern void part_spawn_gravity_fade(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

void func_PAL_L23_004281E8(u8 *obj) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    L23Rec rec;
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
    ApproachValue((float *)(vars + 0x1C), 2.8000002f, 0.080000006f);
    vec_scale_to_length(vel, obj + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, obj + 0xE0, axis);
    FastVecScale(quat, quat, D_L23_001B192C * 0.5f);
    len = FastVecLength(quat);
    quat[3] = -square_root(1.0f - len * len);
    quaternion_to_rotation_basis(quat, mtx);
    multiply_matrix3x3(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(c, *(u8 **)(vars + 0x18) + 0xE0, D_L23_001B1930);
            FastVecAdd(b, *(u8 **)(vars + 0x18) + 0x10, c);
            vec_turn_toward_target(obj + 0x10, obj + 0xC0, b, vars + 0x20, up, a,
                              D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B1920);
            vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
            FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x79) {
                FastVecSub(a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(a, vel) < 0.0f) {
                    vec_turn_toward_target(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, b,
                                      D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B191C);
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
    part_spawn_gravity_fade(a, D_L23_001A8F20, 0xC, 0x808080, n, 0x20, 0, r * 210000.0f, r * 42000.0f, 0.0f, 0);
    FastVecAdd(b, b, c);
    qcopy(a, obj + 0x10);
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
    if (obj[0xBC] == 0 && CollLine(a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
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
        flag = 0;
        other = g_last_ray_hit.f18;
        if (other != 0) {
            cls = *(u16 *)(other + 0xAA);
            if (cls == 0xF7E || cls == 0xF7F || (s16)cls == 0x120F) {
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
        func_PAL_002AC718(obj, D_L23_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        coll_process_hit(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        moby_mark_spawned(obj);
    }
}
