#include "common.h"
/* Adapted from RAC1 draw_scrolling_ribbon_colored (OpenRAC, GPL-3.0). */
extern int g_ribbon_l14_core_texture __attribute__((sda));
extern int g_ribbon_l14_halo_texture __attribute__((sda));
extern int g_ribbon_l14_core_color __attribute__((sda));
extern int g_ribbon_l14_halo_color __attribute__((sda));
extern float g_ribbon_l14_uv_scroll __attribute__((sda));
extern char g_tether_l14_origin_vec[];
extern long GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern void VU1_addGSregister(int, long);
typedef float RibbonVector[4] __attribute__((aligned(16)));
typedef struct { float v[4]; } RibbonPoint;
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 pos;          /* 0x00 */
    TI128 next;         /* 0x10 */
    float height;       /* 0x20 */
    int handle;         /* 0x24 */
    int pad28;          /* 0x28 */
    int count;          /* 0x2C */
    int mode;           /* 0x30 */
    int shape;          /* 0x34 */
    int row;            /* 0x38 */
    int dirty;          /* 0x3C */
    float f40;          /* 0x40 */
    float f44;          /* 0x44 */
    int coreColor;      /* 0x48 */
    int haloColor;      /* 0x4C */
} RibbonOwnerState;
typedef struct {
    int color[4];
    float uv[8];
    long primitive, texture, mode, flags;
} RibbonMaterial;

extern void ResetBoltPointsToLine(void *self);
extern void part_rebuild_lightning_bolt(void *self);
extern void gfx_add_draw_callback_third(void (*callback)(char *), void *object);
extern void gfx_draw_ribbon_pair(char *object);
extern int gfx_add_point_light(float *position, float range, float radius, int color);

extern int g_ribbon_l14_segment_count __attribute__((sda));
extern float g_ribbon_l14_core_width __attribute__((sda));
extern float g_ribbon_l14_halo_width __attribute__((sda));

extern char *g_effect_path_table[];
extern char g_ribbon_buffers[][0x280];

/* Moves the ribbon's head to the object's position, eases its height and adds it to the
   head; when the state is dirty, refreshes the newest four points of the ribbon's row from
   the shape table and queues the draw callback. On the first update it resets the state. */
void ribbon_update(char *self)
{
    RibbonOwnerState *st = *(RibbonOwnerState **)(self + 0x68);
    float v[4] __attribute__((aligned(16)));
    char *src;
    int count;
    int i;

    qcopy(&st->pos, self + 0x10);
    qcopy(&st->next, &st->pos);
    st->height += (6.0f - st->height) * 0.07f + 12.0f;
    v[0] = 0;
    v[1] = st->height;
    v[2] = 0;
    FastVecAdd(&st->next, &st->pos, v);
    /* The new head is copied back into v as well; v is not used again. */
    qcopy(v, &st->next);
    g_ribbon_l14_segment_count = 20;
    ResetBoltPointsToLine(self);

    if (st->dirty != 0) {
        part_rebuild_lightning_bolt(self);
        count = g_ribbon_l14_segment_count;
        src = g_effect_path_table[st->shape];
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&g_ribbon_buffers[st->row][i * 16], src + i * 16 + 0x10);
        }
        gfx_add_draw_callback_third(gfx_draw_ribbon_pair, self);
    }

    if (*(unsigned char *)(self + 0x20) == 0) {
        st->dirty = 0;
        st->handle = gfx_add_point_light((float *)&st->pos, 0.0f, 0.0f, 0);
        *(unsigned char *)(self + 0x20) = 1;
        st->count = g_ribbon_l14_segment_count;
        st->coreColor = g_ribbon_l14_core_color;
        st->haloColor = g_ribbon_l14_halo_color;
        st->f40 = g_ribbon_l14_core_width;
        st->f44 = g_ribbon_l14_halo_width;
        st->mode = -1;
    }
}

