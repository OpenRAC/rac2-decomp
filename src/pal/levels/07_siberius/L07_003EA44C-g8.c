/* func_PAL_L07_003EA44C, the PAL copy of func_L07_003E61E0: the same C, where the three
 * retimed 0x344 stores (480..600 and 580..600, twice) take PAL's 50 Hz scale. */
#include "common.h"
#define I(p, o) (*(int *)((p)+(o)))
#define H(p, o) (*(unsigned short *)((p)+(o)))
#define B(p, o) (*(unsigned char *)((p)+(o)))
#define F(p, o) (*(float *)((p)+(o)))
extern int D_L07_001B1E08 MACRO_ADDR;
extern int D_L07_001C9780 NOT_SDA;
extern float D_L07_001B0AE8 __attribute__((sda));
extern float D_L07_001B0AEC __attribute__((sda));
extern float D_L07_001B0AF0 __attribute__((sda));
extern float D_L07_001B0AF4 __attribute__((sda));
extern float D_L07_001B0AF8 __attribute__((sda));
extern float D_L07_001B0AFC __attribute__((sda));
extern float D_L07_001B0B00 __attribute__((sda));
extern struct Choice61 {int a, b, c, d;} D_L07_001B0B08;
extern int func_PAL_L07_003EAC48(void *);
extern void func_PAL_L07_003EB508(void *);
extern void func_PAL_L07_003EB0C8(void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424A50(float, float);
extern int func_002B3890(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002B1C20(void *, void *);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int func_002A77E0(int);
extern void func_L02_00332630(void *, void *);
extern float func_00283248(float, float);
extern int func_PAL_L02_00333638(void *, void *, int, float, float, float);
extern void func_PAL_002B5BA8(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_0029F530(void *);
extern void func_L01_00322288(void *, float);
extern int func_002A8C28(void *, void *, int, float, float, int, float, int, int);
extern float func_00283C80(float, float);
extern int func_002A8508(int, int);

/* Update the entity's submode, movement target and timed attack actions. */
void func_PAL_L07_003EA44C(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    float time;
    int result;
    int choices[4];
    if (D_L07_001B1E08 >= 2 && D_L07_001C9780 != I(state, 0x350)) return;
    if (func_PAL_L07_003EAC48(actor)) goto cleanup;
    {
        switch (B(actor, 0x95)) {
        case 0:
            if (I(state, 0x2D4) == 1) {func_002A7750(actor, 6, 2); break;}
            if (I(state, 0x2D0)) {
                func_002A7750(actor, 3, 1);
                I(state, 0x2D0) = 0;
                if (I(state, 0x344) < 250) I(state, 0x344) = ((s32)(func_002A7820(480, 600)) * 5 + 2) / 6;
            }
            break;
        case 1:
            if (I(state, 0x2D4) == 1) func_002A7750(actor, 6, 2);
            break;
        case 2:
            func_L00_00424A08(0, D_L07_001B0AFC, 0.003f);
            func_L00_00424A50(D_L07_001B0B00, 0.003f);
            if (func_002B3890(actor))
                func_002B60B0(actor, D_L07_001B0AEC*0.00040000002f, D_L07_001B0AF0*0.020000001f, D_L07_001B0AF4*6.981318e-06f, D_L07_001B0AF8*0.0003490659f);
            if (I(state, 0x2D4) != 1 && B(actor, 0x20) != 7) {
                if (I(state, 0x338)) func_002A7750(actor, 3, 1);
                else func_002A7750(actor, 4, 1);
                I(state, 0x344) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
            }
            break;
        case 3:
            result = func_002B1C20(actor, state + 0x140);
            if (result & 1) {
                func_PAL_L07_003EB508(actor);
cleanup:
                /* The initialization helper also reaches this shared cleanup. */
                func_0029F338(actor);
                return;
            }
            if (result & 2) {func_002A7750(actor, 7, 2);I(state, 0x344) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;}
            break;
        }
    }
    switch (B(actor, 0x20)) {
    case 1:
        if (func_002B3868(actor) && B(actor, 0x43) != 2) func_PAL_002A7E68(actor, 2, 0, 17);
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) func_002A7750(actor, 2, -1);
        break;
    case 2: {
        float radius, angle;
        if (func_002B3868(actor)) {
            if (B(actor, 0x43) != 8) func_PAL_002A7E68(actor, 8, 0, 17);
            radius = func_002A7878(0, 5);
            angle = func_002A7940();
            F(state, 0x300) = func_00283180(angle)*radius;
            F(state, 0x304) = func_00283198(angle)*radius;
            F(state, 0x308) = 0;
            func_00282CC0(state + 0x300, state + 0x300, state + 0x2F0);
        }
        result = func_PAL_L01_00323068(actor, state + 0x300);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 33) || H(actor, 0x96) > 150) func_002A7750(actor, 1, -1);
        break;
    }
    case 3:
        if (func_002B3868(actor)) {
            *(struct Choice61 *)choices = D_L07_001B0B08;
            if (B(actor, 0x43) != choices[func_002A77E0(4)]) func_PAL_002A7E68(actor, choices[func_002A77E0(4)], 0, 17);
        }
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) func_002A7750(actor, 4, -1);
        break;
    case 4: {
        float radius, angle;
        if (func_002B3868(actor)) {
            if (B(actor, 0x43) != 8) func_PAL_002A7E68(actor, 8, 0, 17);
            radius = func_002A7878(0, 3);
            angle = func_002A7940();
            F(state, 0x300) = func_00283180(angle)*radius;
            F(state, 0x304) = func_00283198(angle)*radius;
            F(state, 0x308) = 0;
            func_00282CC0(state + 0x300, state + 0x300, state + 0x2F0);
        }
        func_L02_00332630(actor, state + 0x210);
        angle = func_00283248(F(state, 0x300)-F(actor, 0x10), F(state, 0x304)-F(actor, 0x14));
        result = func_PAL_L02_00333638(actor, state + 0x300, 16, angle, -1, -1);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 33) || H(actor, 0x96) > 150) func_002A7750(actor, 3, -1);
        break;
    }
    case 6:
        if (func_002B3868(actor) && B(actor, 0x43) != 11) func_PAL_002A7E68(actor, 11, 0, 17);
        func_PAL_002B5BA8(actor, state + 0x210, 0);
        if (func_00282E80(actor + 0x10, state + 0x210) < D_L07_001B0AE8) func_002A7750(actor, 7, -1);
        break;
    case 7:
        if (func_002B3868(actor) && B(actor, 0x43) != 12) func_PAL_002A7E68(actor, 12, 5, 8);
        time = func_0029F530(actor);
        if (time < 19) func_L01_00322288(actor, func_00283248(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14)));
        else if (time<=22) {
            func_002A8C28(actor, *(char **)(state + 0x330)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
            func_002A8C28(actor, *(char **)(state + 0x334)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
        }
        if (B(actor, 0x60) & 2) {
            time = func_00282E80(actor + 0x10, state + 0x210);
            if (D_L07_001B0AE8+0.5f < time ||
                func_00283C80(F(actor, 0xF8), func_00283248(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14))) > 0.349065899848938f)
                func_002A7750(actor, 6, -1);
        }
        break;
    case 9:
        if (!func_002A8508(I(state, 0x2B8), -1) || F(state, 0x20) < *(short *)(state + 0x24)) func_002A7750(actor, 10, -1);
        break;
    case 10:
        if (func_002B3868(actor) && B(actor, 0x43) != 1) func_PAL_002A7E68(actor, 1, 0, 2);
        if (B(actor, 0x60) & 2) func_002A7750(actor, 6, -1);
        break;
    }
    func_PAL_L07_003EB0C8(actor);
}
