#include "include_asm.h"

extern char D_00189E20_9[];

extern char D_001A63A8_3[];

extern short D_00152C2A;

extern void func_002B72E8_1();

extern void func_002E4AC8();

extern void func_00288EA0();

extern void func_002E6D88();

typedef unsigned char u8;

typedef int s32;

typedef struct {
 u8 prefix[0x30];s32 state;u8 gap0[0x1c];u8 *current;u8 gap1[0x138];s32 bank[2];
} NativeContext;

extern NativeContext D_L24_001BC3C0;

extern u8 D_L24_0028AAC0[];

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
void func_002E7018(void)
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
void func_002E7090(int level)
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
        func_002E6D88(3);
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


/* func_002E7248 is matched in its own unit, 002E7248-qcopy.c. */

INCLUDE_ASM("asm/game", func_002E7338);

/* func_002E7570 is in 002E7018-qcopy.c (grouped lq/sq copies). */

INCLUDE_ASM("asm/game", func_002E76C0);

extern unsigned int D_001A7AF0 __attribute__((sda));
extern void func_002E76C0(void *, int, int);

void func_002E7B48(void *object)
{
    int count = ((D_001A7AF0 >> 4) & 1) ? 3 : 1;
    int index;
    for (index = 0; index < count; index++)
        func_002E76C0(object, index, 0);
}


INCLUDE_ASM("asm/game", func_002E7BC8);


/* func_002E8190 is matched in 002E7018-g8.c (-G8 small data). */

extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027E018(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern char *D_001A7344 __attribute__((sda));
extern unsigned long long D_001B2168 __attribute__((sda));

void func_002E82C8(int alpha)
{
    unsigned long long color;
    unsigned long long packet;
    char *dst;

    func_002FC560(0x47, 0x31801ULL);
    func_002FC560(0x42, 0x8000000044ULL);
    color = (alpha << 24) | 0x00808080;
    packet = D_001B2168;
    dst = D_001A7344;
    func_0027E018(0x20, dst - 0x58, 0x100, 0x20, 0, 0, 0x100, 0x20, color, packet);
    func_002FC560(0x47, 0x5360BULL);
}


INCLUDE_ASM("asm/game", func_002E8368);

INCLUDE_ASM("asm/game", func_002E8BA8);



INCLUDE_ASM("asm/game", func_002E9268);

extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void func_0027C480(void);
extern void func_0027BD70(void);
extern void func_002E8BA8(void);

void func_002EA8E8(void)
{
    switch (D_00152C20) {
    case 0:
    case 3:
        func_0027C480();
        break;
    case 1:
        D_001B1594 = 127;
        func_0027BD70();
        break;
    case 2:
        func_002E8BA8();
        break;
    }
}

INCLUDE_ASM("asm/game", func_002EA968);

extern void func_001325E8(void *, void (*)(int, long), long long);
extern void func_0011AEA0(int);
extern int func_001261F0(int);
extern int func_00132028(void);
extern void func_002E6088(int, long);

void func_002EAAA8(void *arg, int *status) {
    *status = -1;
    func_001325E8(arg, func_002E6088, (unsigned long long)(unsigned int)status);
    {
        int sentinel = -1;
        do {
            func_0011AEA0(0);
            func_001261F0(0);
            func_00132028();
        } while (*status == sentinel);
    }
}

INCLUDE_ASM("asm/game", func_002EAB18);


/* D_001B8840 is declared above func_002E7090 (List2E7090). */
extern char D_0014B540[];
extern int func_002B7B18(int, int, int);
extern void func_002B7CE0(int);

int func_002EB158(int index)
{
    char *table = D_0014B540;
    int row = D_001B8840.selected * 0x14C;
    int destination = D_001B8840.destination;
    int base = (int)(table + 0x3EA8);
    int first = *(int *)((index << 2) + row + base);
    int count = *(int *)(((index + 1) << 2) + row + base) - first;
    if (count > 0) {
        func_002B7B18(destination, first + *(int *)(table + 0x3E24), count);
        func_002B7CE0(0);
    }
    return 1;
}

INCLUDE_ASM("asm/game", func_002EB1E0);


INCLUDE_ASM("asm/game", func_002EB7E8);

INCLUDE_ASM("asm/game", func_002EBAA8);


INCLUDE_ASM("asm/game", func_002EBC70);

INCLUDE_ASM("asm/game", func_002EBDF0);

/* func_002EC1C0 is matched in 002E7018-g8.c (-G8 small data). */

INCLUDE_ASM("asm/game", func_002EC408);

INCLUDE_ASM("asm/game", func_002ECB70);

/* selects the level data bank when the resident context is in state 9 */
void func_002ED058(void) {
 s32 index=-1;
 if(D_L24_001BC3C0.state==9) index=1;
 if(index!=-1) {
  D_L24_001BC3C0.current=D_L24_0028AAC0;
  *(s32 *)(D_L24_0028AAC0+0x68)=D_L24_001BC3C0.bank[index];
 }
}

