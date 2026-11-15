/* func_PAL_L00_003CD850, the PAL copy of func_L00_003C9978: the same C, where rename func_00334160 becomes func_PAL_00335DD0; rename func_002AC728 becomes func_PAL_002AD288; rename func_L00_00341410 becomes func_PAL_L00_00343940; wrap vars- becomes accel (({e}) * 1.44f). */
/* Homing projectile update, in all 27 levels. A unit of its own for -ffast-math (min.s) and
 * -frac2-hazard-labels (the fast/slow arms' cross-jump lands on the mtc1 hazard nop). */

#include "common.h"

typedef struct Vec4_003C9978 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec4_003C9978;

typedef int TI_003C9978 __attribute__((mode(TI)));

typedef union Quad_003C9978 {
    TI_003C9978 q;
    Vec4_003C9978 v;
} Quad_003C9978;

typedef struct Class_003C9978 {
    u8 pad0[0x46];
    s16 kind;                       /* 0x46 */
} Class_003C9978;

typedef struct Moby_003C9978 {
    u8 pad0[0x10];
    Vec4_003C9978 pos;              /* 0x10 */
    u8 state;                       /* 0x20 */
    u8 pad21[3];
    Class_003C9978 *cls;            /* 0x24 */
    u8 pad28[8];
    union {
        u64 all;
        struct {
            u32 lo;
            u16 mode;
            u16 hi;
        } h;
    } flags;                        /* 0x30 */
    u8 pad38[0x30];
    struct Vars_003C9978 *vars;     /* 0x68 */
    u8 pad6C[0x2C];
    s32 alive;                      /* 0x98 */
    u8 pad9C[0xE];
    s16 oclass;                     /* 0xAA */
    u8 padAC[0xC];
    s32 b8;                         /* 0xB8 */
    u8 padBC[4];
    Vec4_003C9978 m[3];             /* 0xC0 */
} Moby_003C9978;

typedef struct Vars_003C9978 {
    Vec4_003C9978 vel;              /* 0x00 */
    Vec4_003C9978 trail[4];         /* 0x10 */
    Moby_003C9978 *target;          /* 0x50 */
    f32 f54;                        /* 0x54 */
    f32 wobble_z;                   /* 0x58 */
    f32 wobble;                     /* 0x5C */
    f32 speed;                      /* 0x60 */
    f32 spin;                       /* 0x64 */
    f32 max_speed;                  /* 0x68 */
    s16 flip;                       /* 0x6C */
    s16 effect;                     /* 0x6E */
    f32 accel;                      /* 0x70 */
    f32 damage;                     /* 0x74 */
    u8 b78;                         /* 0x78 */
    u8 b79;                         /* 0x79 */
    u8 spark;                       /* 0x7A */
    u8 fast;                        /* 0x7B */
    u8 locked;                      /* 0x7C */
    u8 trail_timer;                 /* 0x7D */
    u16 life;                       /* 0x7E */
} Vars_003C9978;

typedef union Info_003C9978 {
    struct {
        Vec4_003C9978 a;
        Vec4_003C9978 b;
        /* Reused as the collision request tail before the direction is needed. */
        Vec4_003C9978 direction;
    } v;
    struct {
        Vec4_003C9978 direction;
        void *source;
        u32 flags;
        u8 kind;
        u8 count;
        u16 oclass;
        float damage;
        int repeats;
        float extra;
    } hit;
    struct {
        u8 pad0[0x10];
        struct Pair_003C9978 {
            void *p[2];
        } pair;
    } t;
} Info_003C9978;

typedef struct Collide_003C9978 {
    u8 pad0[0xAA];
    u16 oclass;
} Collide_003C9978;

extern Moby_003C9978 *g_area_hit_targets[];
extern void *g_hero_moby;
extern s16 D_0018A168;
extern s32 D_L00_001A8FF0 __attribute__((sda));
extern s32 D_L00_001A8FF4;
extern s32 D_L00_001ADB2C MACRO_ADDR;
extern Collide_003C9978 *D_L00_001BF218;
extern u8 D_L00_001BF230[];
extern struct Pair_003C9978 D_L00_001B0128;

