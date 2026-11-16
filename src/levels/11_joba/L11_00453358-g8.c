#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern void gfx_draw_billboard_quad(void *a0, void *a1, void *a2, float f12, float f13, float f14,
                          int a3);

extern float math_random_angle(void);

extern int math_random_int_range(int a0, int a1);

extern float math_random_float_range(float a, float b);

extern void part_draw_billboard_sprite(char *a0, void *a1, void *a2, int a3, int t0, float f12,
                              float f13);

extern void vec_scale_to_length(char *a0, void *a1, float f12);

extern void math_build_axis_angle_quat(void *a0, void *a1, float f12);

extern void FastVecScale(char *a0, void *a1, float f12);

extern void vec_rotate_by_quaternion(void *a0, void *a1, void *a2);

extern void FastVecAdd(void *a0, void *a1, void *a2);

extern float fast_subtract_rotations(float a, float b);

extern void gfx_add_draw_callback_first(void *a0, void *a1);

extern void joba_effect_update_particles(char *p);

extern void gfx_init_square_packet(char *p);

extern void part_spawn_random_spark_beam(char *p, float *v);

extern void lerp_vector(float *out, char *a, char *b, float k);

extern float vec_distance_xy(char *p, float *v);

extern float mat_fast_helper_a(float a, float b);

extern void euler_to_matrix(float *matrix, float *quat);

extern void draw_world_quad(char *pkt, float *matrix, int mode);

extern int func_001163B0(void);

extern int g_effect_quad_color __attribute__((sda));

extern int g_joba_quad_color_base __attribute__((sda));

/* The vector the aim helpers read, at 0x001BA780 in joba. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L11AimVector;

extern L11AimVector g_hero_l11_state_block;

extern void *g_ring_effect_sprite __attribute__((sda));

extern void *g_ring_l11_effect_color __attribute__((sda));

extern float g_ring_effect_size __attribute__((sda));

extern void *g_shot_smoke_sprite_a __attribute__((sda));

extern void *g_shot_smoke_sprite_b __attribute__((sda));

extern float g_shot_smoke_size __attribute__((sda));

extern float g_shot_smoke_random_scale __attribute__((sda));

extern float g_effect_offset_angle __attribute__((sda));

/* The level's script gate, read through $gp. */
extern s32 g_hero_l11_input_blocked __attribute__((sda));

/* The shared table of the level's live projectiles. */
extern char g_sound_state[];

/* The aiming target the level's spot checks measure against. */
extern char g_hero_l11_position[];

extern int FloatToInt(float);

extern void moby_set_state(void *, int, int);

extern void moby_set_controller_speed_limits(void *, float, float, float, float);

extern void get_moby_color(void *, void *, void *, void *);

extern void moby_update_ground_check(void *);

extern float moby_update_aim_target_strength(void *, void *);

extern void *part_find_owned_effect_slot(void *, unsigned int, int);

extern float fast_vec_dist(void *, void *);

extern int snd_is_voice_playing_for_owner(void *, int);

extern void snd_stop_voice(int);

extern int PlayMobySound(int, int, char *);

extern void matrix_from_basis_rows(void *, void *);

extern void cam_compute_view_direction(void *, void *, int);

extern void gfx_start_color_fade(void *, void *);

extern void vec_random_direction(void *, float, float);

extern void FastVecSub(void *, void *, void *);

extern float FastVecDot(void *, void *);

extern float FastVecLength(void *);


extern float FastAddRotations(float, float);

extern float func_L00_002EE290(void *);

extern void drone_update_lock_on(char *);

extern void drone_reset_to_idle(char *);

extern u8 *arena_get_center_point(u8 *);

extern int arena_is_point_in_inner_zone(u8 *, u8 *);


extern float math_random_signed_float_range(float, float);

extern int math_random_int_below(int);

extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

extern void vec_build_spherical_offset(void *, float, float, float);

extern char *part_spawn_ground_effect(void *, int, int, float, float, float, int, int, void *, int);

extern void *part_spawn_spinning_particle(void *, void *, int, int, float, float, int, int, int, int, int);

