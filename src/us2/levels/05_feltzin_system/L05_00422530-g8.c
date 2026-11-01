#include "include_asm.h"

#include "common.h"
extern u8 *D_L05_001B251C;
extern u8 D_00188660[];
extern int D_L05_001A8F00;
extern int D_L05_001A904C __attribute__((sda));
extern int D_L05_001B13F0 __attribute__((sda));
extern int D_L05_001B1350[] MACRO_ADDR;
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
extern void func_US2_0029C548(int, int);
extern int func_L05_00420360(void);
extern void func_L05_004222D8(void);
extern int func_0029B3E0(int, int);
extern void func_L05_00379F48(int);
extern void func_L05_0041FC60(void *);
extern int func_002B49E0(int, int, int, int, u8 *);
typedef struct { u8 pad[0x270]; int id; } MissionState;

/* Once per mission slot: pays the bolt reward for this completion (the table's column is capped
   at the third, times ten when D_001A7A0A is set), then waits for the prompt's buttons. */
void func_US2_L05_00422530(u8 *actor, int mission)
{
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *owner = D_L05_001B251C + (*(int *)(state + 0x24) << 8);
    MissionState *ownerState = *(MissionState **)(owner + 0x68);
    int sound = ownerState->id;
    if (sound != -1) {
        u8 *record = D_00188660 + sound * 0x70;
        if (*(u8 **)(record + 0x88) == owner && record[0x74] != 0)
            func_002E59F8(sound);
    }
    ownerState->id = -1;
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
        func_US2_0029C548(0, (int)func_L05_00420360);
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
    }
    func_L05_00379F48(1);
    if (func_00282948(state + 0x40) == 0) {
        unsigned int buttons = D_00138324;
        int completed = buttons & 0x40;
        if (completed) {
            D_L05_001B13F0 = 0;
            *(int *)(state + 0x40) = 5400;
            func_0027D330(30);
            func_L05_00379F48(0);
            *(int *)(state + 0x58) = 120;
            *(int *)(state + 0x44) = 7200;
            if (D_L05_001B1350_gp[0] != 0) {
                completed = D_L05_001B1350[1];
                if (completed != 0 && D_L05_001B1350[2] != 0)
                    D_L05_001B13EC = 3;
                else if (D_L05_001B1350_gp[0] != 0) {
                    if (completed != 0)
                        D_L05_001B13EC = 2;
                    else
                        D_L05_001B13EC = 1;
                }
            }
            func_L05_0041FC60(actor);
        } else if (buttons & 0x10) {
            func_002B49E0(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(state + 0x40) = 600;
    }
}
