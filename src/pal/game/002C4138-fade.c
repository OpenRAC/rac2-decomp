#include "include_asm.h"

#include "common.h"
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern int func_00283CF0(float);
extern void func_0029FCC0(void *,int,void *);
extern float D_001B5340[];
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern unsigned char *D_001F2634;

/* Follows an animated source joint, easing size and alpha toward their limits.
 * Corresponds to RAC1's update_animated_source_attached_fade_in_out_effect_particle. */
void func_PAL_002C4138(char *p)
{
    char *q;
    float a[4], b[4];
    float f;

    if (!p)
        return;
    q = p + 32;
    if (func_00282978((short *)(p + 10)) || !*(char **)q ||
        *(signed char *)(*(char **)q + 32) < 0) {
        func_002B9180(p);
        return;
    }
    *(short *)(q + 12) = (*(unsigned short *)(q + 12) + 1) & 15;
    if (*(float *)(p + 12) < 159600.0f) {
        *(float *)(p + 12) += 4788.0f;
        if (*(float *)(p + 12) > 159600.0f)
            *(float *)(p + 12) = 159600.0f;
    } else if (*(float *)(p + 12) > 159600.0f) {
        *(float *)(p + 12) -= 19152.0f;
        if (*(float *)(p + 12) < 159600.0f)
            *(float *)(p + 12) = 159600.0f;
    }
    *(float *)(q + 8) += 0.0012f;
    p[8] = func_00283CF0(*(float *)(q + 8) * 255.0f);
    p[2] = D_001F2634[*(short *)(q + 12)];
    if (*(float *)(p + 12) <= 159600.0f || *(float *)(q + 16) > 0.0f)
        *(float *)(q + 4) += *(float *)(q + 16);
    {
        float x;
        if (*(float *)(p + 12) <= 159600.0f) {
            x = *(float *)(q + 4);
            f = 0.3f;
        } else {
            x = *(float *)(q + 4);
            f = 0.15f;
        }
        if (!(f < x)) {
            if (x < 0.0f) {
                func_002B9180(p);
                return;
            }
        } else {
            *(float *)(q + 16) = -*(float *)(q + 16);
            *(float *)(q + 4) = x + *(float *)(q + 16);
        }
    }
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) +
        (func_00283CF0(*(float *)(q + 4) * 256.0f) << 24);
    *(float *)(q + 20) += (1.0f - *(float *)(q + 20)) * 0.21000001f;
    func_0029FCC0(*(void **)q, *(short *)(q + 14), a);
    func_00282CF0(b, D_001B5340, a);
    func_00282F20(b, b, *(float *)(q + 20));
    func_00282CC0(p + 16, (char *)a, (char *)b);
}