extern float g_smoke_spray_speed_min __attribute__((sda));
extern float g_smoke_spray_speed_max __attribute__((sda));
extern float g_smoke_spray_rise_min __attribute__((sda));
extern float g_smoke_spray_rise_max __attribute__((sda));
extern float g_ground_effect_param __attribute__((sda));
extern float g_effect_size_min __attribute__((sda));
extern float g_effect_size_max __attribute__((sda));
extern int g_ground_effect_kind_a __attribute__((sda));
extern int g_ground_effect_kind_b __attribute__((sda));

/* Sprays smoke puffs and a few sparks out of a point, thrown toward the level's aim target. The mode picks the smaller puffs. */
void part_spray_smoke_and_sparks(float *center, int count, int mode)
{
    float vel[4], pos[4], axis[4], up[4], a[4], b[4], out[4];
    int i, j, sign;
    char *effect;
    float size, speed, angle, heading;

    FastVecSub(axis, g_hero_l11_position, center);
    axis[2] = 0;
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    up[3] = 1;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(g_effect_size_min, g_effect_size_max);
        sign = math_random_int_below(2);
        if (!sign)
            --sign;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(vel, axis, up, angle);
        speed = math_random_float_range(g_smoke_spray_speed_min, g_smoke_spray_speed_max) * (1.0f / 60.0f);
        vec_scale_to_length((char *)vel, vel, speed);
        vel[2] = math_random_float_range(g_smoke_spray_rise_min, g_smoke_spray_rise_max) * (1.0f / 60.0f);
        qcopy(pos, center);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        if (!mode) {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 60, g_ground_effect_kind_a, size * 0.35f, size, g_ground_effect_param, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 60, g_ground_effect_kind_b, size * 0.245f, size * 0.7f, g_ground_effect_param, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, g_hero_l11_position, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = part_spawn_ground_effect(pos, 40, g_ground_effect_kind_a, size * 2.05f, size, g_ground_effect_param, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 40, g_ground_effect_kind_b, size * 1.4350000619888306f, size * 0.7f, g_ground_effect_param, 1, -sign, vel, 0);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 60, g_ground_effect_kind_a, size * 0.3f, size, g_ground_effect_param, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 60, g_ground_effect_kind_b, size * (0.3f * 0.7f), size * 0.7f, g_ground_effect_param, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, g_hero_l11_position, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = part_spawn_ground_effect(pos, 40, g_ground_effect_kind_a, size * 0.25f, size, g_ground_effect_param, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 40, g_ground_effect_kind_b, size * 0.175f, size * 0.7f, g_ground_effect_param, 1, -sign, vel, 0);
            }
        }
        if (effect)
            effect[9] = FloatToInt(4.0f) + 112;
    }
    for (j = 1; j >= 0; j--) {
        angle = math_random_float_range(-0.9599312f, -1.3962636f);
        heading = math_random_angle();
        vec_build_spherical_offset(a, math_random_float_range(0, 0.5f) * (1.0f / 60.0f), heading, angle);
        FastVecSub(b, g_hero_l11_position, center);
        vec_scale_to_length((char *)b, b, 0.15f);
        FastVecAdd(center, center, b);
        size = math_random_float_range(30000, 60000);
        out[0] = center[0] + math_random_signed_float_range(0, 0.15f);
        out[1] = center[1] + math_random_signed_float_range(0, 0.15f);
        out[2] = center[2] + math_random_signed_float_range(0, 0.15f);
        if (mode)
            part_spawn_spinning_particle(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(10, 20), 1, -1, -1, 0);
        else
            part_spawn_spinning_particle(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(25, 60), 1, -1, -1, 0);
    }
}

/* Rebuilds the state's offset block from its rotation and installs the next handler. */
void joba_effect_prepare_offsets(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float rotation[4];

    vec_scale_to_length((char *)rotation, vars + 0x40, 1.0f);
    math_build_axis_angle_quat(rotation, rotation, *(float *)(vars + 0x30));
    FastVecScale(vars + 0x10, vars, *(float *)(vars + 0x60));
    vec_rotate_by_quaternion(vars + 0x10, vars + 0x10, rotation);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    FastVecAdd(vars + 0x10, moby + 0x10, vars + 0x10);
    FastVecAdd(vars + 0x20, moby + 0x10, vars + 0x20);
    *(float *)(vars + 0x30) = fast_subtract_rotations(*(float *)(vars + 0x30),
                                         g_effect_offset_angle * 0.000290888245f);
    gfx_add_draw_callback_first(joba_effect_update_particles, moby);
}

