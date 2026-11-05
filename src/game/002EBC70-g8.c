#include "common.h"

/* One frame of the level transition loop: it re-links the queued entries to
   their predecessor, runs the frame's call sequence, and repeats while the
   shared mode word says "running".  The three small-data words it counts live
   in the program's own small-data area, so the unit is built with -G8. */
typedef struct {
    char pad0[0x28]; void *previous;
} SceneEntry;
typedef struct {
    char pad0[0x44]; short count; char pad46[0x146]; SceneEntry *entries[17];
    char pad1D0[0x1A0]; int mode; char pad374[4]; int next_mode;
} SceneFrame;
extern SceneEntry *D_001B1B5C MACRO_ADDR;
extern SceneFrame D_001B8840;
extern int D_001A8BB0;
extern int D_001A8BB8;
extern int D_001B169C __attribute__((sda));
extern int D_001B1594 __attribute__((sda));
extern int D_001B1598;
extern int D_001B1598_GP SDATA(D_001B1598);
extern int D_001A8BB0_GP SDATA(D_001A8BB0);

extern void func_002EB7E8(void);
extern void func_002FC280(void);
extern void func_002FC220(void);
extern void func_00284FC0(void);
extern void func_00285338(void);
extern void func_00284EA8(void);
extern void func_00298F00(void);
extern void func_00279D18(void);
extern void func_0029FB20(void);
extern void func_0027B858(void);
extern void func_002B9000(void);
extern int func_002EB1E0(void);
extern void func_00284F40(int);
extern void func_0027BD70(void);
extern void func_002FC3C0(int);
extern int func_001261F0(int);
extern void func_002EBAA8(void);

int func_002EBC70(int unused)
{
    SceneEntry *prev;
    SceneEntry *entry;
    int i;
    int value;

    func_002EB7E8();
    prev = D_001B1B5C;
    i = 0;
    if (i < D_001B8840.count) {
        do {
            do {
                entry = D_001B8840.entries[i];
                if (entry != 0 && prev != entry) {
                    entry->previous = prev;
                    prev = entry;
                }
            } while (0);
            i++;
        } while (i < D_001B8840.count);
    }
    D_001A8BB0 = 2;
    do {
        func_002FC280();
        func_002FC220();
        func_00284FC0();
        func_00285338();
        func_00284EA8();
        func_00298F00();
        func_00279D18();
        func_0029FB20();
        func_0027B858();
        D_001B169C = -1;
        func_002B9000();
        value = func_002EB1E0();
        func_00284F40(0);
        D_001B1594 = 0x131;
        func_0027BD70();
        if (D_001A8BB8 != -2) {
            D_001A8BB0 = D_001A8BB8;
            D_001A8BB8 = -2;
        }
        func_002FC3C0(1);
        func_001261F0(0);
        D_001B1598_GP = D_001B1598 + 1;
    } while (D_001A8BB0 == 2);
    D_001A8BB0_GP = 0;
    func_002EBAA8();
    return value;
}

