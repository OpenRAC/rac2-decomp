#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x30];
    float f30;
    float f34;
    unsigned char pad1[0x48];
} Rec_42550;
extern float D_L20_001B2124 __attribute__((sda));
extern float D_L20_001B2134 __attribute__((sda));
extern char D_00189E20[];
extern Rec_42550 *D_L20_001B308C;
extern float func_002AA2E8(float *, float, float);
extern void func_002AA800(char *, int, float, float);
extern float func_00282E80(char *, char *);
extern float func_002A89A8(void *, int, float);
extern float func_00283248(float, float);
extern int func_L01_00322288(char *, float);
extern int func_002E5CF8(int, int, char *);

int func_PAL_L20_00447F88(char *arg0) {
    char *s0 = arg0;
    char *s2 = *(char **)(arg0 + 0x68);
    char *s1;
    char *s3;
    float f0;
    int v0;
    Rec_42550 *p;

    func_002AA2E8((float *)(s0 + 0x48), 1.0f, 0.040000003f);

    if (*(u8 *)(s0 + 0x94) == 2) {
        func_002AA800(s2 + 0x1804, 1, 0.0f, D_L20_001B2124 * 0.00017453295f);
    }
    f0 = *(float *)(s2 + 0xF8);
    s1 = D_00189E20;
    *(float *)(s0 + 0x18) += f0;

    *(float *)(s2 + 0xF8) -= *(float *)(s2 + 0x7C);

    if (*(int *)(s1 + 0x2294) == 0x8C) {
        float f0;
        s3 = s1 + 0x80;
        f0 = func_00282E80(s3, s0 + 0x10);
        if (f0 <= 4.0f) {
            f0 = *(float *)(s1 + 0x88);
            f0 += 5.0f;
            *(float *)(s1 + 0x88) = f0;
            f0 = func_002A89A8(s3, 0, 0.5f);
            *(float *)(s1 + 0x88) = f0;
            *(unsigned short *)(s1 + 0x1E0) = 5;
            *(unsigned short *)(s1 + 0x1F0) = 5;
        }
        v0 = *(int *)(s2 + 0x230);
        p = (Rec_42550 *)((v0 << 7) + (unsigned int)D_L20_001B308C);
        f0 = func_00283248(p->f30 - *(float *)(s0 + 0x10), p->f34 - *(float *)(s0 + 0x14));
        func_L01_00322288(s0, f0);

    } else {
        func_L01_00322288(s0, func_00283248(
            *(float *)(s1 + 0x80) - *(float *)(s0 + 0x10),
            *(float *)(s1 + 0x84) - *(float *)(s0 + 0x14)));
    }

    if (*(float *)(s0 + 0x18) <= *(float *)(s2 + 0xE0)) {
        float velocity;
        *(float *)(s0 + 0x18) = *(float *)(s2 + 0xE0);
        func_002E5CF8(0, 0, s0);
        velocity = *(float *)(s2 + 0xF8) * -D_L20_001B2134;
        *(float *)(s2 + 0xF8) = velocity;
        if (velocity < 0.020000001f) {
            *(int *)(s2 + 0xF8) = 0;
            return 1;
        }
    }
    return 0;
}

extern float D_L20_001B212C __attribute__((sda));
extern float D_L20_001B2130 __attribute__((sda));
extern float D_L20_001B2138 __attribute__((sda));
extern float D_L20_001B2128 __attribute__((sda));
extern void *func_002B60B0(unsigned char *, float, float, float, float);
extern float func_00282C10(float);

void func_PAL_L20_00447ED8(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    func_002B60B0((unsigned char *)actor, 0.0f, 0.0f,
                 D_L20_001B212C * 6.981318e-06f,
                 D_L20_001B2130 * 0.0003490659f);
    *(float *)(state + 0x7C) = D_L20_001B2138 * 0.00040000002f;
    *(float *)(state + 0xE0) = func_002A89A8(actor + 0x10, 0, 0.5f);
    qzero(state + 0xF0);
    *(float *)(state + 0xF8) = func_00282C10(*(float *)(state + 0x7C) * 2.0f * D_L20_001B2128);
}
