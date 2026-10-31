/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections.
 * us: 0/4; us2: 0/4; pal: absent.
 * 944/940 bytes; frame 0xA0. Real seven-child state, three complete vectors and spring inputs
 * retained. Scalar initialization/store and loop induction schedules differ. The registered
 * callback is now canonical after the independent twelve-placement entry repair.
 * Reopen: Independent scalar/child-pointer lifetime and initializer scheduling witness.
 */
#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int D_L05_00221D94;
extern int D_001A79F0;
extern u8 D_0019B2E8[];
extern char *D_L05_001B251C;
extern float D_L05_001B1680[] SDATA(D_L05_001B1680);
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

void func_L05_0042AC30(u8 *actor)
{
    Vector position, step, rotation;
    u8 *state = *(u8 **)(actor + 0x68);
    int i;
    char **child;
    float *tuning = D_L05_001B1680;
    if (D_L05_00221D94 != 0 || !(D_0019B2E8[(D_001A79F0 << 4) + actor[0xB0]] & 0x80)) {
        func_0029F338(actor);
        return;
    }
    if (actor[0x20] == 0) {
        float span;
        float phase = 0.0f;
        *(u16 *)(actor + 0x34) |= 0x41;
        func_002833F0(actor + 0xC0, actor + 0xF0);
        actor[0x20] = 1;
        actor[0x30] = 0xFF;
        *(float *)(actor + 0x2C) = *(float *)(*(char **)(actor + 0x24) + 0x24) * (tuning[0] * tuning[2]);
        span = tuning[7] * 6.0f;
        tuning[4] = tuning[25] = tuning[30] = tuning[31] = 0.0f;
        tuning[33] = tuning[35] = tuning[21] = tuning[26] = 0.0f;
        *(float *)(state + 0x20) = span;
        func_00282D30(&position, actor + 0xC0, span);
        func_00282CC0(&position, &position, actor + 0x10);
        *(float *)(state + 0x24) = position.f[0];
        *(float *)(state + 0x28) = position.f[1];
        *(float *)(state + 0x2C) = position.f[2];
        span *= 0.14285715f;
        func_00282D30(&step, actor + 0xC0, -span);
        func_002AB600(&rotation, actor + 0xC0);
        child = (char **)state;
        for (i = 6; i >= 0; i--) {
            *child++ = func_L05_0042BCE0(&position, &rotation, tuning[0], phase);
            phase += span;
            func_00282CC0(&position, &position, &step);
        }
        D_L05_001B1728 = actor;
    }
    child = (char **)state;
    for (i = 6; i >= 0; i--, child++) {
        u8 *object = (u8 *)*child;
        if (object != 0) {
            float amount = tuning[3] * 0.016666668f;
            u8 *objectState;
            amount += amount;
            func_00282D30(&position, actor + 0xC0, -amount);
            func_00282CC0(object + 0x10, object + 0x10, &position);
            objectState = *(u8 **)(object + 0x68);
            *(float *)(objectState + 0x10) += amount;
            if (*(float *)(state + 0x20) <= *(float *)(objectState + 0x10)) {
                *(float *)(object + 0x10) = *(float *)(state + 0x24);
                *(float *)(object + 0x14) = *(float *)(state + 0x28);
                *(int *)(object + 0x1C) = 0;
                *(float *)(object + 0x18) = *(float *)(state + 0x2C);
                *(int *)(objectState + 0x10) = 0;
            }
        }
    }
    if (*(int *)(*(char **)(D_L05_001B251C + (*(int *)(state + 0x1C) << 8) + 0x68) + 0x34) != 0) {
        tuning[3] = func_002702C8(tuning + 4, tuning[3], tuning[6], 0.02f, 0.2f, 0.0f);
        tuning[22] = func_002702C8(tuning + 25, tuning[22], tuning[24], 0.02f, 0.2f, 0.0f);
        tuning[27] = func_002702C8(tuning + 30, tuning[27], tuning[29], 0.02f, 0.2f, 0.0f);
    } else {
        tuning[3] = func_002702C8(tuning + 4, tuning[3], tuning[5], 0.02f, 0.2f, 0.0f);
        tuning[22] = func_002702C8(tuning + 25, tuning[22], tuning[23], 0.02f, 0.2f, 0.0f);
        tuning[27] = func_002702C8(tuning + 30, tuning[27], tuning[28], 0.02f, 0.2f, 0.0f);
    }
    func_L00_002E6CF0(func_L05_0042AFE0, actor);
}
