#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad[0x60];
    u8 * particles[8];
} Controller;
typedef struct {
    u8 pad[4];
    int colour;
    u8 pad08[4];
    float size;
} ParticleHeader;
typedef struct {
    u8 pad[8];
    float radius;
    float angle;
} ParticleState;
extern float ref_L22_003FC048_00[8] __attribute__((sda));
extern float ref_L22_003FC048_01 __attribute__((sda)), ref_L22_003FC048_02 __attribute__((sda)), ref_L22_003FC048_03 __attribute__((sda));
extern float ref_L22_003FC048_04 __attribute__((sda)), ref_L22_003FC048_05 __attribute__((sda));
extern int ref_L22_003FC048_07 __attribute__((sda));
extern u8 ref_L22_003FC048_08 __attribute__((sda));
extern u8 * D_L22_001B1D6C;
extern u8 D_L22_001B9C80[];
extern float func_00283198(float), func_00283B98(float, float), func_00282E80(void *, void *);
extern void func_L22_003FBFD0(void), func_L22_003FBF00(void *, void *, int), func_L22_003FC338(void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_00282D30(void *, void *, float), func_00282CC0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern u8 * func_002C36D0(void *, int, int, int);

/* Update existing particles and maintain eight persistent effect slots. */
void func_PAL_L22_00400890(u8 * obj) {
    float p[4], tmp[4], point[4], origin[4], zero[4];
    Controller * ctl = *(Controller **)(obj + 0x68);
    int i, count;
    float distance;
    u8 **slot;

    if (obj[0x20] == 0) {
        int j;
        for (j = 0; j < 8; j++) {
            u8 * v = ctl->particles[j];
            if (v) {
                u8 * s = v + 0x20;
                *(float *)(s + 8) = ref_L22_003FC048_01 * func_00283198(*(float *)(s + 12)) + ref_L22_003FC048_02;
                *(float *)(s + 12) = func_00283B98(*(float *)(s + 12), ref_L22_003FC048_00[j]);
            }
        }
    }
    if (D_L22_001B1D6C == obj)
        func_L22_003FBFD0();
    qcopy(p, obj + 0x10);
    func_00282D30(tmp, obj + 0xE0, ref_L22_003FC048_03);
    func_00282CC0(p, p, tmp);
    p[3] = 1.0f;
    if (func_00283DB8(p, 64.0f) < 0)
        return;
    func_L00_002E6CF0(func_L22_003FC338, obj);
    if (obj[0x20])
        return;
    distance = func_00282E80(obj + 0x10, D_L22_001B9C80);
    if (distance > 30.0f)
        count = 2;
    else if (distance > 10.0f)
        count = 17;
    else
        count = 33;
    for (i = 0, slot = ctl->particles; i < 8; i++, slot++) {
        u8 * v, *old;
        func_L22_003FBF00(obj, point, i);
        v = func_002C36D0(point, count, 2, 0);
        if (v) {
            u8 * s = v + 0x20;
            qcopy(origin, obj + 0x10);
            qzero_nc(zero);
            func_00282CC0(point, point, zero);
            *(float *)(s + 0x10) = *(float *)(v + 0x10)-origin[0];
            *(float *)(s + 0x14) = *(float *)(v + 0x14)-origin[1];
            *(float *)(s + 0x18) = *(float *)(v + 0x18)-origin[2];
            if (obj[0x20] == 0)
                *(u8 **)(s + 4) = obj;
            else
                *(u8 **)(s + 4) = *(u8 **)(obj + 0xB8);
            ((ParticleHeader *)v)->colour = ref_L22_003FC048_07;
            ((ParticleHeader *)v)->size = ref_L22_003FC048_04;
        }
        old = *slot;
        if (!old) {
            *slot=func_002C36D0(point,0,1,0);
            v = *slot;
            if (v) {
                ParticleState * s = (ParticleState *)(v + 0x20);
                s->angle = 0.0f;
                s->radius = ref_L22_003FC048_02;
                ((ParticleHeader *) * slot)->size = ref_L22_003FC048_05;
                ((ParticleHeader *) * slot)->colour = ref_L22_003FC048_07;
            }
        } else {
            qcopy(old + 0x10, point);
            old[8] += ref_L22_003FC048_08;
        }
    }
}
