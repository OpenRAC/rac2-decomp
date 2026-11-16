#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern float g_look_rate_scale_a __attribute__((sda));
extern float g_look_sensitivity_a __attribute__((sda));

int hero_get_camera_params_pal(float *a0, float *a1, float *a2)
{
    char *p = g_hero_state;
    int v = *(int *)(p + 8852);

    if (v >= 98 && v <= 100) {
        if (a0) *a0 = *(float *)(p + 6316);
        if (a1) *a1 = g_look_rate_scale_a * 6.981318e-06f;
        if (a2) *a2 = g_look_sensitivity_a * 0.0003490659f;
        return 1;
    }
    if (v == 17) {
        if (a0) *a0 = *(float *)(p + 152);
        if (a1) *a1 = g_look_rate_scale_a * 2.0943955e-05f;
        if (a2) *a2 = g_look_sensitivity_a * 0.0010471977f;
        return 1;
    }
    return 0;
}

extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern char g_camera_l00_position[];
extern char g_camera_state_block[];

void hero_update_camera_block_pal(void) {
    char *player = g_hero_state;
    char *camera;
    float target;
    if (*(float *)(player + 0x151C) == 0.0f) *(float *)(player + 0x151C) = 1.5f;
    target = 1.5f;
    if (*(int *)(player + 0x2294) == 4) target = 0.75f;
    math_step_value_toward_target(player + 0x151C, player + 0x1520, target, 0.0064000003f, 0.0064000003f, 0.64000005f);
    vec_scale_to_length(player + 0x14D0, player + 0x20, *(float *)(player + 0x151C));
    FastVecAdd(player + 0x14D0, player + 0x14D0, player + 0x80);
    if (*(int *)(player + 0x229C) == 25 || *(int *)(player + 0x2294) == 102) {
        float height = *(float *)(player + 0x334) + 0.75f;
        if (*(float *)(player + 0x14D8) < height) *(float *)(player + 0x14D8) = height;
    }
    camera = g_camera_l00_position;
    qcopy(camera, g_camera_state_block);
    qcopy(camera + 0x230, g_camera_state_block + 0x10);
    FastVecCross(camera + 0x240, camera + 0x230, g_camera_state_block - 0x14B0);
    vec_scale_to_length(camera + 0x240, camera + 0x240, 1.0f);
    FastVecCross(camera + 0x250, camera + 0x240, camera + 0x230);
    vec_scale_to_length(camera + 0x250, camera + 0x250, 1.0f);
}
