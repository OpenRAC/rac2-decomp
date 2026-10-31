#include "common.h"
/* Adapted from RAC1 draw_scrolling_ribbon_colored (OpenRAC, GPL-3.0). */
extern int D_L14_001B16A8 __attribute__((sda));
extern int D_L14_001B16AC __attribute__((sda));
extern int D_L14_001B1680 __attribute__((sda));
extern int D_L14_001B1684 __attribute__((sda));
extern float D_L14_001B1678 __attribute__((sda));
extern char D_L14_001B9500[];
extern long func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_002FC560(int, long);
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

extern void func_L11_0046BC08(void *self);
extern void func_L14_00422498(void *self);
extern void func_L00_002E6EF8(void (*callback)(char *), void *object);
extern void func_L14_004228C0(char *object);
extern int func_00291308(float *position, float range, float radius, int color);

extern int D_L14_001B1618 __attribute__((sda));
extern float D_L14_001B1688 __attribute__((sda));
extern float D_L14_001B168C __attribute__((sda));

extern char *D_L14_001FE1C0[];
extern char D_L14_002594F0[][0x280];

/* Moves the ribbon's head to the object's position, eases its height and adds it to the
   head; when the state is dirty, refreshes the newest four points of the ribbon's row from
   the shape table and queues the draw callback. On the first update it resets the state. */
void func_L14_004221D8(char *self)
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
    func_00282CC0(&st->next, &st->pos, v);
    /* The new head is copied back into v as well; v is not used again. */
    qcopy(v, &st->next);
    D_L14_001B1618 = 20;
    func_L11_0046BC08(self);

    if (st->dirty != 0) {
        func_L14_00422498(self);
        count = D_L14_001B1618;
        src = D_L14_001FE1C0[st->shape];
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&D_L14_002594F0[st->row][i * 16], src + i * 16 + 0x10);
        }
        func_L00_002E6EF8(func_L14_004228C0, self);
    }

    if (*(unsigned char *)(self + 0x20) == 0) {
        st->dirty = 0;
        st->handle = func_00291308((float *)&st->pos, 0.0f, 0.0f, 0);
        *(unsigned char *)(self + 0x20) = 1;
        st->count = D_L14_001B1618;
        st->coreColor = D_L14_001B1680;
        st->haloColor = D_L14_001B1684;
        st->f40 = D_L14_001B1688;
        st->f44 = D_L14_001B168C;
        st->mode = -1;
    }
}

/* Draws a scrolled core and a camera-facing halo, with colours from the owner. */
void func_L14_004229A0(char *object, RibbonPoint *points, int alpha, int outerAlpha, int count, float coreWidth, float haloWidth, float extend)
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
    long texture = func_0027C878(D_L14_001B16A8);

    core.flags = 0x8000000048L;
    core.mode = 0xFF9000000260L;
    core.texture = texture;
    core.primitive = 0;
    coreColor = state->coreColor | (alpha << 24);
    core.color[3] = coreColor;
    core.color[2] = coreColor;
    core.color[1] = coreColor;
    core.color[0] = coreColor;
    halo.texture = func_0027C878(D_L14_001B16AC);
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
    core.uv[0] = D_L14_001B1678;
    core.uv[1] = zero;
    core.uv[2] = D_L14_001B1678;
    core.uv[3] = 1.0f;
    core.uv[4] = D_L14_001B1678 + 1.0f;
    core.uv[5] = zero;
    core.uv[6] = D_L14_001B1678 + 1.0f;
    core.uv[7] = 1.0f;

    /* First core segment. */
    func_00282CF0(eye, points, D_L14_001B9500);
    func_00282CF0(tangent, &points[1], points);
    func_00282DD8(normal, tangent, eye);
    initialLength = func_00282DF0(normal);
    if (initialLength != zero)
        initialLength = 1.0f / initialLength;
    func_00282D30(normal, normal, coreWidth * initialLength);
    func_00282CC0(coreVertices[0], points, normal);
    func_00282CF0(coreVertices[1], points, normal);

    for (i = 1; i < count - 1; i++) {
        float coreZero = 0.0f;
        func_00282CF0(eye, &points[i], D_L14_001B9500);
        func_00282CF0(tangent, &points[i + 1], &points[i]);
        func_00282DD8(normal, tangent, eye);
        length = func_00282DF0(normal);
        if (length != coreZero)
            length = 1.0f / length;
        func_00282D30(normal, normal, coreWidth * length);
        func_00282CC0(coreVertices[2], &points[i], normal);
        func_00282CF0(coreVertices[3], &points[i], normal);
        if (i == 1) {
            core.color[1] = D_L14_001B1680;
            core.color[0] = D_L14_001B1680;
        } else if (i == count - 2) {
            core.color[3] = D_L14_001B1680;
            core.color[2] = D_L14_001B1680;
        } else if (i == 2) {
            core.color[1] = coreColor;
            core.color[0] = coreColor;
        }
        func_00280B90(coreVertices, 0, 0);
        qcopy(coreVertices[0], coreVertices[2]);
        qcopy(coreVertices[1], coreVertices[3]);
    }

    /* The halo omits the final core segment. */
    for (i = 0; i < count - 2; i++) {
        float haloZero = 0.0f;
        func_00282CF0(firstRay, &points[i], D_L14_001B9500);
        func_00282CF0(lastRay, &points[i + 1], D_L14_001B9500);
        firstLength = func_00282DF0(firstRay);
        lastLength = func_00282DF0(lastRay);
        if (lastLength < firstLength) {
            if (lastLength == haloZero)
                qcopy(lastRay, firstRay);
            else
                func_00282D30(lastRay, lastRay, firstLength / lastLength);
        } else {
            if (firstLength == haloZero)
                qcopy(firstRay, lastRay);
            else
                func_00282D30(firstRay, firstRay, lastLength / firstLength);
        }
        func_00282CC0(first, D_L14_001B9500, firstRay);
        func_00282CC0(last, D_L14_001B9500, lastRay);
        func_00282CF0(tangent, last, first);
        func_00282D30(extension, tangent, extend);
        func_00282CF0(first, first, extension);
        func_00282CC0(last, last, extension);
        func_00282CF0(toEye, D_L14_001B9500, first);
        func_00282DD8(normal, toEye, tangent);
        haloLength = func_00282DF0(normal);
        if (haloLength != haloZero)
            haloLength = 1.0f / haloLength;
        func_00282D30(widthVector, normal, haloWidth * haloLength);
        func_00282CC0(haloVertices[0], first, widthVector);
        func_00282CF0(haloVertices[1], first, widthVector);
        func_00282CC0(haloVertices[2], last, widthVector);
        func_00282CF0(haloVertices[3], last, widthVector);
        if (i == 0) {
            halo.color[1] = D_L14_001B1684;
            halo.color[0] = D_L14_001B1684;
        } else if (i == count - 3) {
            halo.color[3] = D_L14_001B1684;
            halo.color[2] = D_L14_001B1684;
        } else if (i == 1) {
            halo.color[1] = haloColor;
            halo.color[0] = haloColor;
        }
        func_00280B90(haloVertices, 0, 0);
    }

    func_002FC560(0x47, 0x5360B);
}
