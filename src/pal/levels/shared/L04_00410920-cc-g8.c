/* func_PAL_L04_00410920, the PAL copy of func_L04_0040C368: the same C, where rename func_0033BB18 becomes func_002A7878. */
#include "common.h"

typedef unsigned int EffectQuad __attribute__((mode(TI)));
extern const EffectQuad D_L04_001B0980[3];
extern unsigned char D_L04_002BDAC0[], D_L04_002BDB20[];
extern int D_L04_001B097C __attribute__((sda));
extern unsigned char D_00188660[];
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void *func_L00_0033C0D0(void *, void *, void *, void *, int);
extern void func_002E59F8(int);

/* `object` is a late copy of the parameter and `m` a copy of that copy: gcse's copy
   propagation follows one copy per pass, so its PRE pass hashes the addresses off
   `object`'s higher pseudo.  That puts the third vector's reaching register before
   those of m + 0x10 and m + 0xc0, the spill-slot order retail has; the next pass
   restores the parameter and leaves no copy in the output. */
void func_PAL_L04_00410920(unsigned char *self)
{
    EffectQuad offsets[3];
    float velocity[4];
    float point[4], first[4], second[4], third[4];
    unsigned char *p;
    unsigned char *parameters;
    float strength, scale, fade, spread;
    int i, handle;

    *(EffectQuad *)velocity = 0;
    offsets[0] = D_L04_001B0980[0];
    offsets[1] = D_L04_001B0980[1];
    offsets[2] = D_L04_001B0980[2];
    {
        unsigned char *object = self;

        p = *(unsigned char **)(object + 0x68);
        if (object[0xbc] == 3 || object[0xbc] == 4) D_L04_001B097C = 0;
        strength = *(float *)(p + 0x27c) * 8.333333f;
        if (strength > 1.0f) strength = 1.0f;
        else if (strength < 0.0f) strength = 0.0f;
        scale = *(float *)(p + 0x30c) * 2.4999998f;
        if (scale > 1.0f) scale = 1.0f;
        else if (scale < 0.5f) scale = 0.5f;
        {
            unsigned char *m = object;

            for (i = 0; i < 3; i++) {
                if (i == 1) parameters = D_L04_002BDB20;
                else parameters = D_L04_002BDAC0;
                func_00283098(point, &offsets[i], m + 0xc0);
                func_00282CC0(point, point, m + 0x10);
                point[3] = 0.0f;
                qcopy(first, point);
                qcopy(second, point);
                qcopy(third, point);
                spread = strength * 0.01f;
                spread += 0.005f;
                func_002ACB48(first, spread);
                func_002ACB48(second, spread);
                func_002ACB48(third, strength * 0.009f + 0.005f);
                if (strength > 0.0f || D_L04_001B097C > 0 || *(int *)(p + 0x278) > 0) {
                    if (strength == 0.0f && *(int *)(p + 0x278) == 0) {
                        fade = (float)D_L04_001B097C * 0.033333335f;
                        D_L04_001B097C--;
                    } else {
                        fade = 1.0f;
                        D_L04_001B097C = 30;
                    }
                    spread = strength * 0.01f;
                    spread += 0.01f;
                    func_002ACB48(first, spread);
                    func_002ACB48(second, spread);
                    velocity[0] = (func_002A7878(3.0f, 5.25f) + strength * 2.0f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    func_L00_0033C0D0(m, first, velocity, parameters + 0x30, 1);
                    velocity[0] = (func_002A7878(1.0f, 2.25f) + strength * 3.0f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    func_L00_0033C0D0(m, second, velocity, parameters + 0x40, 1);
                    func_L00_0033C0D0(m, point, velocity, parameters + 0x50, 1);
                } else {
                    handle = *(int *)(p + 0x714);
                    if (handle != -1) {
                        unsigned char *record = D_00188660 + handle * 0x70;
                        if (*(unsigned char **)(record + 0x88) == m && record[0x74]) func_002E59F8(handle);
                    }
                    *(int *)(p + 0x714) = -1;
                    velocity[0] = (func_002A7878(1.5f, 2.5f) + strength * 1.5f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    func_L00_0033C0D0(m, first, velocity, parameters, 1);
                    velocity[0] = (func_002A7878(1.5f, 2.5f) + strength * 2.45f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    func_L00_0033C0D0(m, second, velocity, parameters + 0x10, 1);
                    velocity[0] = (func_002A7878(1.5f, 2.5f) + strength * 3.25f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    func_L00_0033C0D0(m, third, velocity, parameters + 0x20, 1);
                }
            }
        }
    }
}
