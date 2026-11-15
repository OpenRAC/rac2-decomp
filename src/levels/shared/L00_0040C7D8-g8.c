#include "common.h"

extern char g_hero_state[];
extern char g_camera_l00_position[];
extern char D_L00_002563A0[];
extern float D_L00_001B1000 __attribute__((sda));
extern float D_L00_001B0FF8 __attribute__((sda));
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void draw_world_quad(void *, int, int);
extern void DrawRibbonWithHalo(void *, int, int, float, float, float, int, int, int);

/* Draws two camera-facing beam segments outside the angle threshold,
 * or four glowing point chains with intensity selected by the state flag. */
void DrawBeamSegmentsOrRibbons(char *object)
{
    struct {
        float position[16];
        int color[4];
        float uv[8];
        char tail[32];
    } buffer;
    char *packet = (char *)&buffer;
    float delta[4], camera[4], normal[4];
    char *position, *third, *start, *end;
    char *state = *(char **)(object + 0x68);
    char *globals = g_hero_state;
    char *target = *(char **)(globals + 0x18d0);
    float angle = mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(globals + 0x80),
                               *(float *)(target + 0x14) - *(float *)(globals + 0x84));

    angle = FastDiffRots(angle, *(float *)(globals + 0x98));
    if (D_L00_001B1000 * 0.017453294f < angle) {
        if (*(int *)(state + 0x1c)) {
            gfx_init_quad_packet_state(packet, 0x17, 1, 0x80);
            position = object + 0x10;
            *(int *)(packet + 0x40) = *(int *)(packet + 0x44) =
                *(int *)(packet + 0x48) = *(int *)(packet + 0x4c) =
                (*(int *)(state + 0x10) << 27) | 0xa0aff;
            start = state + 0x30;
            end = state + 0x60;
            third = state + 0x70;

            *(int *)(packet + 0x48) = *(int *)(packet + 0x4c) = (*(int *)(state + 0x10) << 27) | 0xa0aff;
            buffer.uv[0] = 0.0f;
            buffer.uv[1] = 0.0f;
            buffer.uv[2] = 0.0f;
            buffer.uv[3] = 1.0f;
            buffer.uv[4] = 1.0f;
            buffer.uv[5] = 0.0f;
            buffer.uv[6] = 1.0f;
            buffer.uv[7] = 1.0f;
            FastVecSub(delta, start, end);
            FastVecSub(camera, position, g_camera_l00_position);
            FastVecCross(normal, camera, delta);
            vec_scale_to_length(normal, normal, D_L00_001B0FF8);
            FastVecAdd(packet, start, normal);
            FastVecSub(packet + 0x10, start, normal);
            FastVecAdd(packet + 0x20, end, normal);
            FastVecSub(packet + 0x30, end, normal);
            draw_world_quad(packet, 0, 0);
            draw_world_quad(packet, 0, 0);
            FastVecSub(delta, start, third);
            FastVecSub(camera, position, g_camera_l00_position);
            FastVecCross(normal, camera, delta);
            vec_scale_to_length(normal, normal, D_L00_001B0FF8);
            FastVecAdd(packet, start, normal);
            FastVecSub(packet + 0x10, start, normal);
            FastVecAdd(packet + 0x20, third, normal);
            FastVecSub(packet + 0x30, third, normal);
            draw_world_quad(packet, 0, 0);
            draw_world_quad(packet, 0, 0);
        }
    } else if (*(int *)(state + 0x1c)) {
        DrawRibbonWithHalo(D_L00_002563A0, 70, 70, 0.2f, 0.35f, 0.2f, 10, 0x7f7f7f, 0x10ff10);
        DrawRibbonWithHalo(D_L00_002563A0 + 0xa0, 32, 32, 0.1f, 0.19f, 0.2f, 10, 0x7f7f7f, 0xff1010);
        DrawRibbonWithHalo(D_L00_002563A0 + 0x140, 32, 32, 0.1f, 0.19f, 0.2f, 10, 0x7f7f7f, 0xff1010);
        DrawRibbonWithHalo(D_L00_002563A0 + 0x1e0, 32, 32, 0.1f, 0.19f, 0.2f, 10, 0x7f7f7f, 0xff1010);
    } else {
        DrawRibbonWithHalo(D_L00_002563A0, 50, 50, 0.07f, 0.15f, 0.2f, 10, 0x7f7f7f, 0x20ff20);
        DrawRibbonWithHalo(D_L00_002563A0 + 0xa0, 15, 15, 0.03f, 0.09f, 0.2f, 10, 0x7f7f7f, 0x10ffff);
        DrawRibbonWithHalo(D_L00_002563A0 + 0x140, 15, 15, 0.03f, 0.09f, 0.2f, 10, 0x7f7f7f, 0x10ffff);
        DrawRibbonWithHalo(D_L00_002563A0 + 0x1e0, 15, 15, 0.03f, 0.09f, 0.2f, 10, 0x7f7f7f, 0x10ffff);
    }
}