/* Draws a scrolled core and a camera-facing halo, with colours from the owner. */
void DrawPrisonScrollingRibbonWithHalo(char *object, RibbonPoint *points, int alpha, int outerAlpha, int count, float coreWidth, float haloWidth, float extend)
{
    RibbonVector coreVertices[4];
    RibbonMaterial core;
    RibbonVector haloVertices[4];
    RibbonMaterial halo;
    RibbonVector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    int i, coreColor, haloColor;
    float length, initialLength, haloLength, firstLength, lastLength;
    /* Each pass declares its own zero constant; one shared constant changes the code. */
    const float zero = 0.0f;
    RibbonOwnerState *state = *(RibbonOwnerState **)(object + 0x68);
    long texture = GetEffectTextureDescriptor(g_ribbon_l14_core_texture);

    core.flags = 0x8000000048L;
    core.mode = 0xFF9000000260L;
    core.texture = texture;
    core.primitive = 0;
    coreColor = state->coreColor | (alpha << 24);
    core.color[3] = coreColor;
    core.color[2] = coreColor;
    core.color[1] = coreColor;
    core.color[0] = coreColor;
    halo.texture = GetEffectTextureDescriptor(g_ribbon_l14_halo_texture);
    haloColor = state->haloColor | (outerAlpha << 24);
    halo.flags = core.flags;
    halo.mode = core.mode;
    halo.primitive = core.primitive;
    halo.color[3] = haloColor;
    halo.color[2] = haloColor;
    halo.color[1] = haloColor;
    halo.color[0] = haloColor;

    halo.uv[0] = zero;
    halo.uv[1] = zero;
    halo.uv[2] = zero;
    halo.uv[3] = 1.0f;
    halo.uv[4] = 1.0f;
    halo.uv[5] = zero;
    halo.uv[6] = 1.0f;
    halo.uv[7] = 1.0f;
    core.uv[0] = g_ribbon_l14_uv_scroll;
    core.uv[1] = zero;
    core.uv[2] = g_ribbon_l14_uv_scroll;
    core.uv[3] = 1.0f;
    core.uv[4] = g_ribbon_l14_uv_scroll + 1.0f;
    core.uv[5] = zero;
    core.uv[6] = g_ribbon_l14_uv_scroll + 1.0f;
    core.uv[7] = 1.0f;

    /* First core segment. */
    FastVecSub(eye, points, g_tether_l14_origin_vec);
    FastVecSub(tangent, &points[1], points);
    FastVecCross(normal, tangent, eye);
    initialLength = FastVecLength(normal);
    if (initialLength != zero)
        initialLength = 1.0f / initialLength;
    FastVecScale(normal, normal, coreWidth * initialLength);
    FastVecAdd(coreVertices[0], points, normal);
    FastVecSub(coreVertices[1], points, normal);

    for (i = 1; i < count - 1; i++) {
        float coreZero = 0.0f;
        FastVecSub(eye, &points[i], g_tether_l14_origin_vec);
        FastVecSub(tangent, &points[i + 1], &points[i]);
        FastVecCross(normal, tangent, eye);
        length = FastVecLength(normal);
        if (length != coreZero)
            length = 1.0f / length;
        FastVecScale(normal, normal, coreWidth * length);
        FastVecAdd(coreVertices[2], &points[i], normal);
        FastVecSub(coreVertices[3], &points[i], normal);
        if (i == 1) {
            core.color[1] = g_ribbon_l14_core_color;
            core.color[0] = g_ribbon_l14_core_color;
        } else if (i == count - 2) {
            core.color[3] = g_ribbon_l14_core_color;
            core.color[2] = g_ribbon_l14_core_color;
        } else if (i == 2) {
            core.color[1] = coreColor;
            core.color[0] = coreColor;
        }
        draw_world_quad(coreVertices, 0, 0);
        qcopy(coreVertices[0], coreVertices[2]);
        qcopy(coreVertices[1], coreVertices[3]);
    }

    /* The halo omits the final core segment. */
    for (i = 0; i < count - 2; i++) {
        float haloZero = 0.0f;
        FastVecSub(firstRay, &points[i], g_tether_l14_origin_vec);
        FastVecSub(lastRay, &points[i + 1], g_tether_l14_origin_vec);
        firstLength = FastVecLength(firstRay);
        lastLength = FastVecLength(lastRay);
        if (lastLength < firstLength) {
            if (lastLength == haloZero)
                qcopy(lastRay, firstRay);
            else
                FastVecScale(lastRay, lastRay, firstLength / lastLength);
        } else {
            if (firstLength == haloZero)
                qcopy(firstRay, lastRay);
            else
                FastVecScale(firstRay, firstRay, lastLength / firstLength);
        }
        FastVecAdd(first, g_tether_l14_origin_vec, firstRay);
        FastVecAdd(last, g_tether_l14_origin_vec, lastRay);
        FastVecSub(tangent, last, first);
        FastVecScale(extension, tangent, extend);
        FastVecSub(first, first, extension);
        FastVecAdd(last, last, extension);
        FastVecSub(toEye, g_tether_l14_origin_vec, first);
        FastVecCross(normal, toEye, tangent);
        haloLength = FastVecLength(normal);
        if (haloLength != haloZero)
            haloLength = 1.0f / haloLength;
        FastVecScale(widthVector, normal, haloWidth * haloLength);
        FastVecAdd(haloVertices[0], first, widthVector);
        FastVecSub(haloVertices[1], first, widthVector);
        FastVecAdd(haloVertices[2], last, widthVector);
        FastVecSub(haloVertices[3], last, widthVector);
        if (i == 0) {
            halo.color[1] = g_ribbon_l14_halo_color;
            halo.color[0] = g_ribbon_l14_halo_color;
        } else if (i == count - 3) {
            halo.color[3] = g_ribbon_l14_halo_color;
            halo.color[2] = g_ribbon_l14_halo_color;
        } else if (i == 1) {
            halo.color[1] = haloColor;
            halo.color[0] = haloColor;
        }
        draw_world_quad(haloVertices, 0, 0);
    }

    VU1_addGSregister(0x47, 0x5360B);
}