/* Aims the object's stage at the level's aim vector and dispatches the resulting packet. */
void joba_effect_spawn_quad(char *moby)
{
    char pkt[144];
    float matrix[16];
    float quat[4];
    float point[4];
    char *vars = *(char **)(moby + 0x68);
    float scale;
    int parity;
    int alpha_shift;

    gfx_init_square_packet(pkt);
    lerp_vector(point, vars + 0x10, vars + 0x20, math_random_float_range(0.0f, 1.0f));

    point[0] += math_random_float_range(-0.1f, 0.1f) * *(float *)(vars + 0x60);
    point[1] += math_random_float_range(-0.1f, 0.1f) * *(float *)(vars + 0x60);
    point[2] += math_random_float_range(-0.1f, 0.1f) * *(float *)(vars + 0x60);

    *(long long *)(pkt + 120) = GetEffectTextureDescriptor((char *)0xB);
    *(long long *)(pkt + 128) = 0x0000FF9000000260LL;
    *(long long *)(pkt + 112) = 0LL;

    parity = func_001163B0();
    *(long long *)(pkt + 136) = ((long long)((parity % 2) + 1) << 2) | 0x8000000040LL;
    alpha_shift = math_random_int_range(0x40, 0x7F) << 24;
    *(int *)(pkt + 76) = (g_effect_quad_color & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 72) = (g_effect_quad_color & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 68) = (g_effect_quad_color & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 64) = (g_effect_quad_color & 0xFFFFFF) + alpha_shift;

    quat[3] = 0.0f;
    quat[2] = mat_fast_helper_a(g_hero_l11_state_block.x_140 - point[0], g_hero_l11_state_block.y_144 - point[1]);
    quat[1] = -mat_fast_helper_a(vec_distance_xy((char *)point, &g_hero_l11_state_block.x_140),
                             g_hero_l11_state_block.z_148 - point[2]);
    quat[0] = math_random_angle();
    euler_to_matrix(matrix, quat);

    matrix[12] = point[0];
    matrix[13] = point[1];
    matrix[14] = point[2];
    matrix[15] = 1.0f;

    scale = math_random_float_range(0.05f, 0.15f) * *(float *)(vars + 0x60);
    FastVecScale(pkt, pkt, scale);
    FastVecScale(pkt + 16, pkt + 16, scale);
    FastVecScale(pkt + 32, pkt + 32, scale);
    FastVecScale(pkt + 48, pkt + 48, scale);
    draw_world_quad(pkt, matrix, 0);

    *(int *)(pkt + 76) = (g_joba_quad_color_base & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 72) = (g_joba_quad_color_base & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 68) = (g_joba_quad_color_base & 0xFFFFFF) + alpha_shift;
    *(int *)(pkt + 64) = (g_joba_quad_color_base & 0xFFFFFF) + alpha_shift;

    FastVecScale(pkt, pkt, 0.5f);
    FastVecScale(pkt + 16, pkt + 16, 0.5f);
    FastVecScale(pkt + 32, pkt + 32, 0.5f);
    FastVecScale(pkt + 48, pkt + 48, 0.5f);
    draw_world_quad(pkt, matrix, 0);

    part_spawn_random_spark_beam(moby, point);
}

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void drone_launcher_update_state(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float vec0[4];
    float vec1[4];
    float vec2[4];
    float damage;
    float dot;
    float len;
    int slot;
    char *hit;
    char *entry;
    u8 *other;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x18) = (int)(vars + 0x60);
        *(float *)(moby + 0x2C) *= 0.75f;
        *(int *)(vars + 0x1DC) = -1;
        *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(12.0f);
        *(float *)(vars + 0x1D0) =
            math_random_float_range(-*(float *)(vars + 0x1D0), *(float *)(vars + 0x1D0)) *
            0.01745329424738884f;
        *(u8 *)(moby + 0x30) = 0x80;
        *(int *)(vars + 0x1D4) = 1;
        *(float *)(vars + 0x1D8) *= 0.01666666753590107f;
        moby_set_controller_speed_limits(moby, 0.02777777798473835f, 1.6666667461395264f,
                      0.0011635529808700085f, 0.10471977293491364f);
        *(int *)(vars + 0x98) |= 4;
        *(float *)(vars + 0x60) = 0.75f;
        *(float *)(vars + 0x68) = 0.75f;
        *(int *)(vars + 0x64) = 0;
        *(float *)(vars + 0x6C) = 0.5f;
        *(float *)(vars + 0x70) = 1.134464144706726f;
        *(float *)(vars + 0x90) = 0.523598849773407f;
        *(float *)(vars + 0x8C) = 0.0027777778450399637f;
        get_moby_color(moby, vars + 0x1F0, vars + 0x1F4, vars + 0x1F8);
        *(u8 *)(vars + 0x28) = 3;
        *(int *)(vars + 0x30) = 0;
        *(short *)(vars + 0x1EC) = 0;
        drone_reset_to_idle(moby);
    }
    if (*(short *)(vars + 0x1FC) == 0 && *(u8 *)(moby + 0x20) != 0xE &&
        g_hero_l11_input_blocked == 0) {
        *(u16 *)(moby + 0x34) |= 0x400;
        if (*(u8 *)(moby + 0x31) != 0) {
            if (fast_vec_dist(moby + 0x10, g_hero_l11_position) < 24.0f) {
                moby_update_ground_check(moby);
                *(u8 *)(moby + 0x6F) = 0x16;
            }
        }
    } else {
        *(u16 *)(moby + 0x34) &= 0xFBFF;
    }
    if (*(u8 *)(moby + 0x95) >= 2) {
        if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x1DC)) == 0)
            *(int *)(vars + 0x1DC) = PlayMobySound(1, 4, moby);
    } else {
        if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x1DC))) {
            slot = *(int *)(vars + 0x1DC);
            if (slot != -1) {
                entry = g_sound_state + slot * 0x70;
                if (*(char **)(entry + 0x88) == moby && *(u8 *)(entry + 0x74) != 0)
                    snd_stop_voice(slot);
            }
            *(int *)(vars + 0x1DC) = -1;
        }
    }
    if (*(short *)(vars + 0x1FC) != 0)
        *(int *)(vars + 0x98) &= ~0x10;
    else
        *(int *)(vars + 0x98) |= 0x10;
    hit = (char *)part_find_owned_effect_slot(moby, 0x10000, 0);
    if (hit != 0) {
        other = *(u8 **)(hit + 0x20);
        if (other != 0) {
            if (*(short *)(other + 0xAA) == 0xA03 /* moby class 2563 */)
                *(int *)(hit + 0x2C) = 0;
            else if (*(u8 *)(moby + 0x31) == 0 && *(short *)(other + 0xAA) == 0xB89 /* moby class 2953 */)
                *(int *)(hit + 0x2C) = 0;
        }
    }
    damage = moby_update_aim_target_strength(moby, hit);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) -= damage;
    if (damage != 0.0f) {
        if (*(u8 *)(moby + 0x20) != 3 && *(u8 *)(moby + 0x20) != 0xE) {
            vec_scale_to_length((char *)vec0, hit + 0x10, 0.8333333730697632f);
            vec_random_direction(vec1, -0.1388888955116272f, 0.1388888955116272f);
            FastVecAdd(vec0, vec0, vec1);
            if (*(short *)(vars + 0x1FC) == 0) {
                vec0[2] = math_random_float_range(0.0f, 0.0f) * 0.00027777778450399637f;
                vec0[3] = 5627.9248046875f;
            } else {
                FastVecSub(vec2, arena_get_center_point(*(u8 **)(moby + 0xB8)),
                              moby + 0x10);
                vec2[2] = 0.0f;
                vec_scale_to_length((char *)vec2, vec2, 1.0f);
                dot = FastVecDot(vec0, vec2);
                if (dot < 0.0f) {
                    vec_scale_to_length((char *)vec2, vec2, dot);
                    len = FastVecLength(vec0);
                    FastVecSub(vec0, vec0, vec2);
                    vec_scale_to_length((char *)vec0, vec0, len);
                }
            }
            FastVecAdd(vars + 0x100, vars + 0x100, vec0);
            vec_random_direction(vec1, 0.0017453294713050127f, 0.006981317885220051f);
            *(float *)(vars + 0x1B0) = FastAddRotations(*(float *)(vars + 0x1B0), vec1[0]);
            *(float *)(vars + 0x1B4) = FastAddRotations(*(float *)(vars + 0x1B4), vec1[1]);
            *(float *)(vars + 0x1B8) = FastAddRotations(*(float *)(vars + 0x1B8), vec1[2]);
            gfx_start_color_fade(moby, vars + 0x50);
            moby_set_state(moby, 0xD, 4);
        }
    }
    if (*(short *)(vars + 0x1FC) != 0) {
        matrix_from_basis_rows(vars + 0x170, moby + 0xC0);
        cam_compute_view_direction(moby + 0x10, vars + 0x1A0, 0);
        if (arena_is_point_in_inner_zone(*(u8 **)(moby + 0xB8), (u8 *)(moby + 0x10)) == 0) {
            *(int *)(vars + 0x20) = 0;
            moby_set_state(moby, 0xE, 4);
        }
        if (*(u8 *)(moby + 0x20) != 0xE) {
            len = *(float *)(moby + 0x18);
            other = arena_get_center_point(*(u8 **)(moby + 0xB8));
            FastVecSub(vec0, moby + 0x10, other);
            vec0[2] = 0.0f;
            if (func_L00_002EE290(vec0) > 225.0f) {
                vec_scale_to_length((char *)vec0, vec0, 15.0f);
                other = arena_get_center_point(*(u8 **)(moby + 0xB8));
                FastVecAdd(moby + 0x10, vec0, other);
                *(float *)(moby + 0x18) = len;
            }
        }
    }
    if (*(u8 *)(moby + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2)
        drone_reset_to_idle(moby);
    drone_update_lock_on(moby);
}

