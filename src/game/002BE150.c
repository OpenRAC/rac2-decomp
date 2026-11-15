/* func_002BE150: the colour word at +4 keeps its low 24 bits (retail masks it with
 * 0x00FFFFFF before or-ing the new alpha in; the draft dropped the mask), and the
 * 16-byte copy is qcopy(). */
#include "common.h"

extern void func_002B9180(void *);
extern float func_00283CE0(int n);
extern int func_00283CF0(float f);


void func_002BE150(char *a0)
{
    char *s0;
    char *s1;
    unsigned char *p;
    float f0;
    float f1;
    float f2;
    float f3;
    unsigned int c;
    int r;

    s0 = a0;
    if (s0 == 0)
        return;
    s1 = s0 + 0x20;
    p = *(unsigned char **)(s0 + 0x20);
    if (p == 0 || (p[1] & 0x80)) {
        func_002B9180(s0);
        return;
    }
    qcopy(s0 + 0x10, p + 0x10);
    *(unsigned char *)(s0 + 8) = p[8];
    f0 = *(float *)(p + 0xC) * *(float *)(s1 + 4) + *(float *)(s1 + 8);
    *(float *)(s0 + 0xC) = f0;
    f3 = 0.0f;
    f1 = *(float *)(s1 + 0xC) + *(float *)(s1 + 0x14);
    *(float *)(s1 + 0xC) = f1;
    if (f1 < f3) {
        *(float *)(s1 + 0xC) = f3;
        return;
    }
    if (1.0f < f1) {
        *(float *)(s1 + 0xC) = 1.0f;
    }
    c = *(unsigned int *)(s0 + 4) & 0xFFFFFF;
    r = FloatToInt(((IntToFloat((*(unsigned char **)(s0 + 0x20))[7]) / 256.0f)
                       * *(float *)(s1 + 0x10) + *(float *)(s1 + 0xC)) * 256.0f);
    c = c | ((unsigned int)r << 24);
    *(unsigned int *)(s0 + 4) = c;
}
