/* Complete C near miss; not linked and no matching credit.
 * Default -O2 -G8 -ffunction-sections: 596/600 bytes, USA 0/1.
 * Independent retail sibling callers consistently pass the actor to the reset,
 * supporting the genuine unused pointer formal despite a prior void(void)
 * definition. No synthetic actor read or per-use alias is needed. Actual
 * callback returns int(void), and dispatcher29B3E0 returns int too.
 * Snapshotting the mode before the sound-handle reset restores the retail
 * actor/predicate lifetime. Full array/record strides and incomplete GP views
 * preserve real footprints; no local buffers or artificial small-data bounds.
 * Remaining differences: edge-specific mode load, controller mask lifetime,
 * independent timer store order and conditional completion-state branch.
 * Fine GCSE-edge/interblock controls, G0 scalar model, no-expensive and first
 * scheduling control do not close the audited level5 family; no replay needed.
 * Reopen with new predicate/assembler-address lifetime evidence.
 */
#include "common.h"

extern u8 *D_001B251C;
extern u8 D_00188660[];
extern int D_L10_001A8F00;
extern int D_L10_001A904C __attribute__((sda));
extern int D_L10_001B1440 __attribute__((sda));
extern int D_L10_001B1390[] MACRO_ADDR;
extern int D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
extern int D_L10_001B1448[][3];
extern int D_L10_001B1448_gp[][3] SDATA(D_L10_001B1448);
extern int D_L10_001B13EC __attribute__((sda));
extern int D_L10_001B13E8 __attribute__((sda));
extern int D_L10_001B143C __attribute__((sda));
extern int D_L10_001B355C;
extern u8 D_001A7A0A;
extern int D_001A79F8;
extern int D_001A79F8_gp SDATA(D_001A79F8);
extern unsigned int D_00138324;
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0027D330(int);
extern void func_0029B758(int, int);
extern int func_L10_004239A0(void);
extern void func_L10_00425888(void);
extern int func_0029B3E0(int, int);
extern void func_L05_00379F48(int);
/* Independent sibling retail callers pass the same actor to this reset. */
extern void func_L10_00423500(void *);
extern int func_002B49E0(int, int, int, int, u8 *);

void func_L10_00423DC8(u8 *actor, int mission)
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
    {
        int mode = D_L10_001A8F00;
        *(int *)(ownerState + 0x270) = -1;
        if (mode == 2)
            return;
    }
    if (func_00282948(state + 0x58) == 0)
        return;
    if (D_L10_001A904C != 0 && D_L10_001B1440 == 0) {
        int *count;
        int previous;
        int rank;
        int reward;
        func_0027D330(30);
        func_0029B758(0, (int)func_L10_004239A0);
        count = &D_L10_001B1390_gp[mission];
        previous = *count;
        rank = previous < 3 ? previous : 2;
        D_L10_001B1440 = 1;
        D_L10_001B355C = mission;
        D_L10_001B13EC = 0;
        D_L10_001B13E8 = 0;
        reward = D_L10_001B1448_gp[mission][rank];
        if (D_001A7A0A != 0)
            reward *= 10;
        D_001A79F8_gp = D_001A79F8 + reward;
        *count = previous + 1;
        func_L10_00425888();
        func_0029B3E0(0, -1);
        func_L05_00379F48(1);
    }
    if (func_00282948(state + 0x40) == 0) {
      unsigned int pressed = D_00138324;
      if (pressed & 0x40) {
        D_L10_001B1440 = 0;
        *(int *)(state + 0x40) = 162000;
        func_0027D330(30);
        func_L05_00379F48(0);
        *(int *)(state + 0x48) = 10800;
        *(int *)(state + 0x58) = 120;
        if (D_L10_001B1390_gp[0] != 0) {
            int second = D_L10_001B1390[1];
            if (second != 0 && D_L10_001B1390[2] != 0)
                D_L10_001B143C = 3;
            else if (D_L10_001B1390_gp[0] != 0)
                {
                int completed = 1;
                if (second != 0)
                    completed = 2;
                D_L10_001B143C = completed;
            }
        }
        func_L10_00423500(actor);
      } else if (pressed & 0x10) {
        func_002B49E0(3, 1, 4, 0, 0);
      }
    } else {
        *(int *)(state + 0x40) = 162000;
    }
}
