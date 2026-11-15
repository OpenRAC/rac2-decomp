#include "include_asm.h"

extern int D_001A8BB0;
extern int D_001B1870 __attribute__((section(".sdata")));
extern char D_00255330[];
extern void func_0028B4D8(char *);

/* The subtitle counters are small data reached through $gp in retail, so this unit is -G8. */
extern int D_L00_001A9070[2] __attribute__((sda));

typedef struct {
    int active;
    int timer;
    int unk08;
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int entryIndex;
    int unk24;
    int pad28[8];
    int unk48;
} SubtitleState;

typedef struct { int unk00; int unk04; int id; int unk0C; } TextEntry;

extern SubtitleState D_00254E78;
extern TextEntry *D_001B1840;
extern unsigned short D_001A7B94;
extern int D_001A7344;
extern int D_001A7B90;
extern void func_2E5E58(int, int, int);
extern void func_2802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_280200(unsigned short *, long long, int, int);
extern int func_1157AC(int);

/* Seeds the subtitle renderer's state from the current text entry and its font metrics. */
void func_00289020(void)
{
    unsigned short metrics[12];
    int id;
    int h;

    D_00254E78.active = 1;
    D_00254E78.timer = 0;
    if (D_001A7B94 != 0)
        func_2E5E58(0, 1, 0);
    id = D_001B1840[D_00254E78.entryIndex].unk00;
    func_2802E0(metrics, 0xF0, 0x1E0, 0x2C, 0x1D4, 0x100, 0x168, 0x10, 7);
    func_280200(metrics, 0x80FFA888LL, id, -1);
    D_00254E78.unk08 = ((short)metrics[6] >> 1) + 10;
    D_00254E78.unk0C = ((short)metrics[7] >> 1) + 5;
    D_00254E78.unk10 = 0x100;
    D_00254E78.unk14 = D_L00_001A9070[D_001A7B90];
    D_00254E78.unk18 = 8;
    D_00254E78.unk1C = 8;
    D_00254E78.unk48 = 0;
    if (id != 0)
        D_00254E78.unk48 = func_1157AC(id) * 7;
    h = D_001A7344;
    D_00254E78.unk14 = h - 0x3C;
    if (h - 0xC < D_00254E78.unk14 + D_00254E78.unk0C) {
        int bottom = D_00254E78.unk0C + 0xC;
        D_00254E78.unk14 = h - bottom;
    }
}

extern char *ref_L00_0028B338_00 __attribute__((sda));
extern int D_001A8D44 __attribute__((sda));
extern char *D_001B1B5C;
extern char *D_001B1B60;
extern int D_001B1B64;
extern int D_001B1B6C;
extern char *D_001B18D8;
extern char *D_001B18DC;
extern int D_001B18E0;
extern int D_001B18E4;

/* Switches between the two moby contexts when the requested one is not the current one, swapping the stored pointers and counts. */
void func_0028B338(int requested)
{
    int state = D_001A8D44;
    if (requested != state) {
        char *first;
        char *second;
        int third, fourth, active_fourth;
        char *active_first = ref_L00_0028B338_00;
        requested = state ^ 1;
        first = *(char *volatile *)&D_001B18D8;
        *(char *volatile *)&D_001B18D8 = active_first;
        active_first = *(char *volatile *)&D_001B1B60;
        second = *(char *volatile *)&D_001B18DC;
        *(char *volatile *)&D_001B18DC = active_first;
        active_first = (char *)*(volatile int *)&D_001B1B64;
        third = *(volatile int *)&D_001B18E0;
        active_fourth = *(volatile int *)&D_001B1B6C;
        fourth = *(volatile int *)&D_001B18E4;
        *(volatile int *)&D_001A8D44 = requested;
        *(char *volatile *)&D_001B1B5C = first;
        *(char *volatile *)&D_001B1B60 = second;
        *(volatile int *)&D_001B1B64 = third;
        *(volatile int *)&D_001B18E0 = (int)active_first;
        *(volatile int *)&D_001B1B6C = fourth;
        *(volatile int *)&D_001B18E4 = active_fourth;
    }
}

/* Sets up or refreshes one of 16 slot records (0x90 bytes each) with an id, callback and four values; returns 0 if it is refused. */
int func_0028B3D0(int slot, int id, int callback, int value1, int value2, int value3, int value4)
{
    int index = slot & 15;
    char *p = D_00255330 + index * 0x90;
    int flags = slot & 0xfff0;
    int refresh;
    int serial;
    if (D_001A8BB0 == 5 && index != 2 && index != 0) return 0;
    if (*(int *)(p + 0x2c) == value3 && *(int *)(p + 0x28) == value4 &&
        *(int *)(p + 0x20) == id && *(int *)(p + 0x24) == flags &&
        *(int *)(p + 0x30) == callback && *(int *)(p + 0x34) == value1 &&
        *(int *)(p + 0x38) == value2) return *(int *)(p + 0x64);
    serial = D_001B1870;
    *(int *)(p + 0x2c) = value3;
    refresh = flags & *(int *)(p + 4);
    *(int *)(p + 0x64) = serial;
    refresh &= 0x20;
    serial++;
    *(int *)(p + 0x28) = value4;
    *(int *)(p + 0x20) = id;
    *(int *)(p + 0x30) = callback;
    *(int *)(p + 0x34) = value1;
    *(int *)(p + 0x38) = value2;
    D_001B1870 = serial;
    *(int *)(p + 0x68) = 1;
    *(int *)(p + 0x24) = flags;
    *(int *)(p + 0x7c) = 0;
    *(int *)(p + 0x70) = 0;
    if (refresh) func_0028B4D8(p);
    return *(int *)(p + 0x64);
}
