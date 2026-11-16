#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } RibbonPacket;
extern char g_camera_eye_state[];
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int), VU1_addGSregister(int, u64);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *), FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float g_ribbon_uv_scroll __attribute__((sda)), g_ribbon_normal_scale __attribute__((sda));
extern int g_ribbon_core_texture __attribute__((sda)), g_ribbon_halo_texture __attribute__((sda));
extern s32 g_ribbon_core_end_color __attribute__((sda)), g_ribbon_halo_color __attribute__((sda));
/* Draws the narrow ribbon and its camera-facing halo along the point chain.
 * The EE ABI independently orders integer and FP arguments: count is a3,
 * unused is f12, width is f13, and extend is f14. */
void beam_draw_ribbon_with_halo(Vector *points, u32 color, u32 outerColor, float unused, float width, float extend, int count) {
    RibbonPacket core, halo;
    Vector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i;
    u32 coreColor, haloColor;
    core.texture = GetEffectTextureDescriptor(g_ribbon_core_texture);
    coreColor = color;
    core.flags = 0x8000000048ULL;
    core.mode = 0xFF9000000260ULL;
    core.primitive = 0;
    core.color[3] = coreColor; core.color[2] = coreColor;
    core.color[1] = coreColor; core.color[0] = coreColor;
    halo.texture = GetEffectTextureDescriptor(g_ribbon_halo_texture);
    halo.flags = core.flags; halo.mode = core.mode; halo.primitive = core.primitive;
    haloColor = outerColor;
    halo.color[3] = haloColor; halo.color[2] = haloColor;
    halo.color[1] = haloColor; halo.color[0] = haloColor;
    halo.uv[0] = 0; halo.uv[1] = 0; halo.uv[2] = 0; halo.uv[3] = 1;
    halo.uv[4] = 1; halo.uv[5] = 0; halo.uv[6] = 1; halo.uv[7] = 1;
    core.uv[0] = g_ribbon_uv_scroll; core.uv[1] = 0; core.uv[2] = g_ribbon_uv_scroll; core.uv[3] = 1;
    core.uv[4] = g_ribbon_uv_scroll + 1.0f; core.uv[5] = 0; core.uv[6] = g_ribbon_uv_scroll + 1.0f; core.uv[7] = 1;
    FastVecSub(&eye, points, g_camera_eye_state);
    FastVecSub(&tangent, points + 1, points);
    FastVecCross(&normal, &tangent, &eye);
    initialLength = FastVecLength(&normal);
    if (initialLength != 0) initialLength = 1.0f / initialLength;
    FastVecScale(&normal, &normal, g_ribbon_normal_scale * initialLength);
    FastVecAdd(&core.vertex[0], points, &normal);
    FastVecSub(&core.vertex[1], points, &normal);
    for (i = 1; i < count - 1; i++) {
        FastVecSub(&eye, points + i, g_camera_eye_state);
        FastVecSub(&tangent, points + i + 1, points + i);
        FastVecCross(&normal, &tangent, &eye);
        length = FastVecLength(&normal);
        if (length != 0) length = 1.0f / length;
        FastVecScale(&normal, &normal, g_ribbon_normal_scale * length);
        FastVecAdd(&core.vertex[2], points + i, &normal);
        FastVecSub(&core.vertex[3], points + i, &normal);
        if (i == 1) { core.color[1] = g_ribbon_core_end_color; core.color[0] = g_ribbon_core_end_color; }
        else if (i == count - 2) { core.color[3] = g_ribbon_core_end_color; core.color[2] = g_ribbon_core_end_color; }
        else if (i == 2) { core.color[1] = coreColor; core.color[0] = coreColor; }
        draw_world_quad(&core, 0, 0);
        qcopy(&core.vertex[0], &core.vertex[2]); qcopy(&core.vertex[1], &core.vertex[3]);
    }
    for (i = 0; i < count - 1; i++) {
        FastVecSub(&firstRay, points + i, g_camera_eye_state);
        FastVecSub(&lastRay, points + i + 1, g_camera_eye_state);
        firstLength = FastVecLength(&firstRay);
        lastLength = FastVecLength(&lastRay);
        if (lastLength < firstLength) {
            if (lastLength == 0) { qcopy(&lastRay, &firstRay); }
            else FastVecScale(&lastRay, &lastRay, firstLength / lastLength);
        } else if (firstLength == 0) { qcopy(&firstRay, &lastRay); }
        else FastVecScale(&firstRay, &firstRay, lastLength / firstLength);
        FastVecAdd(&first, g_camera_eye_state, &firstRay);
        FastVecAdd(&last, g_camera_eye_state, &lastRay);
        FastVecSub(&tangent, &last, &first);
        FastVecScale(&extension, &tangent, extend);
        FastVecSub(&first, &first, &extension);
        FastVecAdd(&last, &last, &extension);
        FastVecSub(&toEye, g_camera_eye_state, &first);
        FastVecCross(&normal, &toEye, &tangent);
        haloLength = FastVecLength(&normal);
        if (haloLength != 0) haloLength = 1.0f / haloLength;
        FastVecScale(&widthVector, &normal, width * haloLength);
        FastVecAdd(&halo.vertex[0], &first, &widthVector);
        FastVecSub(&halo.vertex[1], &first, &widthVector);
        FastVecAdd(&halo.vertex[2], &last, &widthVector);
        FastVecSub(&halo.vertex[3], &last, &widthVector);
        if (i == 0) { halo.color[1] = g_ribbon_halo_color; halo.color[0] = g_ribbon_halo_color; }
        else if (i == count - 2) { halo.color[3] = g_ribbon_halo_color; halo.color[2] = g_ribbon_halo_color; }
        else if (i == 1) { halo.color[1] = haloColor; halo.color[0] = haloColor; }
        draw_world_quad(&halo, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}
