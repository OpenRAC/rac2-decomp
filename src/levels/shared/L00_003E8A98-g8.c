#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern float g_charge_weapon_effect_table[4][32];
extern float g_plasma_coil_beam_points[5][4];
extern float g_plasma_coil_anchor[4] MACRO_ADDR;
extern float g_plasma_coil_angle_a __attribute__((sda));
extern float g_plasma_coil_angle_b __attribute__((sda));
extern float g_charge_min __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void part_update_wave_offsets(int, float *, int);
extern void get_moby_joint_matrices(void *, int, int *, void *);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float), FastAddRotations(float, float);
extern void transform_vector(void *, void *, void *);
extern void moby_get_attachment_point(char *, int, char *, char *);
extern void part_spawn_random_effect(int, int, int, int, float);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern void gfx_draw_lightning_arc(void *, void *, void *, void *);
extern void vec_compute_arc_side_direction(char *, void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int func_001163B0(void);
extern void part_spawn_sparks(void *, int, float);
extern void moby_transform_joint_to_world(char *, int, char *);

/* Transform the weapon's animated attachment points and draw its beam network. */
/* Draws the Plasma Coil's lightning arcs and glows between its moving parts. */
void plasma_coil_draw_beams(void *object)
{
    float points[5][4], attachments[5][4], matrix[4][4];
    float normal[4], side[4], endpoint[4], muzzle[4];
    char *moby = object;
    char *state;
    int lookup, i;
    float *first;
    VU1_addGSregister(0x47, 0x53001ULL);
    state = *(char **)(moby + 0x68);
    part_update_wave_offsets((int)moby, g_charge_weapon_effect_table[0], 4);
    lookup = 0;
    get_moby_joint_matrices(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    g_plasma_coil_beam_points[1][0] = -math_fast_sin_or_cos_a(g_plasma_coil_angle_b) * 0.0151f;
    g_plasma_coil_beam_points[1][2] = math_fast_sin_or_cos_a(g_plasma_coil_angle_a) * 0.0149f;
    g_plasma_coil_beam_points[1][1] = -(math_fast_sin_or_cos_b(g_plasma_coil_angle_a) * 0.015f + 0.4f);
    g_plasma_coil_angle_a = FastAddRotations(g_plasma_coil_angle_a, 0.4188790917f);
    g_plasma_coil_angle_b = FastAddRotations(g_plasma_coil_angle_b, 0.4130613208f);
    {
        float *src = g_plasma_coil_beam_points[0], *dst;
        first = attachments[0];
        dst = first;
        for (i = 0; i < 5; i++) {
            transform_vector(dst, src, matrix);
            src += 4;
            dst += 4;
        }
    }
    moby_get_attachment_point(moby, 0, (char *)points[0], (char *)first);
    part_spawn_random_effect((int)moby, (int)points[0], 0x7F7F2020, 0x40, 0.11f);
    part_spawn_random_effect((int)moby, (int)points[0], 0x7FFF4040, 0x78, 0.05f);
    moby_get_attachment_point(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (g_plasma_coil_anchor[3] == -1.0f) {
        qcopy(g_plasma_coil_anchor, points[1]);
        g_plasma_coil_anchor[3] = 0.0f;
    } else {
        int changed = 0;
        vec_spring_to_target(g_plasma_coil_anchor, points[1], &changed, 0.25f, 0.2000000179f, 0.5f);
    }
    part_spawn_random_effect((int)moby, (int)g_plasma_coil_anchor, 0x7F00397F, 0x40, 2.0f * *(float *)(state + 0x10) * 0.082499996f);
    part_spawn_random_effect((int)moby, (int)g_plasma_coil_anchor, 0x7F0072FF, 0x78, 2.0f * *(float *)(state + 0x10) * 0.0375f);
    moby_get_attachment_point(moby, 1, (char *)points[2], (char *)attachments[2]);
    part_spawn_random_effect((int)moby, (int)points[2], 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)points[2], 0x7FFF4040, 0x78, 0.025f);
    moby_get_attachment_point(moby, 2, (char *)points[3], (char *)attachments[3]);
    part_spawn_random_effect((int)moby, (int)points[3], 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)points[3], 0x7FFF4040, 0x78, 0.025f);
    moby_get_attachment_point(moby, 3, (char *)points[4], (char *)attachments[4]);
    part_spawn_random_effect((int)moby, (int)points[4], 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)points[4], 0x7FFF4040, 0x78, 0.025f);
    gfx_draw_lightning_arc(moby, points[0], g_plasma_coil_anchor, g_charge_weapon_effect_table[0]);
    vec_compute_arc_side_direction(moby, g_plasma_coil_anchor, normal, *(float *)(state + 0x10) * 0.35f);
    FastVecSub(side, g_plasma_coil_anchor, points[2]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0x10) * 0.45f);
    FastVecAdd(endpoint, side, g_plasma_coil_anchor);
    gfx_draw_lightning_arc(moby, points[2], endpoint, g_charge_weapon_effect_table[1]);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > g_charge_min)
        part_spawn_sparks(endpoint, 1, 0.0f);
    FastVecSub(side, g_plasma_coil_anchor, points[3]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0x10) * 0.45f);
    FastVecAdd(endpoint, side, g_plasma_coil_anchor);
    gfx_draw_lightning_arc(moby, points[3], endpoint, g_charge_weapon_effect_table[2]);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > g_charge_min)
        part_spawn_sparks(endpoint, 1, 0.0f);
    FastVecSub(side, g_plasma_coil_anchor, points[4]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0x10) * 0.45f);
    FastVecAdd(endpoint, side, g_plasma_coil_anchor);
    gfx_draw_lightning_arc(moby, points[4], endpoint, g_charge_weapon_effect_table[3]);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > g_charge_min)
        part_spawn_sparks(endpoint, 1, 0.0f);
    moby_transform_joint_to_world(moby, 1, (char *)muzzle);
    gfx_draw_lightning_arc(moby, muzzle, points[2], g_charge_weapon_effect_table[3]);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    moby_transform_joint_to_world(moby, 2, (char *)muzzle);
    gfx_draw_lightning_arc(moby, muzzle, points[3], g_charge_weapon_effect_table[2]);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    moby_transform_joint_to_world(moby, 3, (char *)muzzle);
    gfx_draw_lightning_arc(moby, muzzle, points[4], g_charge_weapon_effect_table[1]);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    part_spawn_random_effect((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0) {
        int selected = func_001163B0();
        selected %= 4;
        part_spawn_sparks(points[selected + 1], 1, 0.001f);
    }
    VU1_addGSregister(0x47, 0x5360BULL);
}
