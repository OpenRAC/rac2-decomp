#include "include_asm.h"

#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_PAL_L00_00415648(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);
extern float D_L00_001B1260 __attribute__((sda));
extern float D_L00_001B1264 __attribute__((sda));
extern unsigned int D_L00_001B1268 __attribute__((sda));
extern float D_L00_001B1280[4][4] __attribute__((sda));
extern int D_0018B068 __attribute__((nosda));
extern int D_00139688[];

/* Draws the object's glow: the level at +0x1A of its state (out of 90) blends the size
   between two tuning values, four times it (at most 96) plus a pulse from the phase at
   +0x20 gives the alpha, and the phase advances by 8 degrees. As many of the four
   offset vectors as the ammo of the item selected by D_0018B068 (capped by the grade from
   func_PAL_L00_00415648) are transformed by the object, and each draws two sprites.
   The global loads pass the float phase store only under -fstrict-aliasing, and
   D_0018B068, far from $gp, is split into %hi/%lo by nosda as retail does. */
void func_PAL_L00_00415498(char *object)
{
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    float fraction, size;
    int alpha, count, n, i;
    unsigned int color;
    fraction = func_00283CE0(*(short *)(state + 0x1a));
    fraction /= func_00283CE0(75);
    if (fraction > 1.0f) fraction = 1.0f;
    size = D_L00_001B1260 + (D_L00_001B1264 - D_L00_001B1260) * fraction;
    alpha = *(short *)(state + 0x1a) << 2;
    if (alpha >= 97) alpha = 96;
    alpha = (unsigned int)(func_00283CF0(func_00283198(*(float *)(state + 0x20)) * 32.0f) + alpha) << 24;
    *(float *)(state + 0x20) = func_00283B98(*(float *)(state + 0x20), 0.139626354f);
    color = alpha | D_L00_001B1268;
    count = D_00139688[D_0018B068];
    n = func_PAL_L00_00415648(object);
    if (n < count) count = n;
    for (i = 0; i < count; i++) {
        func_00283098(position, D_L00_001B1280[i], object + 0xc0);
        func_00282CC0(position, object + 0x10, position);
        func_00281EB8(position, 11, color, 1, size, 0.0f, 0.0f);
        func_00281EB8(position, 11, 0x80808080, 1, size * 0.3f, 0.0f, 0.0f);
    }
}
