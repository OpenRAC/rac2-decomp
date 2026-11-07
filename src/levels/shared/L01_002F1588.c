/* func_L01_002F1588 (levels 01, 03, 07, 16, 20): the HUD overlay with its icon. The icon block's
   two label ys go through label_y; the other coordinates keep the dead-test rounding helpers. */
#include "common.h"
typedef struct { int first, second; } OverlayColorPair;
extern unsigned char *D_L01_001A908C __attribute__((sda));
extern unsigned char D_L01_0027EAC8[];
extern int D_L01_001A90D0[] SDATA(D_L01_001A90D0);
extern int D_L01_001A90CC[] SDATA(D_L01_001A90CC);
extern float D_L01_001A90C4[] SDATA(D_L01_001A90C4);
extern float D_L01_001B2DC4[] __attribute__((sda));
extern unsigned char D_L01_001BD9C0[];
extern void func_0027AB40(void);
extern int func_00336D50(void *, int);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027EAE8(int, int, int, int, int, const void *);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);

extern int D_L01_001B2DC0[] __attribute__((sda));

/* dead-test helper allowed by owner ruling (master precedent: src/game/002D2188-g8.c) */

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L01_001B2DC0[0] == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int hud_round(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && result == active)
        scaled = 1.0f;
    return result;
}

static __inline__ unsigned char *hud_camera(void)
{
    return D_L01_001BD9C0;
}

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c). Its
   tests do not change the result: flow deletes their stores and jump2 their jumps, but only after
   allocation and both scheduling passes, which see the block they end. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L01_001B2DC0[0];
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

int func_L01_002F1588(void)
{
    OverlayColorPair colors, source;
    float oldProjection, span, rounding, unit, zero, height;
    int top, bottom;
    unsigned char *node;
    int x2, y, one, entry;
    if (!D_L01_001A908C || *(int *)D_L01_0027EAC8 || *(int *)(D_L01_0027EAC8 + 0x24) != -1)
        return D_L01_001A90D0[0];
    oldProjection = *(float *)(hud_camera() + 0xB0);
    *(float *)(hud_camera() + 0xB0) = 0.6200000047683716f;
    span = 375.0f;
    func_0027AB40();
    rounding = 0.5f;
    one = 1;
    entry = 0x8710;
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 142);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = 1.0f;
    unit = height;
    height = 0.0f;
    zero = height;
    height = (float)y;
    func_00300A00(node, 0x60442D00, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 143);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = (float)y;
    func_00300A00(node, 0x60241700, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 144);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = (float)y;
    func_00300A00(node, 0x55F0C070, 250.0f, height, unit, unit, zero);
    source.first = (int)0x800050C0;
    source.second = func_00283D38(0x800050C0, 0x80C04000, D_L01_001A90C4[0]);
    colors = source;
    x2 = func_00283CF0(190.0f + func_00283CE0(198) * D_L01_001A90C4[0]);
    height = D_L01_001B2DC4[0];
    top = hud_round(374.0f, height, rounding, one);
    bottom = hud_round(388.0f, height, rounding, one);
    func_0027EAE8(190, top, x2, bottom, 0, &colors);
    if (D_L01_001A90CC[0]) {
        int icon = func_0028E588(0xEAA7, D_L01_001A90CC[0] - 1);
        height = D_L01_001B2DC4[0];
        /* This caller passes `one`, a local holding 1, as `active` (allowed by owner ruling). */
        top = label_y((void *)icon, 352.0f, height, rounding, one);
        bottom = label_y((void *)icon, 43.0f, height, rounding, one);
        func_0028E868(icon, 139, top, 43, bottom, 128);
    }
    *(float *)(hud_camera() + 0xB0) = oldProjection;
    func_0027AB40();
    return D_L01_001A90D0[0];
}
