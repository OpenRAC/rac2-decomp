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
extern void part_spawn_smoke_and_sparks(void *, int, int);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void lightning_strands_update(void *);
extern void ref_L00_0040BA30_00(void (*)(void *), void *);
extern void DrawBeamSegmentsOrRibbons(void *);

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

/* Per-frame update for the Clank Zapper beam (moby class 3800, Clank Zapper). It fires the beam from the hero, hurts what it hits, shows sparks and a light, then removes itself when the timer ends. */
void UpdateBeamDamageAndParticles(BeamMoby *self)
{
    float old_pos[4];
    float up_vec[4];
    float start_pos[4];
    float beam_dir[4];
    float point_a[4];
    float point_b[4];
    Hit hit;
    BeamVars *vars = self->vars;
    float angle;
    float tilt;
    int i;
    int j;
    int m;
    BeamMoby *locked_target;
    float left_frac1, right_frac1, size, left_frac2, right_frac2, spark_size, left_frac3, right_frac3, hand_size;
    int spin;
    int heroNode;
    ClassEntry *weapon_table;

    qcopy(old_pos, self->pos);
    cam_compute_view_direction(self->pos, up_vec, 1);
    heroNode = g_hero_state.i[0x1314 / 4];
    moby_transform_joint_to_world(heroNode, 6, vars->left);
    moby_transform_joint_to_world(heroNode, 7, vars->right);
    qcopy(start_pos, self->pos);
    FastVecSub(beam_dir, vars->end, &g_hero_state.b[0x2010]);
    vec_scale_to_length(beam_dir, beam_dir, 1.0f);
    angle = mat_fast_helper_a(*(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x10) - g_hero_state.f[0x80 / 4],
                        *(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x14) - g_hero_state.f[0x84 / 4]);
    if (angle < 1.5707964897155762f)
        tilt = math_random_float_range(0.0f, -0.7853982448577881f);
    else
        tilt = math_random_float_range(0.0f, 0.7853982448577881f);
    qcopy(vars->aim, &g_hero_aim_vector);
    vars->aim[2] -= g_clank_zapper_aim_drop;
    FastVecSub(vars->aim, vars->aim, &g_hero_aim_vector);
    math_apply_axis_rotation_to_quat(vars->aim, vars->aim, beam_dir, tilt);
    FastVecAdd(vars->aim, &g_hero_aim_vector, vars->aim);
    locked_target = vars->target;
    if (locked_target != 0) {
        if (locked_target->state == 0xFE) {
            vars->target = 0;
        } else if (locked_target->state == 0xFD) {
            vars->target = 0;
        } else {
            FastVecSub(point_a, locked_target->pos, self->pos);
            if (FastVecLength(point_a) != 0.0f) {
                char *target = moby_get_private_value_0(vars->target);
                if (target != 0) {
                    FastVecScale(point_b, up_vec, *(float *)(target + 0x10));
                    FastVecAdd(point_a, point_a, point_b);
                    FastVecLength(point_a);
                }
            } else {
                vars->target = 0;
            }
        }
    }
    angle = FastDiffRots(mat_fast_helper_a(*(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x10) - g_hero_state.f[0x80 / 4],
                                      *(float *)(g_hero_state.ptr[0x18D0 / 4] + 0x14) - g_hero_state.f[0x84 / 4]),
                        g_hero_state.f[0x98 / 4]);
    switch (self->state) {
    case 0:
        /* Each arm repeats its whole setup; the compiler cross-jumps the shared tails away. */
        weapon_table = g_weapon_l00_table;
        if (weapon_table[g_item_slot_to_record.b[9]].b4 != 0) {
            hit.flags = 0x110000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = weapon_table[g_item_slot_to_record.b[0x49]].f70;
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
            hit.f1C = weapon_table[g_item_slot_to_record.b[9]].f70;
            qcopy(hit.v, vars->dir);
            vec_scale_to_length(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        }
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < angle) {
            if (vars->enabled == 0)
                { moby_mark_spawned(self); return; }
            if (CollLine(&g_hero_aim_vector, vars->end, 0, g_hero_aim_vector.i[0x280 / 4], &hit) == 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.i[0x1C / 4] > 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.p[0x18 / 4] == 0)
                part_spawn_smoke_and_sparks(&g_collision_result.b[0x20], 0xF, 1);
            else if (*(int *)(g_collision_result.p[0x18 / 4] + 0x98) != 0)
                part_spawn_smoke_and_sparks(&g_collision_result.b[0x20], 0xA, 1);
            snd_play_from_class_bank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = g_clank_zapper_timer;
        } else {
            if (CollLine(&g_hero_aim_vector, vars->end, 0, g_hero_aim_vector.i[0x280 / 4], &hit) == 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.i[0x1C / 4] > 0)
                { moby_mark_spawned(self); return; }
            if (g_collision_result.p[0x18 / 4] == 0)
                part_spawn_smoke_and_sparks(&g_collision_result.b[0x20], 0xF, 0);
            else if (*(int *)(g_collision_result.p[0x18 / 4] + 0x98) != 0)
                part_spawn_smoke_and_sparks(&g_collision_result.b[0x20], 0xA, 0);
            snd_play_from_class_bank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = g_clank_zapper_timer;
        }
        FastVecSub(point_a, vars->end, &g_hero_aim_vector);
        vec_scale_to_length(point_a, point_a, FastVecLength(point_a) * 0.5f);
        FastVecAdd(point_a, &g_hero_aim_vector, point_a);
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < angle) {
            if (vars->enabled == 0)
                goto bounds;
            vars->effect = part_l00_alloc_effect_slot_2(point_a, 10.0f, 0.0f, 1.0f, 0.1f, 0.1f);
        } else {
            vars->effect = part_l00_alloc_effect_slot_2(point_a, 10.0f, 0.0f, 0.1f, 1.0f, 0.1f);
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
        if (g_clank_zapper_cone_angle * 0.01745329424738884f < angle) {
            if (vars->enabled != 0) {
                for (i = 0; i < 10; i++) {
                    char *part;
                    left_frac1 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_a, vars->end, vars->left);
                    vec_scale_to_length(point_a, point_a, left_frac1 * FastVecLength(point_a));
                    FastVecAdd(point_a, vars->left, point_a);
                    right_frac1 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_b, vars->end, vars->right);
                    vec_scale_to_length(point_b, point_b, right_frac1 * FastVecLength(point_b));
                    FastVecAdd(point_b, vars->right, point_b);
                    spin = math_random_int_below(0xFF);
                    size = math_random_float_range(0.35f, 0.5f);
                    part = part_spawn_gravity_fade(point_a, g_default_vector, g_clank_zapper_particle_param_a, g_clank_zapper_particle_param_b, spin, 0x30, 0,
                                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[7];
                    part = part_spawn_gravity_fade(point_b, g_default_vector, g_clank_zapper_particle_param_a, g_clank_zapper_particle_param_b, spin, 0x30, 0,
                                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[7];
                }
                for (j = 0; j < 20; j++) {
                    char *part;
                    left_frac2 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_a, vars->end, vars->left);
                    vec_scale_to_length(point_a, point_a, left_frac2 * FastVecLength(point_a));
                    FastVecAdd(point_a, vars->left, point_a);
                    right_frac2 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_b, vars->end, vars->right);
                    vec_scale_to_length(point_b, point_b, right_frac2 * FastVecLength(point_b));
                    FastVecAdd(point_b, vars->right, point_b);
                    spin = math_random_int_below(0xFF);
                    spark_size = math_random_float_range(0.2f, 0.35f);
                    point_a[0] += math_random_signed_float_range(0.0f, 0.02f);
                    point_a[1] += math_random_signed_float_range(0.0f, 0.02f);
                    point_a[2] += math_random_signed_float_range(0.0f, 0.02f);
                    part = part_spawn_gravity_fade(point_a, g_default_vector, g_clank_zapper_particle_kind, g_clank_zapper_particle_color, spin, 0x30, 0,
                                      spark_size * 210000.0f, spark_size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    spark_size *= 0.5f;
                    part = part_spawn_gravity_fade(point_a, g_default_vector, g_clank_zapper_particle_kind, 0x808080, spin, 0x30, 0,
                                      spark_size * 210000.0f, spark_size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    point_b[0] += math_random_signed_float_range(0.0f, 0.02f);
                    point_b[1] += math_random_signed_float_range(0.0f, 0.02f);
                    point_b[2] += math_random_signed_float_range(0.0f, 0.02f);
                    part = part_spawn_gravity_fade(point_b, g_default_vector, g_clank_zapper_particle_kind, g_clank_zapper_particle_color, spin, 0x30, 0,
                                      spark_size * 210000.0f, spark_size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[6];
                    spark_size *= 0.5f;
                    part = part_spawn_gravity_fade(point_b, g_default_vector, g_clank_zapper_particle_kind, 0x808080, spin, 0x30, 0,
                                      spark_size * 210000.0f, spark_size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (g_effect_definitions.p[0x184 / 4])[6];
                }
                if (vars->target != 0 && g_frame_l00_counter % 5 == 0) {
                    char *part;
                    left_frac3 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_a, vars->end, vars->left);
                    vec_scale_to_length(point_a, point_a, left_frac3 * FastVecLength(point_a));
                    FastVecAdd(point_a, vars->left, point_a);
                    right_frac3 = math_random_float_range(0.0f, 1.0f);
                    FastVecSub(point_b, vars->end, vars->right);
                    vec_scale_to_length(point_b, point_b, right_frac3 * FastVecLength(point_b));
                    FastVecAdd(point_b, vars->right, point_b);
                    part = part_spawn_gravity_fade(point_a, g_default_vector, 0x1E, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (part != 0)
                        part[2] = *g_effect_param_pointer_a[0];
                    part = part_spawn_gravity_fade(point_b, g_default_vector, 0x1E, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (part != 0)
                        part[2] = *g_effect_param_pointer_a[0];
                }
            }
        } else {
            for (m = 0; m < 10; m++) {
                char *part;
                hand_size = math_random_float_range(0.25f, 0.4f) * 210000.0f;
                part = part_spawn_gravity_fade(&g_hero_state.b[0x2010], g_default_vector, 2, 0x108010, 2, 0x7F, 0x10,
                                  hand_size, hand_size, 0.0f, 0);
                if (part != 0)
                    part[2] = *g_effect_definitions.p[0x64 / 4];
                part = part_spawn_gravity_fade(&g_hero_state.b[0x2010], g_default_vector, 2, 0x208020, -1, 0x7F, 0x10,
                                  hand_size, hand_size, 0.0f, 0);
                if (part != 0)
                    part[2] = *g_effect_definitions.p[0x64 / 4];
            }
        }
        lightning_strands_update(self);
        ref_L00_0040BA30_00(DrawBeamSegmentsOrRibbons, self);
        break;
    }
bounds:
    if (self->pos[0] < 2.0f || self->pos[0] > 1021.0f ||
        self->pos[1] < 2.0f || self->pos[1] > 1021.0f ||
        self->pos[2] < 2.0f || self->pos[2] > 1021.0f)
        moby_mark_spawned(self);
}
