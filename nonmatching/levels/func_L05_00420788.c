/* Complete C near miss; not linked and no matching credit.
 * Default -O2 -G8 -ffunction-sections: 576/592 bytes, USA 0/1.
 * This trial retains the current no-argument reset declaration. Retail passes
 * an actor consistently, also independently confirmed in the corresponding
 * qualified sibling caller. A no-argument definition does not prove absence
 * of an original unused formal. Reopen after review of that repeated-caller
 * contract and canonical declaration; never add an input only for allocation.
 * Stored menu callback returns int(void); dispatcher29B3E0 returns int too.
 * No local buffers. Incomplete count/reward arrays keep measured strides and
 * sanctioned dual GP views without artificial small-data bounds.
 */
#include "common.h"

extern u8 *D_001B251C;
extern u8 D_00188660[];
extern int D_L05_001A8F00;
extern int D_L05_001A904C __attribute__((sda));
extern int D_L05_001B13F0 __attribute__((sda));
extern int D_L05_001B1350[];
extern int D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern int D_L05_001B13F8[][3];
extern int D_L05_001B13F8_gp[][3] SDATA(D_L05_001B13F8);
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B3578;
extern u8 D_001A7A0A;
extern int D_001A79F8;
extern int D_001A79F8_gp SDATA(D_001A79F8);
extern unsigned int D_00138324;
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0027D330(int);
extern void func_0029B758(int, int);
extern int func_L05_00420360(void);
extern void func_L05_004222D8(void);
extern int func_0029B3E0(int, int);
extern void func_L05_00379F48(int);
extern void func_L05_0041FC60(void);
extern int func_002B49E0(int, int, int, int, u8 *);

void func_L05_00420788(u8 *actor, int mission)
{
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *owner = D_001B251C + (*(int *)(state + 0x24) << 8);
    u8 *ownerState = *(u8 **)(owner + 0x68);
    int sound = *(int *)(ownerState + 0x270);
    if (sound != -1) {
        u8 *record = D_00188660 + sound * 0x70;
        if (*(u8 **)(record + 0x88) == owner && record[0x74] != 0)
            func_002E59F8(sound);
    }
    *(int *)(ownerState + 0x270) = -1;
    if (D_L05_001A8F00 == 2)
        return;
    if (func_00282948(state + 0x58) == 0)
        return;
    if (D_L05_001A904C != 0 && D_L05_001B13F0 == 0) {
        int *count;
        int previous;
        int rank;
        int reward;
        func_0027D330(30);
        func_0029B758(0, (int)func_L05_00420360);
        count = &D_L05_001B1350_gp[mission];
        previous = *count;
        rank = previous < 3 ? previous : 2;
        D_L05_001B13F0 = 1;
        D_L05_001B3578 = mission;
        D_L05_001B13AC = 0;
        D_L05_001B13A8 = 0;
        reward = D_L05_001B13F8_gp[mission][rank];
        if (D_001A7A0A != 0)
            reward *= 10;
        D_001A79F8_gp = D_001A79F8 + reward;
        *count = previous + 1;
        func_L05_004222D8();
        func_0029B3E0(0, -1);
        func_L05_00379F48(1);
    }
    if (func_00282948(state + 0x40) != 0) {
        *(int *)(state + 0x40) = 600;
    } else if (D_00138324 & 0x40) {
        D_L05_001B13F0 = 0;
        *(int *)(state + 0x40) = 5400;
        func_0027D330(30);
        func_L05_00379F48(0);
        *(int *)(state + 0x44) = 7200;
        *(int *)(state + 0x58) = 120;
        if (D_L05_001B1350_gp[0] != 0) {
            int second = D_L05_001B1350[1];
            if (second != 0 && D_L05_001B1350[2] != 0)
                D_L05_001B13EC = 3;
            else if (D_L05_001B1350_gp[0] != 0)
                D_L05_001B13EC = second != 0 ? 2 : 1;
        }
        func_L05_0041FC60();
    } else if (D_00138324 & 0x10) {
        func_002B49E0(3, 1, 4, 0, 0);
    }
}
