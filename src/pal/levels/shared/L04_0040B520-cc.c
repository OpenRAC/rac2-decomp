/* func_PAL_L04_0040B520, the PAL copy of func_L04_00407078: the same C, where wrap func_002A7878(60.0f, 120.0f) (({e}) * 5.0f + 2.0f) * 0.. */
#include "common.h"
extern unsigned char *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002A7A00(void *, float, float);
extern void func_002A0F48(void *);

unsigned char *func_PAL_L04_0040B520(unsigned char *parent, int kind, void *position, void *rotation, int lifetime, int flags, void *velocity, void *spin, void *scale, float gravity, float width)
{
    float tmp[4];
    unsigned char *m = func_0029EFD0(kind);
    unsigned char *p;
    float angle, speed, unit;
    if (m) {
        float ratio = *(float *)(parent + 0x2c) / *(float *)(*(unsigned char **)(parent + 0x24) + 0x24);
        *(float *)(m + 0x2c) = *(float *)(*(unsigned char **)(m + 0x24) + 0x24) * ratio;
        m[0x31] = 1;
        *(unsigned short *)(m + 0x34) |= 0x100;
        p = *(unsigned char **)(m + 0x68);
        *(unsigned long long *)(m + 0x38) = *(unsigned long long *)(parent + 0x38);
        m[0x20] = 1;
        qcopy((m + 0x10), position);
        func_002833F0(m + 0xc0, rotation);
        m[0x30] = 255;
        *(short *)(m + 0x32) = 128;
        *(int *)(m + 0x98) = 0;
        if (lifetime == 0) *(short *)(p + 0x30) = func_00283CF0(((func_002A7878(60.0f, 120.0f)) * 5.0f + 2.0f) * 0.16666667f);
        else *(short *)(p + 0x30) = lifetime;
        *(int *)(p + 0x34) = flags;
        *(short *)(p + 0x32) = 0;
        if (*(float *)(p + 0x38) == 0.0f) *(float *)(p + 0x38) = func_002A7878(10.0f, 15.0f) * 0.00040000002f;
        else *(float *)(p + 0x38) = gravity;
        if (width != 0.0f) {
            *(float *)(p + 0x3c) = width;
            *(int *)(p + 0x34) |= 4;
        }
        if (func_00282DF0(velocity) == 0.0f) {
            angle = func_002A7940();
            unit = 0.020000001f;
            speed = func_002A7878(2.0f, 4.0f) * unit;
            tmp[0] = func_00283180(angle) * speed;
            tmp[1] = func_00283198(angle) * speed;
            tmp[2] = 0.0f;
            tmp[2] = func_002A7878(5.0f, 8.0f) * unit;
            qcopy(p, tmp);
        } else qcopy(p, velocity);
        if (func_00282DF0(spin) == 0.0f) {
            func_002A7A00(tmp, 0.062831864f, 0.12566373f);
            qcopy((p + 0x10), tmp);
        } else qcopy((p + 0x10), spin);
        if (func_00282DF0(scale) == 0.0f && ((float *)scale)[3] == 0.0f) {
            float f;
            qcopy(tmp, (*(unsigned char **)(m + 0x24) + 0x30));
            f = *(float *)(m + 0x2c) * 0.0009765625f;
            func_00282D30(tmp, tmp, f);
            tmp[3] = tmp[3] * f;
            qcopy((p + 0x20), tmp);
        } else qcopy((p + 0x20), scale);
        func_002A0F48(m);
    }
    return m;
}
