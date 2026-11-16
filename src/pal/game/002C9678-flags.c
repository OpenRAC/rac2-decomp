#include "include_asm.h"

#include "common.h"
extern float math_square(float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void vec_transform_or_copy(char *, char *);
extern int FastDecTimer(char *);
extern void part_kill(char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern void vec_scale_to_length(float *, float *, float);

/* func_002C8A38 is defined in 002C8A38.c. */

/* Like func_002C8A38 with a second vector at +0x30 scaled into the motion. Its
 * address e is an integer: retail loads that vector's last two words only after
 * the first vector is stored, the order alias analysis gives an untraced base. */
void part_update_color_changing_pal(char *p)
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
    size0 = IntToFloat(*(unsigned char *)(d + 30)) * 1640.625f;
    size1 = IntToFloat(*(unsigned char *)(d + 31)) * 1640.625f;
    speed0 = IntToFloat(*(unsigned char *)(d + 28)) * (1.0f / 128);
    speed1 = IntToFloat(*(unsigned char *)(d + 29)) * (1.0f / 128);
    scale = IntToFloat(*(unsigned char *)(d + 15)) * (1.0f / 128);
    vec_transform_or_copy(p + 16, p + 16);
    t = IntToFloat(*(short *)(p + 10));
    t /= IntToFloat(*(unsigned char *)(d + 14)); inverse = 1.0f - t;
    if (!fading) {
        *(int *)(p + 4) = FastTweenColor(0x103080, color, inverse) | (alpha << 24);
        *(float *)(p + 12) = size0 + (size1 - size0) * inverse;
        speed0 += (speed1 - speed0) * inverse;
        FastVecScale((char *)scaled, (char *)w, scale * math_square(inverse));
    } else {
        speed0 = speed1;
        a = IntToFloat(alpha); b = IntToFloat(alpha);
        b *= math_square(inverse);
        *(int *)(p + 4) = color | (FloatToInt(a - b) << 24);
        FastVecScale((char *)scaled, (char *)w, scale);
    }
    vec_scale_to_length(tmp, v, speed0);
    FastVecAdd(p + 16, p + 16, (char *)tmp);
    FastVecAdd(p + 16, (char *)scaled, p + 16);
    *(unsigned char *)(p + 8) += spin;
    if (FastDecTimer(p + 10)) {
        if (!fading) {
            *(unsigned char *)(d + 14) = 17;
            *(unsigned char *)(d + 13) |= 1;
            *(short *)(p + 10) = 17;
        } else part_kill(p);
    }
}
