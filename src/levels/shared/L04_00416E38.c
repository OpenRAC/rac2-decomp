/* func_L04_00416E38 (levels 04 and 11): the menu box with its two labels. The box corners go
   through menu_coord; the two label ys go through label_y, whose block end after each conversion
   gives retail's registers for x4 and y4. */
#include "common.h"

extern float D_L04_001B2D44 __attribute__((sda));
extern int D_L04_001B2D40 __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0029B658(float, float, float, float, int, int);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern void func_00280200(void *, unsigned long long, char *, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);

/* The dead-test HUD rounding helper (allowed by owner ruling; master precedent
   src/game/002D2188-g8.c). */
static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c, `active`
   the literal 1 at every call). Its tests do not change the result: flow deletes their stores and
   jump2 their jumps, but only after allocation and both scheduling passes, which see the block they
   end. */
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

void func_L04_00416E38(void) {
    char box[32];
    float s, half, ky, kx;
    int x1, y1, x3, y3, x4, y4, on;

    half = 0.5f;
    on = 1;
    kx = 263.0f;
    s = D_L04_001B2D44;
    x1 = menu_coord(kx, s, half, on);
    ky = 371.0f;
    y1 = menu_coord(ky, s, half, on);
    func_0027EB88(x1, y1, 130, 384, 96, 0x60442D00);
    s = D_L04_001B2D44;
    func_0029B658((float)menu_coord(kx, s, half, on), (float)menu_coord(ky, s, half, on),
                  130.0f, 384.0f, 96, 0x55F0C070);
    s = D_L04_001B2D44;
    x3 = menu_coord(222.0f, s, half, on);
    y3 = label_y((void *)x3, 479.0f, s, half, 1);
    func_002802E0(box, x3, y3, 44, 468, 256, 299, 16, 3);
    func_00280200(box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    x4 = D_001A7340 / 2;
    y4 = label_y((void *)x4, 349.0f, D_L04_001B2D44, half, 1);
    func_0027FB40(x4, y4, (int)0x80F0F0F0, func_00288FB8(0x2F2C), -1);
}
