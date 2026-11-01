#include "include_asm.h"

#include "common.h"
extern float D_L20_001B2418 __attribute__((sda));
extern u32 D_00189E20[] __attribute__((nosda));
extern void func_002A7750(char *, int, int);
extern void *func_002A9640(char *, int, int);
extern float func_PAL_002AA108(char *, char *);
extern int func_002B3BA8(char *, int, void *, int, float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_PAL_L20_004507E0(char *);

void func_PAL_L20_004502D0(char *arg0) {
    char *state;
    char *p;
    u32 *q;
    short t;
    float f;

    state = *(char **)(arg0 + 0x68);
    if (*(u8 *)(arg0 + 0x20) == 0) {
        func_002A7750(arg0, 1, -1);
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        *(int *)(arg0 + 0x98) = 0;
        qcopy((state + 0x180), (arg0 + 0x10));
        *(float *)(arg0 + 0x2C) =
            *(float *)(*(u32 *)(arg0 + 0x24) + 0x24) * D_L20_001B2418;
        *(int *)(state + 0x1B8) = -1;
    }
    if (*(u8 *)(arg0 + 0x20) == 1) {
        return;
    }
    p = func_002A9640(arg0, 0x10000, 0);
    if (p != 0) {
        q = *(u32 **)(p + 0x20);
        if (q != 0) {
            t = *(short *)((char *)q + 0xAA);
            if (t == 0x12F2 || t == 0x12EF) {
                p = 0;
            }
        }
    }
    f = func_PAL_002AA108(arg0, p);
    func_002AA2E8((float *)(state + 0x20), 0.0f, f);
    *(u8 *)(arg0 + 0xA8) = 0xFF;
    if (*(float *)(state + 0x20) == 0.0f) {
        func_PAL_L20_004507E0(arg0);
        *(u8 *)(arg0 + 0xA8) = 0xFF;
        func_002A7750(arg0, 1, -1);
        *(int *)(arg0 + 0x98) = 0;
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    }
    if (*(u8 *)(arg0 + 0x20) == 5) {
        return;
    }
    {
    char *owner = *(char **)(state + 0x1B0);
    if (owner != 0) {
        *(u32 *)(state + 0x150) = (u32)owner;
        qcopy((state + 0x140), (owner + 0x10));
        *(float *)(state + 0x148) = *(float *)(state + 0x148) + 0.5f;
        return;
    }
    }
    func_002B3BA8(arg0, *(int *)(state + 0x160), 0, 0, 1024.0f, 37.0f);
    if (*(u32 *)(state + 0x150) != 0) {
        return;
    }
    {
        u32 *base = (u32 *)D_00189E20;
        *(u32 *)(state + 0x150) = base[0x8A4];
        qcopy((state + 0x140), ((char *)base + 0xD0));
    }
}

extern float D_L20_001B2410 __attribute__((sda));
extern float D_L20_001B2414 __attribute__((sda));
extern float D_L20_001B241C __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002A9288(char *, float);
extern void func_PAL_L20_00450700(char *);

void func_PAL_L20_004504B0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    u16 n = *(u16 *)(arg0 + 0x96);
    float r;

    *(u16 *)(arg0 + 0x96) = n + 1;
    if (*(u8 *)(arg0 + 0x31)) {
        qcopy((arg0 + 0x10), (state + 0x180));
        r = D_L20_001B2414;
        r = func_00283B98(*(float *)(state + 0x1A0), r * 0.0003490659f);
        *(float *)(state + 0x1A0) = r;
        r = func_00283198(r);
        {
            float amount = D_L20_001B241C;
            *(float *)(arg0 + 0x18) = *(float *)(arg0 + 0x18) + D_L20_001B2410 * r;
            func_002A9288(arg0, amount);
        }
    }
    if (((*(u16 *)(arg0 + 0x34)) ^ 1) & 1) {
        func_PAL_L20_00450700(arg0);
    }
}

extern float D_L20_001B2444 __attribute__((sda));
extern float D_L20_001B2448 __attribute__((sda));
extern float D_L20_001B244C __attribute__((sda));
extern float func_00282DF0(void *);
extern void func_002AAC80(void *, float, float, float, float);
extern void func_002AFDD8(char *, char *, char *, char *);
extern int func_L07_00321D68(char *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

float func_PAL_L20_00450568(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *v = state + 0x180;
    char *src = arg0 + 0x10;
    float b0[4] __attribute__((aligned(16)));
    float b1[4] __attribute__((aligned(16)));
    float speed;
    float f;
    float a;
    float gain;
    float pitch;

    func_00282CF0(b0, state + 0x190, state + 0x180);
    speed = func_00282DF0(state + 0xF0);
    f = func_00282DF0(b0);
    func_002AAC80(&speed, f, D_L20_001B2444 * 0.00040000002f,
                  D_L20_001B2444 * 0.00040000002f,
                  D_L20_001B2448 * 0.020000001f);
    func_00282F20(state + 0xF0, b0, speed);
    qcopy(src, v);
    func_L07_00321D68(arg0, state + 0xF0);
    qcopy(v, src);
    func_002AFDD8(arg0, b1, state + 0xF0, 0);
    gain = D_L20_001B244C;
    a = b1[1] * -gain;
    *(float *)(state + 0x1A8) = a;
    *(float *)(state + 0x1AC) = b1[0] * gain;
    if (a > 0.78539824f) {
        *(float *)(state + 0x1A8) = 0.78539824f;
    } else if (a < -0.78539824f) {
        *(float *)(state + 0x1A8) = -0.78539824f;
    }
    pitch = *(float *)(state + 0x1AC);
    if (pitch > 0.78539824f) {
        *(float *)(state + 0x1AC) = 0.78539824f;
    } else if (pitch < 0.0f) {
        *(float *)(state + 0x1AC) = 0.0f;
    }
    return f;
}
