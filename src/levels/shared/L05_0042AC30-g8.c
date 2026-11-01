#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int D_L05_00221D94[];
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0019B2E8[];
extern char *D_L05_001B251C;
extern float D_L05_001B1680 __attribute__((sda));
extern float D_L05_001B1688 __attribute__((sda));
extern float D_L05_001B168C __attribute__((sda));
extern float D_L05_001B1690 __attribute__((sda));
extern float D_L05_001B1694 __attribute__((sda));
extern float D_L05_001B1698 __attribute__((sda));
extern float D_L05_001B169C __attribute__((sda));
extern float D_L05_001B16D4 __attribute__((sda));
extern float D_L05_001B16D8 __attribute__((sda));
extern float D_L05_001B16DC __attribute__((sda));
extern float D_L05_001B16E0 __attribute__((sda));
extern float D_L05_001B16E4 __attribute__((sda));
extern float D_L05_001B16E8 __attribute__((sda));
extern float D_L05_001B16EC __attribute__((sda));
extern float D_L05_001B16F0 __attribute__((sda));
extern float D_L05_001B16F4 __attribute__((sda));
extern float D_L05_001B16F8 __attribute__((sda));
extern float D_L05_001B16FC __attribute__((sda));
extern float D_L05_001B1704 __attribute__((sda));
extern float D_L05_001B170C __attribute__((sda));
extern void *D_L05_001B1728 __attribute__((sda));
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AB600(void *, void *);
extern char *func_L05_0042BCE0(void *, void *, float, float);
extern float func_002702C8(float *, float, float, float, float, float);
extern void func_L00_002E6CF0(void (*)(void *), void *);
/* The registered entry includes its measured pre-prologue F1 load. */
extern void func_L05_0042AFE0(void *);

typedef union { float f[0x40]; int i[0x40]; u16 uh[0x80]; } Fields;

void func_L05_0042AC30(u8 *actor)
{
    Vector position, step, rotation;
    u8 *state = *(u8 **)(actor + 0x68);
    if (D_L05_00221D94[0] != 0 || (D_0019B2E8[actor[0xB0] + (D_001A79F0 << 4)] & 0x80)) {
        func_0029F338(actor);
        return;
    }
    if (actor[0x20] == 0) {
        float span;
        float phase = 0.0f;
        ((Fields *)actor)->uh[0x34 / 2] |= 0x41;
        func_002833F0(actor + 0xC0, actor + 0xF0);
        actor[0x30] = 0xFF;
        actor[0x20] = 1;
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * (D_L05_001B1680 * D_L05_001B1688);
        span = D_L05_001B169C;
        span *= 6.0f;
        D_L05_001B16FC = D_L05_001B16F8 = D_L05_001B16E4 = D_L05_001B1690 = 0.0f;
        D_L05_001B16E8 = D_L05_001B16D4 = D_L05_001B170C = D_L05_001B1704 = 0.0f;
        ((Fields *)state)->f[0x20 / 4] = span;
        func_00282D30(&position, actor + 0xC0, span);
        func_00282CC0(&position, &position, actor + 0x10);
        {
            float *head = (float *)(state + 0x24);
            head[0] = position.f[0];
            head[1] = position.f[1];
            head[2] = position.f[2];
        }
        span *= 0.14285715f;
        func_00282D30(&step, actor + 0xC0, -span);
        func_002AB600(&rotation, actor + 0xC0);
        {
        char **child = (char **)state;
        int i;
        for (i = 6; i >= 0; i--, child++) {
            *child = func_L05_0042BCE0(&position, &rotation, D_L05_001B1680, phase);
            phase += span;
            func_00282CC0(&position, &position, &step);
        }
        }
        D_L05_001B1728 = actor;
    }
    {
    int j;
    for (j = 0; j < 7; j++) {
        u8 *object = ((u8 **)state)[j];
        if (object != 0) {
            float amount = D_L05_001B168C * 0.016666668f;
            float *pos = (float *)(object + 0x10);
            u8 *objectState;
            amount += amount;
            func_00282D30(&position, actor + 0xC0, -amount);
            func_00282CC0(pos, pos, &position);
            objectState = *(u8 **)(object + 0x68);
            ((Fields *)objectState)->f[0x10 / 4] += amount;
            if (((Fields *)state)->f[0x20 / 4] <= ((Fields *)objectState)->f[0x10 / 4]) {
                float *base = (float *)(state + 0x24);
                pos[0] = base[0];
                pos[1] = base[1];
                pos[2] = base[2];
                pos[3] = 0;
                ((Fields *)objectState)->i[0x10 / 4] = 0;
            }
        }
    }
    }
    if (*(int *)(*(char **)(D_L05_001B251C + (((Fields *)state)->i[0x1C / 4] << 8) + 0x68) + 0x34) != 0) {
        D_L05_001B168C = func_002702C8(&D_L05_001B1690, D_L05_001B168C, D_L05_001B1698, 0.02f, 0.2f, 0.0f);
        D_L05_001B16D8 = func_002702C8(&D_L05_001B16E4, D_L05_001B16D8, D_L05_001B16E0, 0.02f, 0.2f, 0.0f);
        D_L05_001B16EC = func_002702C8(&D_L05_001B16F8, D_L05_001B16EC, D_L05_001B16F4, 0.02f, 0.2f, 0.0f);
    } else {
        D_L05_001B168C = func_002702C8(&D_L05_001B1690, D_L05_001B168C, D_L05_001B1694, 0.02f, 0.2f, 0.0f);
        D_L05_001B16D8 = func_002702C8(&D_L05_001B16E4, D_L05_001B16D8, D_L05_001B16DC, 0.02f, 0.2f, 0.0f);
        D_L05_001B16EC = func_002702C8(&D_L05_001B16F8, D_L05_001B16EC, D_L05_001B16F0, 0.02f, 0.2f, 0.0f);
    }
    func_L00_002E6CF0(func_L05_0042AFE0, actor);
}
