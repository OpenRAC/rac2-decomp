/* func_L04_00417028 (levels 04 and 11): the timer box. It formats the elapsed time, draws the box
   (corners through menu_coord) and the centred text, whose y goes through label_y. */
#include "include_asm.h"

extern int D_L04_001A8FE4 __attribute__((sda));
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(char *);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0029B658(float, float, float, float, int, int);
extern int func_0027FBD8(int, int, unsigned long long, char *, int);
extern int D_L04_001B0920_gp __asm__("D_L04_001B0920__gp") __attribute__((section(".sdata")));
extern char D_L04_001B0B20[];
extern char D_L04_001B0B38[];
extern float D_L04_001B2D44 __attribute__((sda));
extern int D_001A7340 __attribute__((sda));

extern int D_L04_001B2D40 __attribute__((sda));
/* The shared HUD rounding helper; the dead mode arm leaves a scheduling boundary. */
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

void func_L04_00417028(void) {
    float s, half, kx, ky;
    int x1, y1, x4, y4, active;
    float fx, fy;
    char text[64], prefix[64];
    func_00115DA8(prefix, func_00288FB8(0x2F82), D_L04_001A8FE4);
    if (D_L04_001B0920_gp / 60 % 60 < 10)
        func_00115DA8(text, D_L04_001B0B20, prefix, func_00288FB8(0x2F83), D_L04_001B0920_gp / 216000, D_L04_001B0920_gp / 3600 % 60, D_L04_001B0920_gp / 60 % 60, D_L04_001B0920_gp / 6 % 10);
    else
        func_00115DA8(text, D_L04_001B0B38, prefix, func_00288FB8(0x2F83), D_L04_001B0920_gp / 216000, D_L04_001B0920_gp / 3600 % 60, D_L04_001B0920_gp / 60 % 60, D_L04_001B0920_gp / 6 % 10);
    active = 1;
    half = 0.5f;
    kx = 112.0f;
    s = D_L04_001B2D44;
    x1 = menu_coord(kx, s, half, active);
    ky = 142.0f;
    y1 = menu_coord(ky, s, half, active);
    func_0027EB88(x1, y1, 50, D_001A7340 - 50, 96, 0x60442D00);
    s = D_L04_001B2D44;
    fx = (float)menu_coord(kx, s, half, active);
    fy = (float)menu_coord(ky, s, half, active);
    func_0029B658(fx, fy, 50.0f, (float)(D_001A7340 - 50), 96, 0x55F0C070);
    x4 = D_001A7340 / 2;
    y4 = label_y((void *)x4, 118.0f, D_L04_001B2D44, half, 1);
    func_0027FBD8(x4, y4, 0x80F0F0F0ULL, text, func_001157AC(text));
}
