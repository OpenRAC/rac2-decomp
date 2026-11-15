/* func_PAL_L00_003A4B50, the PAL copy of func_L00_003A1580: the same C, where rename func_L00_003A2C60 becomes func_PAL_L00_003A6238. */
#include "common.h"
extern float D_L00_0023B510[4][32];
extern float D_L00_002947B0[5][4];
extern float D_L00_001B2850[4] MACRO_ADDR;
extern float D_L00_001AF5F0 __attribute__((sda));
extern float D_L00_001AF5F4 __attribute__((sda));
extern float D_L00_001AF5D8 __attribute__((sda));
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
    beam_update_wobble_points((int)moby, D_L00_0023B510[0], 4);
    lookup = 0;
    get_moby_joint_matrices(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    D_L00_002947B0[1][0] = math_fast_sin_or_cos_b(D_L00_001AF5F0) * 0.015f + 0.4f;
    D_L00_002947B0[1][2] = math_fast_sin_or_cos_a(D_L00_001AF5F0) * 0.0149f;
    D_L00_002947B0[1][1] = -math_fast_sin_or_cos_a(D_L00_001AF5F4) * 0.0151f;
    D_L00_001AF5F0 = FastAddRotations(D_L00_001AF5F0, 0.5026549f);
    D_L00_001AF5F4 = FastAddRotations(D_L00_001AF5F4, 0.4956736f);
    for (i = 0; i < attachment_count; i++)
        transform_vector(attachments[i], D_L00_002947B0[i], matrix);
    weapon_get_attachment_world_pos(moby, 0, (char *)points[0], (char *)attachments[0]);
    beam_spawn_flare((int)moby, (int)points[0], 0x7F7F2020, inner, 0.11f);
    beam_spawn_flare((int)moby, (int)points[0], 0x7FFF4040, outer, 0.05f);
    weapon_get_attachment_world_pos(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (D_L00_001B2850[3] == -1.0f) {
        qcopy(D_L00_001B2850, points[1]);
        D_L00_001B2850[3] = 0.0f;
    } else {
        int changed = 0;
        vec_spring_to_target(D_L00_001B2850, points[1], &changed, 0.3f, 0.24000001f, 0.6f);
    }
    beam_spawn_flare((int)moby, (int)D_L00_001B2850, 0x7F00397F, inner, *(float *)(state + 0xC) * 0.1856249869f);
    beam_spawn_flare((int)moby, (int)D_L00_001B2850, 0x7F0072FF, outer, *(float *)(state + 0xC) * 0.08437500149f);
    weapon_get_attachment_world_pos(moby, 1, (char *)points[2], (char *)attachments[2]);
    beam_spawn_flare((int)moby, (int)points[2], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[2], 0x7FFF4040, outer, 0.025f);
    weapon_get_attachment_world_pos(moby, 2, (char *)points[3], (char *)attachments[3]);
    beam_spawn_flare((int)moby, (int)points[3], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[3], 0x7FFF4040, outer, 0.025f);
    weapon_get_attachment_world_pos(moby, 3, (char *)points[4], (char *)attachments[4]);
    beam_spawn_flare((int)moby, (int)points[4], 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)points[4], 0x7FFF4040, outer, 0.025f);
    beam_draw_jittered_curve(moby, points[0], D_L00_001B2850, D_L00_0023B510[0]);
    vec_compute_ring_normal(moby, D_L00_001B2850, normal, *(float *)(state + 0xC) * 0.35f);
    FastVecSub(side, D_L00_001B2850, points[2]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    beam_draw_jittered_curve(moby, points[2], endpoint, D_L00_0023B510[1]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    FastVecSub(side, D_L00_001B2850, points[3]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    beam_draw_jittered_curve(moby, points[3], endpoint, D_L00_0023B510[2]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    FastVecSub(side, D_L00_001B2850, points[4]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    beam_draw_jittered_curve(moby, points[4], endpoint, D_L00_0023B510[3]);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_PAL_L00_003A6238(endpoint, spark_count, 0.0f);
    moby_transform_joint_to_world(moby, 1, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[2], D_L00_0023B510[3]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    moby_transform_joint_to_world(moby, 2, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[3], D_L00_0023B510[2]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    moby_transform_joint_to_world(moby, 3, (char *)muzzle);
    beam_draw_jittered_curve(moby, muzzle, points[4], D_L00_0023B510[1]);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    beam_spawn_flare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    if (func_001163B0() % 11 == 0) {
        int selected = func_001163B0();
        selected %= 4;
        func_PAL_L00_003A6238(points[selected + 1], spark_count, 0.001f);
    }
    VU1_addGSregister(channel, 0x5360BULL);
}
