#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union {
    Quad quad;
    float f[4];
} Vector;

typedef struct {
    Vector vertex[4];
    u32 color[4];
    float uv[8];
    u64 primitive;
    u64 texture;
    u64 mode;
    u64 flags;
} RibbonPacket;

extern char g_camera_l00_position[];
extern float g_ribbon_core_scroll_u_alt __attribute__((sda));
extern int g_core_effect_texture_id __attribute__((sda));
extern int g_halo_effect_texture_id __attribute__((sda));
extern u32 g_ribbon_core_color_alt __attribute__((sda));
extern u32 g_ribbon_l00_halo_color_3 __attribute__((sda));

extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern void VU1_addGSregister(int, u64);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);

/* Draws the narrow ribbon and its camera-facing halo along the point chain.
 * The EE ABI orders the integer and FP banks independently: count is a3,
 * and coreWidth, width and extend are f12, f13 and f14. */
void DrawScrollingRibbonWithFadedEnds(Vector *points, u32 alpha, u32 outerAlpha, float coreWidth, float width, float extend, int count)
{
    RibbonPacket core, halo;
    Vector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i;
    u32 coreColor, haloColor;
    /* Separate zero constants for the setup and for each loop. */
    const float zero = 0.0f;

    core.texture = GetEffectTextureDescriptor(g_core_effect_texture_id);
    coreColor = g_ribbon_core_color_alt | (alpha << 24);
    core.flags = 0x8000000048ULL;
    core.mode = 0xFF9000000260ULL;
    core.primitive = 0;
    core.color[3] = coreColor;
    core.color[2] = coreColor;
    core.color[1] = coreColor;
    core.color[0] = coreColor;

    halo.texture = GetEffectTextureDescriptor(g_halo_effect_texture_id);
    halo.flags = core.flags;
    halo.mode = core.mode;
    halo.primitive = core.primitive;
    haloColor = g_ribbon_l00_halo_color_3 | (outerAlpha << 24);
    halo.color[3] = haloColor;
    halo.color[2] = haloColor;
    halo.color[1] = haloColor;
    halo.color[0] = haloColor;

    halo.uv[0] = zero;
    halo.uv[1] = zero;
    halo.uv[2] = zero;
    halo.uv[3] = 1;
    halo.uv[4] = 1;
    halo.uv[5] = zero;
    halo.uv[6] = 1;
    halo.uv[7] = 1;

    core.uv[0] = g_ribbon_core_scroll_u_alt;
    core.uv[1] = zero;
    core.uv[2] = g_ribbon_core_scroll_u_alt;
    core.uv[3] = 1;
    core.uv[4] = g_ribbon_core_scroll_u_alt + 1.0f;
    core.uv[5] = zero;
    core.uv[6] = g_ribbon_core_scroll_u_alt + 1.0f;
    core.uv[7] = 1;

    FastVecSub(&eye, points, g_camera_l00_position);
    FastVecSub(&tangent, points + 1, points);
    FastVecCross(&normal, &tangent, &eye);
    initialLength = FastVecLength(&normal);
    if (initialLength != zero)
        initialLength = 1.0f / initialLength;
    FastVecScale(&normal, &normal, coreWidth * initialLength);
    FastVecAdd(&core.vertex[0], points, &normal);
    FastVecSub(&core.vertex[1], points, &normal);

    for (i = 1; i < count - 1; i++) {
        float coreZero = 0.0f;

        FastVecSub(&eye, points + i, g_camera_l00_position);
        FastVecSub(&tangent, points + i + 1, points + i);
        FastVecCross(&normal, &tangent, &eye);
        length = FastVecLength(&normal);
        if (length != coreZero)
            length = 1.0f / length;
        FastVecScale(&normal, &normal, coreWidth * length);
        FastVecAdd(&core.vertex[2], points + i, &normal);
        FastVecSub(&core.vertex[3], points + i, &normal);

        if (i == 1) {
            core.color[1] = g_ribbon_core_color_alt;
            core.color[0] = g_ribbon_core_color_alt;
        } else if (i == count - 2) {
            core.color[3] = g_ribbon_core_color_alt;
            core.color[2] = g_ribbon_core_color_alt;
        } else if (i == 2) {
            core.color[1] = coreColor;
            core.color[0] = coreColor;
        }

        draw_world_quad(&core, 0, 0);
        qcopy(&core.vertex[0], &core.vertex[2]);
        qcopy(&core.vertex[1], &core.vertex[3]);
    }

    for (i = 0; i < count - 1; i++) {
        float haloZero = 0.0f;

        FastVecSub(&firstRay, points + i, g_camera_l00_position);
        FastVecSub(&lastRay, points + i + 1, g_camera_l00_position);
        firstLength = FastVecLength(&firstRay);
        lastLength = FastVecLength(&lastRay);
        if (lastLength < firstLength) {
            if (lastLength == haloZero)
                qcopy(&lastRay, &firstRay);
            else
                FastVecScale(&lastRay, &lastRay, firstLength / lastLength);
        } else {
            if (firstLength == haloZero)
                qcopy(&firstRay, &lastRay);
            else
                FastVecScale(&firstRay, &firstRay, lastLength / firstLength);
        }

        FastVecAdd(&first, g_camera_l00_position, &firstRay);
        FastVecAdd(&last, g_camera_l00_position, &lastRay);
        FastVecSub(&tangent, &last, &first);
        FastVecScale(&extension, &tangent, extend);
        FastVecSub(&first, &first, &extension);
        FastVecAdd(&last, &last, &extension);

        FastVecSub(&toEye, g_camera_l00_position, &first);
        FastVecCross(&normal, &toEye, &tangent);
        haloLength = FastVecLength(&normal);
        if (haloLength != haloZero)
            haloLength = 1.0f / haloLength;
        FastVecScale(&widthVector, &normal, width * haloLength);
        FastVecAdd(&halo.vertex[0], &first, &widthVector);
        FastVecSub(&halo.vertex[1], &first, &widthVector);
        FastVecAdd(&halo.vertex[2], &last, &widthVector);
        FastVecSub(&halo.vertex[3], &last, &widthVector);

        if (i == 0) {
            halo.color[1] = g_ribbon_l00_halo_color_3;
            halo.color[0] = g_ribbon_l00_halo_color_3;
        } else if (i == count - 2) {
            halo.color[3] = g_ribbon_l00_halo_color_3;
            halo.color[2] = g_ribbon_l00_halo_color_3;
        } else if (i == 1) {
            halo.color[1] = haloColor;
            halo.color[0] = haloColor;
        }

        draw_world_quad(&halo, 0, 0);
    }

    VU1_addGSregister(0x47, 0x5360B);
}
