#include "include_asm.h"


extern char D_00189E20_9[];
extern char D_001A63A8_3[];
extern short D_00152C2A;
extern void func_002B72E8_1();
extern void func_002E4AC8();
extern void func_00288EA0();
extern void func_002E6D88();

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
void func_US2_002E7E70(void)
{
    char *p = D_00189E20_9;
    char *q;
    unsigned short v;

    if (*(int *)(p + 9420) <= 0) {
        *(int *)(p + 9420) = 1;
    }
    func_002B72E8_1(0);

    q = D_001A63A8_3;
    v = *(unsigned short *)(q + 114);
    if ((unsigned short)(v - 6) >= 2) {
        *(unsigned short *)(q + 114) = 5;
    }
    func_002E4AC8();
    func_00288EA0();
    func_002E6D88(0);
    D_00152C2A = 0;
}

#include "common.h"
extern void func_US2_002E7BE0();
#define MACRO_ADDR __attribute__((section(".sdata")))
typedef struct { char pad[0x20]; short active; short slot; } Menu2E7090;
typedef struct { char pad[0xC]; int start; int end; } Range2E7090;
typedef struct { char pad[0x30]; int selected; int base; int page; int row; char pad40[0x6C - 0x40]; int start; int destination; } List2E7090;
extern float D_001B15A0 MACRO_ADDR;
extern int D_001B15A4 MACRO_ADDR;
extern Menu2E7090 D_00152C00;
extern int D_001B22B0 MACRO_ADDR;
extern Range2E7090 D_001BAEC0;
extern List2E7090 D_001B8840;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001B1680 MACRO_ADDR;
extern void func_002FC138(void);
extern void func_00294070(int);
extern int func_0029B3E0(int, int);

/* Opens the list: rebases its range on the loaded block and, for the current program, lays
   out the first page (80 or 96 rows a page). */
void func_US2_002E7EE8(int level)
{
    Menu2E7090 *menu = &D_00152C00;
    short none = -1;
    int base;

    D_001B15A0 = 1.0f;
    D_001B15A4 = 0;
    menu->active = 0;
    menu->slot = none;
    func_002FC138();
    base = D_001B22B0 - 0x60000;
    D_001B8840.start = D_001BAEC0.start + base;
    D_001B8840.destination = D_001BAEC0.end + base;
    D_001B22B0 = base;
    if (D_001A79F0 == level) {
        func_US2_002E7BE0(3);
        level = D_001A7B90 ? 0x50 : 0x60;
        D_001B8840.base = 0;
        D_001B8840.row = D_001B8840.base / level;
        func_00294070(D_001B8840.row);
        D_001B8840.page = D_001B8840.base % level;
    } else {
        func_0029B3E0(0, level);
        D_001B1680 = level;
        menu->active = 1;
        menu->slot = none;
    }
}