extern unsigned short g_joba_shot_lifetime __attribute__((sda));
extern float mat_fast_helper_a(float a, float b);
extern void func_002A0F48(char *p);

/* Initialises a spawned object: clears its state flags, copies the two start vectors and the
   caller's parameters into the object and its state block, and aims it along the first vector. */
void joba_shot_init(char *moby, int owner, int controller, int goal_object, float gravity, float damage, void *start_pos,
                       float *velocity, int fade_time)
{
    char *vars = *(char **)(moby + 0x68);

    int flags_word;

    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    flags_word = *(int *)(*(char **)(moby + 0x24) + 0x10);
    *(unsigned short *)(moby + 0x34) &= 0xEFFF;
    *(int *)(moby + 0x98) = flags_word;
    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(unsigned short *)(moby + 0x32) = 0xFF;
    moby[0x20] = 2;
    *(int *)(vars + 0x15C) = owner;
    *(int *)(moby + 0xB8) = controller;
    qcopy(moby + 0x10, start_pos);
    qcopy(vars + 0xC0, velocity);
    *(unsigned short *)(vars + 0x16C) = g_joba_shot_lifetime;
    *(int *)(vars + 0x150) = fade_time;
    *(float *)(vars + 0x4C) = gravity;
    *(unsigned short *)(vars + 0x16E) = 0;
    *(int *)(moby + 0xF0) = 0;
    *(int *)(moby + 0xF4) = 0;
    *(float *)(moby + 0xF8) = mat_fast_helper_a(velocity[0], velocity[1]);
    *(float *)(vars + 0x158) = damage;
    func_002A0F48(moby);
    *(int *)(vars + 0x164) = goal_object;
    *(int *)(moby + 0x78) = 0xFF84E643;
}

extern char *CreateMoby(int);
extern void part_l11_spawn_spark_ring(void *, int);
extern float g_swirl_effect_scale __attribute__((sda));
extern int g_swirl_effect_arg __attribute__((sda));
extern int snd_play_from_class_bank(int, int, char *, int);
