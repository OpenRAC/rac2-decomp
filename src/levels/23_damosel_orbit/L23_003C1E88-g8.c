/* Update the oscillating effect parameter and submit a complete 144-byte quad packet.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA18 __attribute__((sda));
extern float D_L23_001AFA1C __attribute__((sda));
extern float D_L23_001AFA20 __attribute__((sda));
extern int D_L23_001AFA24 __attribute__((sda));
extern int D_L23_001AFA28 __attribute__((sda));
extern int D_L23_001AFA2C __attribute__((sda));
extern int D_L23_001AFA30 __attribute__((sda));
extern int D_L23_001AFA34 __attribute__((sda));
extern int D_L23_001AFA38 __attribute__((sda));
extern float D_L23_001AFA3C __attribute__((sda));
extern float D_L23_001AFA40 __attribute__((sda));
extern float D_L23_001AFA44 __attribute__((sda));
extern int D_L23_001AFA48 __attribute__((sda));

extern char g_camera_l23_position[];

extern float math_random_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern u64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(u32, u64);
extern void draw_world_quad(void *, int, int);

/* Makes the beam strength swing up and down, then draws a glowing beam strip between the enemy and its helper object. */
void gfx_draw_pulsing_beam(char *moby) {
    TI128 pull_back;
    TI128 sideways;
    TI128 to_camera;
    TI128 forward;
    TI128 end_point;
    TI128 start_point;
    char packet[0x90] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    TI128 *start_ptr;
    TI128 *forward_ptr;
    char *moby_pos;
    char *moby_forward;
    float width;
    float level;
    float limit;
    u64 tex_bits;
    int color;
    float zero;
    long long gif_bits;

    if (*(short *)(vars + 0x3BC) > 0) {
        level = *(float *)(vars + 0x3B8) + math_random_float_range(D_L23_001AFA40, D_L23_001AFA44);
        limit = D_L23_001AFA3C;
        *(float *)(vars + 0x3B8) = level;
        if (limit < level) {
            *(float *)(vars + 0x3B8) = limit;
            *(short *)(vars + 0x3BC) = -1;
        }
    } else {
        level = *(float *)(vars + 0x3B8) - math_random_float_range(D_L23_001AFA40, D_L23_001AFA44);
        limit = (float)D_L23_001AFA38;
        *(float *)(vars + 0x3B8) = level;
        if (level < limit) {
            *(float *)(vars + 0x3B8) = limit;
            *(short *)(vars + 0x3BC) = 1;
        }
    }
    start_ptr = &start_point;
    width = D_L23_001AFA18;
    qcopy(start_ptr, moby + 0x10);
    moby_pos = moby + 0x10;
    FastVecSub(&end_point, *(char **)(vars + 0x2A0) + 0x10, moby_pos);
    FastVecScale(&end_point, &end_point, D_L23_001AFA1C);
    FastVecAdd(&end_point, &end_point, start_ptr);
    moby_forward = moby + 0xE0;
    forward_ptr = &forward;
    qcopy(forward_ptr, moby_forward);
    FastVecSub(&to_camera, start_ptr, g_camera_l23_position);
    FastVecCross(&sideways, forward_ptr, &to_camera);
    vec_scale_to_length(&sideways, &sideways, width);
    vec_scale_to_length(&pull_back, &to_camera, -D_L23_001AFA20);
    FastVecAdd(start_ptr, start_ptr, &pull_back);
    FastVecAdd(&end_point, &end_point, &pull_back);
    FastVecAdd(packet + 0x00, start_ptr, &sideways);
    FastVecSub(packet + 0x10, start_ptr, &sideways);
    FastVecAdd(packet + 0x20, &end_point, &sideways);
    FastVecSub(packet + 0x30, &end_point, &sideways);
    tex_bits = GetEffectTextureDescriptor(D_L23_001AFA24);
    color = D_L23_001AFA48;
    *(int *)(packet + 0x4C) = color;
    *(u64 *)(packet + 0x78) = tex_bits;
    *(unsigned long long *)(packet + 0x80) = 0xFF9000000260ULL;
    *(u64 *)(packet + 0x70) = 0;
    *(int *)(packet + 0x48) = color;
    *(int *)(packet + 0x44) = color;
    *(int *)(packet + 0x40) = color;
    VU1_addGSregister(0x47, 0x53001);
    gif_bits = D_L23_001AFA28;
    gif_bits |= (long long)D_L23_001AFA2C << 2;
    gif_bits |= (long long)D_L23_001AFA30 << 4;
    gif_bits |= (long long)D_L23_001AFA34 << 6;
    gif_bits |= (long long)(int)*(float *)(vars + 0x3B8) << 32;
    *(int *)(packet + 0x54) = 0;
    *(float *)(packet + 0x5C) = 1.0f;
    *(int *)(packet + 0x50) = 0;
    *(long long *)(packet + 0x88) = gif_bits;
    *(int *)(packet + 0x64) = 0;
    zero = *(float *)(packet + 0x50);
    *(float *)(packet + 0x68) = zero;
    *(float *)(packet + 0x6C) = 1.0f;
    *(float *)(packet + 0x60) = zero;
    *(float *)(packet + 0x58) = 0.99f;
    *(float *)(packet + 0x50) = 0.99f;
    draw_world_quad(packet, 0, 0);
}
