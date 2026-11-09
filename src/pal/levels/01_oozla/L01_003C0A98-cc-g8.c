/* func_PAL_L01_003C0A98, the PAL copy of func_L01_003BCEC8: the same C. */
#include "common.h"

/* Small data reached through $gp: these are only one instruction at -G8. */
/* Oozla debris update. */
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float D_L01_001AFE30 __attribute__((sda));
extern char D_L01_001BF920[];

void func_PAL_L01_003C0A98(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float saved, scale, tilt;

    qcopy(pos, obj + 0x10);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_0029F338(obj);
        return;
    case 1:
        if (func_00282948(s + 0x30)) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(8.666667f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (func_00282948(s + 0x30)) {
            func_0029F338(obj);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(obj + 0x23) = func_00283CF0((float)*(int *)(s + 0x30) * 14.76923f);
        break;
    }
    *(float *)(s + 0x40) = func_00283B98(*(float *)(s + 0x40), 0.04188791f);
    *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                           *(float *)(s + 0x18) * func_00283198(*(float *)(s + 0x40)));
    *(float *)(obj + 0xF0) += (*(float *)(s + 0x44) - *(float *)(obj + 0xF0)) * 0.02f;
    if (*(unsigned char *)(obj + 0x20) != 2) {
        tilt = func_00283180(*(float *)(s + 0x40)) * 0.17453295f;
        scale = D_L01_001AFE30;
        *(float *)(obj + 0xF4) = tilt;
        saved = *(float *)(s + 8);
        *(float *)(s + 8) = 0.0f;
        func_00282D30(s, s, scale);
        *(float *)(s + 8) = saved;
        func_00282CC0(obj + 0x10, obj + 0x10, s);
        *(float *)(s + 8) -= *(float *)(s + 0x38);
        if (*(float *)(s + 8) < *(float *)(s + 0x3C))
            *(float *)(s + 8) = *(float *)(s + 0x3C);
    } else {
        *(float *)(obj + 0xF4) += (0.17453295f - *(float *)(obj + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (func_002761F8(pos, obj + 0x10, 2, obj, 0)) {
        qcopy(obj + 0x10, D_L01_001BF920);
        /* qzero(state + 8): retail passes a misaligned pointer here (original bug; sq ignores the low four address bits). Allowed by owner ruling (2026-11-09). */
        qzero(s + 8);
        *(int *)(s + 0x38) = 0;
        qzero(s + 0x10);
        if (*(unsigned char *)(obj + 0x20) != 2) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(8.666667f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
        }
    }
}
