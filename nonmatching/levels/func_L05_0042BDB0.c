/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections.
 * us: 0/3; us2: absent; pal: absent.
 * 1024/1020 bytes; frame 0x40. All three states, four phases, item/sound updates and four
 * repeated cleanup calls retained. Actual pointer copies and 32-bit color/state widths are kept.
 * Source/call/GP scalar ordering differs.
 * Reopen: Measured state CFG and scratch lifetime evidence.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_001A79F0;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 D_0019B278[];
extern float D_L05_001B1738[] SDATA(D_L05_001B1738);
extern int D_L05_001B1778 __attribute__((sda));
extern int D_L05_001B177C __attribute__((sda));
extern u8 *D_L05_001B1780 __attribute__((sda));
extern int D_L05_001B2170 __attribute__((sda));
extern int D_L05_001B1F68 __attribute__((sda));
extern int D_L05_001B2268;
extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern float func_002A7940(void);
extern void func_L01_00397950(void *);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern void func_L01_00397A28(void *);
extern int func_002A77E0(int);
extern void func_L01_00417090(void *);
extern float func_00282E48(void *, void *);
extern void func_002B0A18(int, int);
extern int func_0029B3E0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_0029F338(void *);
extern void func_L01_00397C98(void *);
extern void func_L01_00397870(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_002D2168(int, int, float);
extern int func_00282948(void *);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_003355A8(int);

void func_L05_0042BDB0(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    float *tuning = D_L05_001B1738;
    int i;
    switch (actor[0x20]) {
    case 0:
        if (*(int *)state == -1 || D_0019B278[(D_001A79F0_gp << 2) + *(int *)state] != 0) {
            func_0029F338(actor);
            return;
        }
        qcopy(state + 0x10, actor + 0x10);
        *(float *)(state + 0x1C) = *(float *)(actor + 0xF8);
        *(float *)(actor + 0xF0) = func_002A7940();
        *(float *)(actor + 0xF4) = func_002A7940();
        *(float *)(actor + 0xF8) = func_002A7940();
        *(float *)(actor + 0xFC) = func_002A7940();
        *(float *)(state + 0x68) = tuning[4] * 0.00029088825f;
        *(float *)(state + 0x64) = tuning[5] * 0.00029088825f;
        *(float *)(state + 0x60) = tuning[6] * 0.00029088825f;
        if (*(s16 *)(actor + 0x32) < 64)
            *(s16 *)(actor + 0x32) = 64;
        actor[0x20] = 1;
        func_L01_00397950(actor);
        return;
    case 1:
        *(float *)(actor + 0x2C) = *(float *)(*(char **)(actor + 0x24) + 0x24) * tuning[0];
        *(float *)(actor + 0x18) = *(float *)(state + 0x18) + tuning[1] +
                                  tuning[2] * func_00283198(*(float *)(actor + 0xFC));
        *(float *)(actor + 0xF0) = func_00283B98(*(float *)(actor + 0xF0), tuning[4] * 0.00029088825f);
        *(float *)(actor + 0xF4) = func_00283B98(*(float *)(actor + 0xF4), tuning[5] * 0.00029088825f);
        *(float *)(actor + 0xF8) = func_00283B98(*(float *)(actor + 0xF8), tuning[6] * 0.00029088825f);
        *(float *)(actor + 0xFC) = func_00283B98(*(float *)(actor + 0xFC), tuning[7] * 0.00029088825f);
        func_L01_00397A28(actor);
        if (func_002A77E0(D_L05_001B1778) == 0)
            func_L01_00417090(actor);
        if (func_00282E48(D_L05_001B1780 + 0x10, actor + 0x10) < 1.5f) {
            D_L05_001B2170 = 180;
            func_002B0A18(0x124B, -1);
            D_0019B278[(D_001A79F0 << 2) + *(int *)state] = 1;
            D_L05_001B177C++;
            func_0029B3E0(0, -1);
            func_002E5CF8(1, 0, actor);
            func_0029F338(actor);
        }
        return;
    case 2:
        D_L05_001B2268 = 1;
        func_L01_00397C98(actor);
        qcopy(actor + 0x10, D_00189EA0);
        qcopy(actor + 0xF0, D_00189EA0 + 0x10);
        if (actor[0x42] == 1) {
            func_L01_00397870(actor);
            if (func_002A77E0(10) == 0)
                func_L01_00417090(actor);
            if (actor[0x60] & 2) {
                if (actor[0x43] != 0)
                    func_002A7470(actor, 0, 0, 0);
                actor[0x31] = 0;
                *(u16 *)(actor + 0x34) |= 1;
                for (i = 3; i >= 0; i--)
                    func_L01_00417090(actor);
            }
        }
        if (*(int *)(D_00189E20 + 0xC28) & 2)
            func_L00_002D2168(0, 0, 30.0f);
        if (actor[0x42] == 0 && func_00282948(state + 0x6C) != 0) {
            D_L05_001B2170 = 180;
            func_002B0A18(0x1234, -1);
            D_0019B278[(D_001A79F0 << 2) + *(int *)state] = 1;
            D_L05_001B177C++;
            D_L05_001B1F68 = 0;
            func_L00_002B9D60(D_00189E20 + 0x80, D_00189E20 + 0x90, 0, 0);
            func_003355A8(0);
            func_0029B3E0(0, -1);
            func_0029F338(actor);
        }
        break;
    }
}
