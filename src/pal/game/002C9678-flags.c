#include "include_asm.h"

#include "common.h"
extern float func_002A7790(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_00300190(char *, char *);
extern int func_00282978(char *);
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282F20(float *, float *, float);

/* func_002C8A38 is defined in 002C8A38.c. */

/* Like func_002C8A38 with a second vector at +0x30 scaled into the motion. Its
 * address e is an integer: retail loads that vector's last two words only after
 * the first vector is stored, the order alias analysis gives an untraced base. */
void func_PAL_002C9A98(char *p)
{
    char *d = p + 32;
    int e = (int)p + 48;
    float scaled[4], v[4], w[4], tmp[4];
    int color, alpha, fading, spin;
    float size0, size1, speed0, speed1, scale, t, inverse, a, b;
    v[3] = 0;
    v[0] = *(float *)(d + 0); v[1] = *(float *)(d + 4); v[2] = *(float *)(d + 8);
    w[0] = *(float *)(e + 0); w[1] = *(float *)(e + 4); w[2] = *(float *)(e + 8); w[3] = 0;
    color = *(unsigned char *)(d + 12) & 15;
    alpha = (*(unsigned char *)(d + 12) >> 4) | 0x70;
    color |= (color << 16) | (color << 8);
    spin = *(unsigned char *)(d + 13) >> 4;
    fading = *(unsigned char *)(d + 13) & 15;
    size0 = func_00283CE0(*(unsigned char *)(d + 30)) * 1640.625f;
    size1 = func_00283CE0(*(unsigned char *)(d + 31)) * 1640.625f;
    speed0 = func_00283CE0(*(unsigned char *)(d + 28)) * (1.0f / 128);
    speed1 = func_00283CE0(*(unsigned char *)(d + 29)) * (1.0f / 128);
    scale = func_00283CE0(*(unsigned char *)(d + 15)) * (1.0f / 128);
    func_00300190(p + 16, p + 16);
    t = func_00283CE0(*(short *)(p + 10));
    t /= func_00283CE0(*(unsigned char *)(d + 14)); inverse = 1.0f - t;
    if (!fading) {
        *(int *)(p + 4) = func_00283D38(0x103080, color, inverse) | (alpha << 24);
        *(float *)(p + 12) = size0 + (size1 - size0) * inverse;
        speed0 += (speed1 - speed0) * inverse;
        func_00282D30((char *)scaled, (char *)w, scale * func_002A7790(inverse));
    } else {
        speed0 = speed1;
        a = func_00283CE0(alpha); b = func_00283CE0(alpha);
        b *= func_002A7790(inverse);
        *(int *)(p + 4) = color | (func_00283CF0(a - b) << 24);
        func_00282D30((char *)scaled, (char *)w, scale);
    }
    func_00282F20(tmp, v, speed0);
    func_00282CC0(p + 16, p + 16, (char *)tmp);
    func_00282CC0(p + 16, (char *)scaled, p + 16);
    *(unsigned char *)(p + 8) += spin;
    if (func_00282978(p + 10)) {
        if (!fading) {
            *(unsigned char *)(d + 14) = 17;
            *(unsigned char *)(d + 13) |= 1;
            *(short *)(p + 10) = 17;
        } else func_002B9180(p);
    }
}
