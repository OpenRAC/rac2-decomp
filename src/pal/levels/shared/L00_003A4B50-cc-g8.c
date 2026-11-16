#include "names.h"
/* func_PAL_L00_003A4B50, the PAL copy of func_L00_003A1580: the same C, where rename func_L00_003A2C60 becomes func_PAL_L00_003A6238. */
#include "common.h"
extern float g_beam_oscillator_table[4][32];
extern float g_beam_network_attachment_points[5][4];
extern float g_beam_network_anchor[4] MACRO_ADDR;
extern float g_beam_network_phase_a __attribute__((sda));
extern float g_beam_network_phase_b __attribute__((sda));
extern float g_charge_minimum __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void beam_update_wobble_points(int, float *, int);
extern void get_moby_joint_matrices(void *, int, int *, void *);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float), FastAddRotations(float, float);
extern void transform_vector(void *, void *, void *);
extern void weapon_get_attachment_world_pos(char *, int, char *, char *);
extern void beam_spawn_flare(int, int, int, int, float);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern void beam_draw_jittered_curve(void *, void *, void *, void *);
extern void vec_compute_ring_normal(char *, void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int func_001163B0(void);
extern void func_PAL_L00_003A6238(void *, int, float);
extern void moby_transform_joint_to_world(char *, int, char *);

/* Transform the weapon's animated attachment points and draw its beam network. */
void func_PAL_L00_003A4B50(void *object)
{
    float points[5][4], attachments[5][4], matrix[4][4];
    float normal[4], side[4], endpoint[4], muzzle[4];
    char *moby = object;
    char *state = 0;
    int lookup, i;
    int attachment_count = 5, inner = 0x40, outer = 0x78, channel = 0x47, spark_count = 1;
    VU1_addGSregister(channel, 0x53001ULL);
    state = *(char **)(moby + 0x68);
    beam_update_wobble_points((int)moby, g_beam_oscillator_table[0], 4);
    lookup = 0;
    get_moby_joint_matrices(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    g_beam_network_attachment_points[1][0] = math_fast_sin_or_cos_b(g_beam_network_phase_a) * 0.015f + 0.4f;
    g_beam_network_attachment_points[1][2] = math_fast_sin_or_cos_a(g_beam_network_phase_a) * 0.0149f;
    g_beam_network_attachment_points[1][1] = -math_fast_sin_or_cos_a(g_beam_network_phase_b) * 0.0151f;
    g_beam_network_phase_a = FastAddRotations(g_beam_network_phase_a, 0.5026549f);
    g_beam_network_phase_b = FastAddRotations(g_beam_network_phase_b, 0.4956736f);
    for (i = 0; i < attachment_count; i++)
        transform_vector(attachments[i], g_beam_network_attachment_points[i], matrix);
    weapon_get_attachment_world_pos(moby, 0, (char *)points[0], (char *)attachments[0]);
    beam_spawn_flare((int)moby, (int)points[0], 0x7F7F2020, inner, 0.11f);
    beam_spawn_flare((int)moby, (int)points[0], 0x7FFF4040, outer, 0.05f);
    weapon_get_attachment_world_pos(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (g_beam_network_anchor[3] == -1.0f) {
        qcopy(g_beam_network_anchor, points[1]);
        g_beam_network_anchor[3] = 0.0f;
    } else {
        int changed = 0;
        vec_spring_to_target(g_beam_network_anchor, points[1], &changed, 0.3f, 0.24000001f, 0.6f);
    }
    beam_spawn_flare((int)moby, (int)g_beam_network_anchor, 0x7F00397F, inner, *(float *)(state + 0xC) * 0.1856249869f);
    beam_spawn_flare((int)moby, (int)g_beam_network_anchor, 0x7F0072FF, outer, *(float *)(state + 0xC) * 0.08437500149f);
    weapon_get_attachment_world_pos(moby, 1, (char *)points[2], (char *)attachments[2]);
    beam_spawn_flare((int)moby, (int)points[2], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[2], 0x7FFF4040, outer, 0.025f);
    weapon_get_attachment_world_pos(moby, 2, (char *)points[3], (char *)attachments[3]);
    beam_spawn_flare((int)moby, (int)points[3], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[3], 0x7FFF4040, outer, 0.025f);
    weapon_get_attachment_world_pos(moby, 3, (char *)points[4], (char *)attachments[4]);
    beam_spawn_flare((int)moby, (int)points[4], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[4], 0x7FFF4040, outer, 0.025f);
    beam_draw_jittered_curve(moby, points[0], g_beam_network_anchor, g_beam_oscillator_table[0]);
    vec_compute_ring_normal(moby, g_beam_network_anchor, normal, *(float *)(state + 0xC) * 0.35f);
    FastVecSub(side, g_beam_network_anchor, points[2]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, g_beam_network_anchor);
    beam_draw_jittered_curve(moby, points[2], endpoint, g_beam_oscillator_table[1]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > g_charge_minimum)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    FastVecSub(side, g_beam_network_anchor, points[3]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, g_beam_network_anchor);
    beam_draw_jittered_curve(moby, points[3], endpoint, g_beam_oscillator_table[2]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > g_charge_minimum)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    FastVecSub(side, g_beam_network_anchor, points[4]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, g_beam_network_anchor);
    beam_draw_jittered_curve(moby, points[4], endpoint, g_beam_oscillator_table[3]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > g_charge_minimum)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    moby_transform_joint_to_world(moby, 1, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[2], g_beam_oscillator_table[3]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    moby_transform_joint_to_world(moby, 2, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[3], g_beam_oscillator_table[2]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    moby_transform_joint_to_world(moby, 3, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[4], g_beam_oscillator_table[1]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0) {
        int selected = func_001163B0();
        selected %= 4;
        func_PAL_L00_003A6238(points[selected + 1], spark_count, 0.001f);
    }
    VU1_addGSregister(channel, 0x5360BULL);
}
