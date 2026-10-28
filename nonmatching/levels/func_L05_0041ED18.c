/* func_L05_0041ED18 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_0041ED18-g8.c: 456/488 bytes.
 * US: 0/3 local places; PAL: ABSENT; US2: ABSENT.
 * No strict linked build was run because no local placement matched.
 * Input base lifetime, switch/control block ordering and frame allocation differ. The successful confirmation exits before the failed-confirmation flag and button check. Reopen with measured input layout and block-order evidence.
 */

#include "common.h"

extern int D_L05_001B904C MACRO_ADDR;
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_001B1354 MACRO_ADDR;
extern int D_L05_001B1358 MACRO_ADDR;
extern int D_L05_001B13E8 __attribute__((sda));
extern char D_00138180[];
extern void ref_L05_0041ED18_00(void *);
extern void func_0029B758(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_002B49E0(int, int, int, int, unsigned char *);

int func_L05_0041ED18(void)
{
    unsigned int buttons;
    int accepted;
    if (D_L05_001B904C && !D_L05_001B13AC) {
        func_0029B758(0, (int)ref_L05_0041ED18_00);
        D_L05_001B13A8 = 0;
        D_L05_001B13AC = 1;
    }
    buttons = *(unsigned int *)(D_00138180 + 0x1A4);
    if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--D_L05_001B13EC < 0) D_L05_001B13EC = 3;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++D_L05_001B13EC > 3) D_L05_001B13EC = 0;
    }
    if (*(unsigned int *)(D_00138180 + 0x1A4) & 0x10)
        func_002B49E0(3, 1, 4, 0, 0);
    if (*(unsigned int *)(D_00138180 + 0x1A4) & 0x40) {
        accepted = 0;
        switch (D_L05_001B13EC) {
        case 0:
            accepted = 1;
            break;
        case 1:
            if (D_L05_001B1350) accepted = 1;
            break;
        case 2:
            if (D_L05_001B1350 && D_L05_001B1354) accepted = 1;
            break;
        case 3:
            if (D_L05_001B1350 && D_L05_001B1354 && D_L05_001B1358) accepted = 1;
            break;
        }
        if (accepted) {
            D_L05_001B13E8 = 0;
            func_002E5E58(4, 0, 0);
            return -2;
        } else {
            func_002E5E58(5, 0, 0);
            D_L05_001B13E8 = 1;
        }
    }
    if (*(unsigned long long *)(D_00138180 + 0x1A0) & 0xA000000000ULL)
        func_002E5E58(5, 0, 0);
    return -2;
}