extern int func_001163B0(void);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern int coll_process_hit(float, void *, int, void *, int);
extern int math_fast_float_d(int *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern void QueueMobyImpact(void *, void *);
extern int moby_get_private_value_0(void *);
extern void func_PAL_002AD288(void *, void *, float, float, int);
extern void table_clear_entry_flag(int);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void func_PAL_00335DD0(void *, int, int);
extern void ref_L00_003C9978_00(void (*)(Moby_003C9978 *), void *);
extern void effect_update_in_state_one(Moby_003C9978 *);
extern void vec_turn_toward_target(void *, void *, void *, void *, void *, int, float, float, float, float);
extern void moby_forward_position_call(void *, void *, int);
extern void moby_call_handler_on_inner_data(void *, void *);
extern void * func_PAL_L00_00343940(void *, void *, void *, int, int, float);

void func_PAL_L00_003CD850(Moby_003C9978 *self)
{
    Vec4_003C9978 saved;
    Quad_003C9978 up;
    Quad_003C9978 off;
    Vec4_003C9978 step;
    Info_003C9978 info;
    int life;
    int spark;
    int trail_timer;
    int fast_trail;
    Vars_003C9978 *vars;
    int i;

    off.q = 0;
    vars = self->vars;
    up.q = 0;
    off.v.x = -0.3f;
    up.v.z = 1.0f;
    off.v.w = 1.0f;

    switch (self->state) {
    case 0:
        self->state = 1;
        vars->flip = func_001163B0() % 2;
        vars->spin = 0.0f;
        vec_scale_to_length(&self->m[0], &vars->vel, 1.0f);
        FastVecCross(&self->m[1], &self->m[0], &up);
        vec_scale_to_length(&self->m[1], &self->m[1], 1.0f);
        FastVecCross(&self->m[2], &self->m[1], &self->m[0]);
        matrix_mul_vec3(&off, &off, &self->m[0]);
        vec_transform_or_copy(&self->pos, &self->pos);
        shop_trigger_current_state_effect(vars, vars);
        FastVecAdd(&off, &off, &self->pos);
        vec_scale_to_length(&step, &off, 0.01f);
        qcopy(&vars->trail[0], &off);
        for (i = 0; i < 3; i++)
            FastVecAdd(&vars->trail[i + 1], &vars->trail[i], &step);
        vars->trail_timer = 2;
    case 1: {
        float dist;
        float travelled;
        int hit;

        vars->spin = vars->spin - 0.1f;
        if (vars->spin <= -8.0f)
            vars->spin = vars->spin + 8.0f;

        if (vars->target != 0 && vars->locked == 0) {
            if ((s8)vars->target->state < 0 || vars->target->alive == 0)
                vars->target = 0;
            if (vars->target == 0) {
                int n = coll_process_hit(15.0f, &self->pos, 0, self, 0);
                int i;

                /* The end test leaves by goto, so the break is the first exit expand_end_loop sees
                 * and the whole body rotates. It is then too long for jump.c to duplicate, which
                 * keeps retail's entry branch to the test. */
                for (i = 0;; i++) {
                    Moby_003C9978 *m;
                    Class_003C9978 *cls;
                    u16 *mode;
                    s16 *kind;
                    Moby_003C9978 **found;

                    if (i >= n)
                        goto searched;
                    m = g_area_hit_targets[i];
                    mode = &m->flags.h.mode;
                    if ((*mode & 0x1000) && m->oclass != 0xA7E && m != g_hero_moby) {
                        cls = m->cls;
                        kind = &cls->kind;
                        if (*kind == 5) {
                            found = &vars->target;
                            *found = m;
                            break;
                        }
                    }
                }
            searched:;
            }
        }

        qcopy(&saved, &self->pos);
        vec_scale_to_length(&self->m[0], &vars->vel, 1.0f);
        FastVecCross(&self->m[1], &self->m[0], &up);
        vec_scale_to_length(&self->m[1], &self->m[1], 1.0f);
        FastVecCross(&self->m[2], &self->m[1], &self->m[0]);
        FastVecAdd(&self->pos, &self->pos, &vars->vel);
        life = vars->life;
        if (math_fast_float_d(&life) != 0) {
            self->state = 2;
            self->flags.h.mode |= 0x41;
        }
        vars->life = life;

        if (self->pos.x < 2.0f || self->pos.x > 1021.0f || self->pos.y < 2.0f || self->pos.y > 1021.0f
            || self->pos.z < 2.0f || self->pos.z > 1021.0f) {
            qcopy(&self->pos, &saved);
            self->state = 2;
            self->flags.h.mode |= 0x41;
        }

        off.v.x = -0.3f;
        off.v.w = 1.0f;
        off.v.y = 0.0f;
        off.v.z = 0.0f;
        matrix_mul_vec3(&off, &off, &self->m[0]);
        FastVecAdd(&off, &off, &self->pos);
        vec_transform_or_copy(&off, &off);
        self->m[1].y = self->m[1].y * 0.5f;
        self->m[2].z = self->m[2].z * 0.5f;

        if (coll_test_point(&self->pos, 0x10, self, 0.25f) != 0)
            hit = 1;
        else
            hit = CollLine(&saved, &self->pos, 0x10, self, 0) != 0;
        if (hit) {
            if (D_L00_001BF218 != 0 && (D_L00_001BF218->oclass == 0x1366 || D_L00_001BF218->oclass == 0x1367))
                hit = 0;
            if (hit) {
                int n = coll_process_hit(1.0f, &self->pos, 0, self, 0);
                int i;

                for (i = 0; i < n; i++) {
                    if (g_area_hit_targets[i]->flags.all & 0x500000000000ULL) {
                        make_hit_descriptor(&info, self, 0x210000, vars->damage, vars);
                        info.hit.oclass = self->oclass;
                        info.hit.kind = 5;
                        info.hit.count = 3;
                        QueueMobyImpact(g_area_hit_targets[i], &info);
                        func_PAL_00335DD0(g_area_hit_targets[i], 0x40, self->b8);
                    }
                }
                func_PAL_002AD288(self, D_L00_001BF230, 1.0f, 13.0f, 0);
                self->state = 2;
                self->flags.h.mode |= 0x41;
            }
        }

        vec_scale_to_length(&vars->vel, &vars->vel,
                      (vars->max_speed < vars->speed ? vars->max_speed : vars->speed) * 0.020000001f);
        vars->speed = vars->speed + ((vars->accel) * 1.44f);

        if (vars->target != 0) {
            float *health = ((float *)moby_get_private_value_0(vars->target));
            int n;

            moby_forward_position_call(vars->target, &info, 1);
            if (health != 0 && D_L00_001A8FF0 == 0) {
                FastVecScale(&info.v.b, &vars->target->m[2], health[4]);
                FastVecAdd(&info.v.b, &info.v.b, &vars->target->pos);
            } else if (D_L00_001A8FF0 != 0) {
                moby_call_handler_on_inner_data(self, &info.v.direction);
                vec_scale_to_length(&info.v.direction, &info.v.direction, 1.0f);
                FastVecAdd(&info.v.b, &info.v.direction, &vars->target->pos);
            } else {
                qcopy(&info.v.b, &vars->target->pos);
            }
            dist = fast_vec_dist(&self->pos, &info.v.b);
            if (vars->fast != 0) {
                if (dist < 1.5f)
                    dist = 0.0f;
            } else {
                if (dist < 0.25f)
                    dist = 0.0f;
            }
            n = D_L00_001A8FF0;
            if (n == 0)
                n = D_L00_001A8FF4;
            if (n == 0 && D_0018A168 == 0) {
                info.v.b.y += math_fast_sin_or_cos_b(vars->wobble) * (dist * 0.749f < 0.749f ? dist * 0.749f : 0.749f);
                info.v.b.x -= math_fast_sin_or_cos_a(vars->wobble) * (dist * 0.751f < 0.751f ? dist * 0.751f : 0.751f);
                info.v.b.z += (math_fast_sin_or_cos_b(vars->wobble_z) + 1.0f) * (dist * 0.5f < 0.5f ? dist * 0.5f : 0.5f);
            }
            if (vars->fast != 0)
                vec_turn_toward_target(&self->pos, vars, &info.v.b, &vars->f54, &info, 0, 0.036000002f, 0.24000001f, 0.0f, 1.0f);
            else
                vec_turn_toward_target(&self->pos, vars, &info.v.b, &vars->f54, &info, 0, 0.036000002f, 0.24000001f, 0.0f, 0.25f);
        }

        travelled = fast_vec_dist(&self->pos, &saved);
        info.v.a.w = -1.0f;
        spark = vars->spark;
        if (math_fast_float_d(&spark) != 0 || vars->spark == 0) {
            info.t.pair = D_L00_001B0128;
            func_PAL_L00_00343940(self, &info, info.t.pair.p[vars->flip % 2], vars->b78, vars->b79, travelled * 0.5f);
            vars->flip++;
        }
        vars->spark = spark;
        vars->wobble = FastAddRotations(vars->wobble, math_random_float_range(0.01f, 0.1f));
        vars->wobble_z = fast_subtract_rotations(vars->wobble_z, math_random_float_range(0.025f, 0.25f));
        fast_trail = D_L00_001ADB2C;
        trail_timer = vars->trail_timer;
        if (fast_trail != 0) {
            for (i = 3; i > 0; i--) {
                qcopy(&vars->trail[i], &vars->trail[i - 1]);
                vec_transform_or_copy(&vars->trail[i], &vars->trail[i]);
            }
            qcopy(&vars->trail[0], &off);
        } else if (math_fast_float_d(&trail_timer) != 0) {
            for (i = 3; i > 0; i--)
                qcopy(&vars->trail[i], &vars->trail[i - 1]);
            qcopy(&vars->trail[0], &off);
            trail_timer = 2;
        }
        vars->trail_timer = trail_timer;
        for (i = 2; i >= 0; i--)
            ;
        break;
    }
    case 2:
        table_clear_entry_flag(vars->effect);
        moby_mark_spawned(self);
        return;
    }

    if (self != 0) {
        if (self->state != 0xFE) {
            if (self->state != 0xFD) {
                vec_transform_or_copy(&self->pos, &self->pos);
                shop_trigger_current_state_effect(vars, vars);
                part_steer_effect_direction(vars->effect, vars, 0);
            }
        }
    }
    ref_L00_003C9978_00(effect_update_in_state_one, self);
}
