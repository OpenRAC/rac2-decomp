#include "names.h"
/*
 * func_PAL_L00_00410630, the PAL copy of func_L00_0040BA30: the same C, where the effect timer and the
 * particle lifetimes take the 50 Hz scale, the literal 30 becomes 25, and the second burst loop keeps its
 * counter and random value in locals of its own.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; char *ptr[0x980]; TI128 q[0x260]; } Hero;
extern Hero g_hero_state;
typedef union { unsigned char b[0x400]; short h[0x200]; int i[0x100]; float f[0x100]; char *p[0x100]; TI128 q[0x40]; } Blk;
extern Blk g_hero_aim_vector;
extern Blk g_item_slot_to_record;
typedef struct {
    unsigned char pad0[4];
    unsigned char b4;
    unsigned char pad5[0x6B];
    float f70;
    unsigned char pad74[0x6C];
} ClassEntry;
extern ClassEntry g_weapon_l00_table[];
extern Blk g_collision_result;
extern Blk g_effect_definitions;
extern char g_default_vector[] __attribute__((sda));
extern unsigned char *g_effect_param_pointer_a[];
extern float g_clank_zapper_aim_drop __attribute__((sda));
extern float g_clank_zapper_cone_angle __attribute__((sda));
extern int g_clank_zapper_timer __attribute__((sda));
extern int g_clank_zapper_particle_param_a __attribute__((sda));
extern int g_clank_zapper_particle_param_b __attribute__((sda));
extern int g_clank_zapper_particle_kind __attribute__((sda));
extern int g_clank_zapper_particle_color __attribute__((sda));
extern int g_frame_l00_counter __attribute__((sda));

extern void cam_compute_view_direction(void *, void *, int);
extern void moby_transform_joint_to_world(int, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *moby_get_private_value_0(void *);
extern int math_fast_float_d(void *);
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int CollLine(void *, void *, int, int, void *);
extern void part_spawn_smoke_and_sparks_pal(void *, int, int);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_PAL_L00_0040FF58(void *);
extern void ref_L00_0040BA30_00(void (*)(void *), void *);
extern void func_PAL_L00_004114B0(void *);

typedef struct {
    float v[4];
    char *owner;
    int flags;
    signed char b18;
    signed char b19;
    unsigned short h1A;
    float f1C;
    int f20;
} Hit;

typedef struct BeamVars {
    char pad00[0xC];
    struct BeamMoby *target;
    int timer;
    int pad14;
    int effect;
    int enabled;
    char pad20[0x10];
    float end[4];
    float aim[4];
    float dir[4];
    float left[4];
    float right[4];
} BeamVars;

typedef struct BeamMoby {
    char pad00[0x10];
    float pos[4];
    unsigned char state;
    char pad21[0x13];
    unsigned short flags;
    char pad36[0x32];
    BeamVars *vars;
    char pad6c[0x3E];
    unsigned short oClass;
} BeamMoby;

void func_PAL_L00_00410630(BeamMoby *self)
{
    float old0[4];
    float mtx[4];
    float old20[4];
    float dir[4];
    float v40[4];
    float v50[4];
    Hit hit;
    BeamVars *vars = self->vars;
    float ang;
    float r;
    int i;
    int m;
    BeamMoby *t;
    float s1, s2, s3, s4, s5, s6, s7, s8, s9;
    int n;
    int heroNode;
    ClassEntry *tbl;

    qcopy(old0, self->pos);
    cam_compute_view_direction(self->pos, mtx, 1);
    heroNode = g_hero_state.i[0x1314 / 4];
    moby_transform_joint_to_world(heroNode, 6, vars->left);
    moby_transform_joint_to_world(heroNode, 7, vars->right);
    qcopy(old20, self->pos);
    FastVecSub(dir, vars->end, &g_hero_state.b[0x2010]);
    vec_scale_to_length(dir, dir, 1.0f);
    ang = mat_fast_helper_a(*(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x10) - g_hero_state.f[0x80 / 4],
                        *(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x14) - g_hero_state.f[0x84 / 4]);
    if (ang < 1.5707964897155762f)
        r = math_random_float_range(0.0f, -0.7853982448577881f);
    else
        r = math_random_float_range(0.0f, 0.7853982448577881f);
    qcopy(vars->aim, &g_hero_aim_vector);
    vars->aim[2] -= g_clank_zapper_aim_drop;
    FastVecSub(vars->aim, vars->aim, &g_hero_aim_vector);
    math_apply_axis_rotation_to_quat(vars->aim, vars->aim, dir, r);
    FastVecAdd(vars->aim, &g_hero_aim_vector, vars->aim);
    t = vars->target;
    if (t != 0) {
        if (t->state == 0xFE) {
            vars->target = 0;
        } else if (t->state == 0xFD) {
            vars->target = 0;
        } else {
            FastVecSub(v40, t->pos, self->pos);
            if (FastVecLength(v40) != 0.0f) {
                char *target = moby_get_private_value_0(vars->target);
                if (target != 0) {
                    FastVecScale(v50, mtx, *(float *)(target + 0x10));
                    FastVecAdd(v40, v40, v50);
                    FastVecLength(v40);
                }
            } else {
                vars->target = 0;
            }
        }
    }
    ang = FastDiffRots(mat_fast_helper_a(*(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x10) - g_hero_state.f[0x80 / 4],
                                      *(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x14) - g_hero_state.f[0x84 / 4]),
                        g_hero_state.f[0x98 / 4]);
    switch (self->state) {
    case 0:
        /* Each arm repeats its whole setup; the compiler cross-jumps the shared tails away. */
        tbl = g_weapon_l00_table;
        if (tbl[g_item_slot_to_record.b[9]].b4 != 0) {
            hit.flags = 0x110000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = tbl[g_item_slot_to_record.b[0x49]].f70;
            qcopy(hit.v, vars->dir);
            vec_scale_to_length(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        } else {
            hit.flags = 0x10000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = tbl[g_item_slot_to_record.b[9]].f70;
            qcopy(hit.v, vars->dir);
            vec_scale_to_length(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        }
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < ang) {
            if (vars->enabled == 0)
                { moby_mark_spawned(self); return; }
            if (CollLine(&g_hero_aim_vector, vars->end, 0, g_hero_aim_vector.i[0x280 / 4], &hit) == 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.i[0x1C / 4] > 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.p[0x18 / 4] == 0)
                part_spawn_smoke_and_sparks_pal(&g_collision_result.b[0x20], 0xF, 1);
            else if (*(int *)(g_collision_result.p[0x18 / 4] + 0x98) != 0)
                part_spawn_smoke_and_sparks_pal(&g_collision_result.b[0x20], 0xA, 1);
            snd_play_from_class_bank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = ((s32)(g_clank_zapper_timer) * 5 + 2) / 6;
        } else {
            if (CollLine(&g_hero_aim_vector, vars->end, 0, g_hero_aim_vector.i[0x280 / 4], &hit) == 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.i[0x1C / 4] > 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.p[0x18 / 4] == 0)
                part_spawn_smoke_and_sparks_pal(&g_collision_result.b[0x20], 0xF, 0);
            else if (*(int *)(g_collision_result.p[0x18 / 4] + 0x98) != 0)
                part_spawn_smoke_and_sparks_pal(&g_collision_result.b[0x20], 0xA, 0);
            snd_play_from_class_bank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = ((s32)(g_clank_zapper_timer) * 5 + 2) / 6;
        }
        FastVecSub(v40, vars->end, &g_hero_aim_vector);
        vec_scale_to_length(v40, v40, FastVecLength(v40) * 0.5f);
        FastVecAdd(v40, &g_hero_aim_vector, v40);
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < ang) {
            if (vars->enabled == 0)
                goto bounds;
            vars->effect = part_l00_alloc_effect_slot_2(v40, 10.0f, 0.0f, 1.0f, 0.1f, 0.1f);
        } else {
            vars->effect = part_l00_alloc_effect_slot_2(v40, 10.0f, 0.0f, 0.1f, 1.0f, 0.1f);
        }
        break;
    case 1:
        if (math_fast_float_d(&vars->timer) != 0) {
            vars->target = 0;
            if (vars->effect != -1)
                gfx_free_point_light(vars->effect);
            moby_mark_spawned(self);
            return;
        }
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < ang) {
            if (vars->enabled != 0) {
                for (i = 0; i < 10; i++) {
                    char *p;
                    s1 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v40, vars->end, vars->left);
                    vec_scale_to_length(v40, v40, s1 * FastVecLength(v40));
                    FastVecAdd(v40, vars->left, v40);
                    s2 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v50, vars->end, vars->right);
                    vec_scale_to_length(v50, v50, s2 * FastVecLength(v50));
                    FastVecAdd(v50, vars->right, v50);
                    n = math_random_int_below(0xFF);
                    s3 = math_random_float_range(0.35f, 0.5f);
                    p = part_spawn_gravity_fade(v40, g_default_vector, ((s32)(g_clank_zapper_particle_param_a) * 5 + 2) / 6, g_clank_zapper_particle_param_b, n, 0x30, 0,
                                      s3 * 210000.0f, s3 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[7];
                    p = part_spawn_gravity_fade(v50, g_default_vector, ((s32)(g_clank_zapper_particle_param_a) * 5 + 2) / 6, g_clank_zapper_particle_param_b, n, 0x30, 0,
                                      s3 * 210000.0f, s3 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[7];
                }
                {
                    int j;
                    int n2;

                for (j = 0; j < 20; j++) {
                    char *p;
                    s4 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v40, vars->end, vars->left);
                    vec_scale_to_length(v40, v40, s4 * FastVecLength(v40));
                    FastVecAdd(v40, vars->left, v40);
                    s5 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v50, vars->end, vars->right);
                    vec_scale_to_length(v50, v50, s5 * FastVecLength(v50));
                    FastVecAdd(v50, vars->right, v50);
                    n2 = math_random_int_below(0xFF);
                    s6 = math_random_float_range(0.2f, 0.35f);
                    v40[0] += math_random_signed_float_range(0.0f, 0.02f);
                    v40[1] += math_random_signed_float_range(0.0f, 0.02f);
                    v40[2] += math_random_signed_float_range(0.0f, 0.02f);
                    p = part_spawn_gravity_fade(v40, g_default_vector, ((s32)(g_clank_zapper_particle_kind) * 5 + 2) / 6, g_clank_zapper_particle_color, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    s6 *= 0.5f;
                    p = part_spawn_gravity_fade(v40, g_default_vector, ((s32)(g_clank_zapper_particle_kind) * 5 + 2) / 6, 0x808080, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    v50[0] += math_random_signed_float_range(0.0f, 0.02f);
                    v50[1] += math_random_signed_float_range(0.0f, 0.02f);
                    v50[2] += math_random_signed_float_range(0.0f, 0.02f);
                    p = part_spawn_gravity_fade(v50, g_default_vector, ((s32)(g_clank_zapper_particle_kind) * 5 + 2) / 6, g_clank_zapper_particle_color, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    s6 *= 0.5f;
                    p = part_spawn_gravity_fade(v50, g_default_vector, ((s32)(g_clank_zapper_particle_kind) * 5 + 2) / 6, 0x808080, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (g_effect_definitions.p[0x184 / 4])[6];
                }
                }
                if (vars->target != 0 && g_frame_l00_counter % 5 == 0) {
                    char *p;
                    s7 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v40, vars->end, vars->left);
                    vec_scale_to_length(v40, v40, s7 * FastVecLength(v40));
                    FastVecAdd(v40, vars->left, v40);
                    s8 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(v50, vars->end, vars->right);
                    vec_scale_to_length(v50, v50, s8 * FastVecLength(v50));
                    FastVecAdd(v50, vars->right, v50);
                    p = part_spawn_gravity_fade(v40, g_default_vector, 0x19, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (p != 0)
                        p[2] = *g_effect_param_pointer_a[0];
                    p = part_spawn_gravity_fade(v50, g_default_vector, 0x19, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (p != 0)
                        p[2] = *g_effect_param_pointer_a[0];
                }
            }
        } else {
            for (m = 0; m < 10; m++) {
                char *p;
                s9 = math_random_float_range(0.25f, 0.4f) * 210000.0f;
                p = part_spawn_gravity_fade(&g_hero_state.b[0x2010], g_default_vector, 2, 0x108010, 2, 0x7F, 0x10,
                                  s9, s9, 0.0f, 0);
                if (p != 0)
                    p[2] = *g_effect_definitions.p[0x64 / 4];
                p = part_spawn_gravity_fade(&g_hero_state.b[0x2010], g_default_vector, 2, 0x208020, -1, 0x7F, 0x10,
                                  s9, s9, 0.0f, 0);
                if (p != 0)
                    p[2] = *g_effect_definitions.p[0x64 / 4];
            }
        }
        func_PAL_L00_0040FF58(self);
        ref_L00_0040BA30_00(func_PAL_L00_004114B0, self);
        break;
    }
bounds:
    if (self->pos[0] < 2.0f || self->pos[0] > 1021.0f ||
        self->pos[1] < 2.0f || self->pos[1] > 1021.0f ||
        self->pos[2] < 2.0f || self->pos[2] > 1021.0f)
        moby_mark_spawned(self);
}
