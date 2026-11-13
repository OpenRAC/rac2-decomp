#include "common.h"

/* func_US2_L04_00418348 (USA v2.00, levels 4 and 11): draws a framed menu box titled
   0xA41, a highlight bar sized to the width of label 0x2DC2 (at least the box width), and
   that label centred below it. The coordinates go through the menu_coord and label_y
   helpers, whose display-mode tests have no effect on the result. The bar's scale is read
   twice, once into s2 before the edges are computed, as retail loads it there. */

extern float D_L04_001B2D44 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR;
extern int D_001B0ACC SDATA(D_001B0ACC);
extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_US2_0029C448(int alpha, int color, float top, float bottom, float left, float right);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern void func_00280200(void *, unsigned long long, char *, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);
extern int func_L00_002E9120(char *, int);

typedef struct {
    u8 pad[0xC];
    s16 width;
    u8 pad2[4];
    u16 flags;
    u8 rest[0xC];
} MenuBox;

extern int D_L04_001B2D40 __attribute__((sda));
static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
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

void func_US2_L04_00418348(void) {
    MenuBox box;
    float s, s2, half, bx, kx, ky;
    int w, left, right, center, on, x1, y1, x4, y4;

    half = 0.5f;
    bx = 222.0f;
    on = 1;
    s = D_L04_001B2D44;
    func_002802E0(&box, menu_coord(bx, s, half, on), menu_coord(479.0f, s, half, on), 44, 468, 256, menu_coord(299.0f, s, half, on), 16, 3);
    kx = 263.0f;
    box.flags |= 4;
    func_00280200(&box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    w = func_L00_002E9120(func_00288FB8(0x2DC2), -1);
    if (w < box.width)
        w = box.width;
    center = D_001A7340 >> 1;
    s2 = D_L04_001B2D44;
    left = center - (w >> 1) - D_001B0ACC;
    right = center + (w >> 1) + D_001B0ACC;
    x1 = menu_coord(kx, s2, half, on);
    ky = 371.0f;
    y1 = menu_coord(ky, s2, half, on);
    func_0027EB88(x1, y1, left, right, 96, 0x60442D00);
    s = D_L04_001B2D44;
    func_US2_0029C448(96, 0x55F0C070, (float)menu_coord(kx, s, half, on), (float)menu_coord(ky, s, half, on), (float)left, (float)right);
    box.flags &= ~4;
    func_00280200(&box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    x4 = D_001A7340 / 2;
    y4 = label_y((void *)x4, 349.0f, D_L04_001B2D44, half, on);
    func_0027FB40(x4, y4, (int)0x80F0F0F0, func_00288FB8(0x2DC2), -1);
}
