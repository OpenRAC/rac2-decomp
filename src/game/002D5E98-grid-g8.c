#include "include_asm.h"
#include "common.h"
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(int);
extern void func_0027C660(void);

extern int D_001ABAD8 __attribute__((sda)), D_001ABADC __attribute__((sda)), D_001ABAE8 __attribute__((sda));
extern int D_001AA43C __attribute__((sda));
extern int D_001B1598;
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_001395B8[];
extern unsigned int func_002884B0(unsigned int);
extern int func_00282C30(int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern void func_0028EE98(int, int, int, int, int, int);

typedef struct { char pad[0x14]; char *owner; char pad18[0x40-0x18]; int slots[65]; int override144; int override148; } GridContext;
extern GridContext D_001F2840;
extern unsigned char D_00139568[];
typedef struct { unsigned char pad[4]; unsigned char purchased; unsigned char pad05[7]; int slot; unsigned char pad10[0x3C-0x10]; unsigned short icon; unsigned char pad3E[224-0x3E]; } GridItem;
extern GridItem D_00239BA0[];
extern void func_002D8EC0(char *, short *, int, int, int, int);
extern int func_0028E588(int, int);

int func_002D9008(char *object)
{
    int probe[4];
    short *record = *(short **)(object + 0x48);
    int active = *(char **)(D_001F2840.owner + 0xE8) == object;
    int xStart, xStep, yStart, yStep;
    int width, height, areaWidth, areaHeight, gap;
    int index, column, x, state, bottom, right;
    int texture;
    unsigned long colour, pulse;
    GridItem *entry;
    func_002FC560(66, 0x8000000044ULL);
    func_002FC560(71, 11);
    func_0027C540(0);
    width = D_001ABAD8;
    height = D_001ABADC;
    areaWidth = *(int *)(object + 0x20) << 4;
    areaHeight = *(int *)(object + 0x24) << 4;
    gap = D_001ABAE8;
    if (*(int *)(object + 0x44) >= 2) {
        xStart = *(int *)(object + 0x34) << 4;
        xStep = width + (areaWidth -
                (*(int *)(object + 0x34) << 5) - *(int *)(object + 0x44) * width) /
                (*(int *)(object + 0x44) - 1);
    } else {
        xStart = (areaWidth - width) >> 1;
        xStep = 0;
    }
    if (*(int *)(object + 0x30) & 2) {
        yStep = height + gap;
        yStart = *(int *)(object + 0x38) << 4;
    } else if (*(int *)(object + 0x40) >= 2) {
        yStart = *(int *)(object + 0x38) << 4;
        yStep = height + (areaHeight -
                (*(int *)(object + 0x38) << 5) - *(int *)(object + 0x40) * height) /
                (*(int *)(object + 0x40) - 1);
    } else {
        yStep = 0;
        yStart = (areaHeight - height) >> 1;
    }
    index = 0;
    {
    int row, y;
    y = yStart;
    for (row = 0; row < *(int *)(object + 0x40); row++) {
        x = xStart;
        for (column = 0; column < *(int *)(object + 0x44); column++) {
            bottom = y + height;
            right = x + width;
            state = 0;
            if (record[2] == 0 ? *(D_001A7AF8 + record[3]) : *(D_001395B8 + record[3])) {
                if ((unsigned short)record[2] == 0) {
                    entry = &D_00239BA0[D_00139568[record[3]]];
                    state = 0;
                    if (D_001F2840.slots[entry->slot] == record[3])
                        state = ((*(int *)(object + 0x30) ^ 1) & 1) << 2;
                    if (state == 0) {
                        int owned = 3;
                        if (!entry->purchased) owned = 0;
                        state = owned;
                    }
                    if (D_001F2840.override144 && (*(int *)(object + 0x30) & 8)) state = 2;
                    if (D_001F2840.override148 && (*(int *)(object + 0x30) & 4)) state = 2;
                    if (func_002884B0((unsigned short)record[0]))
                        func_002D8EC0(object, record, column, row, x >> 4, (y >> 4) + 36);
                }
                if (active && *(int *)(object + 0x3C) == index) {
                    pulse = (unsigned int)(((func_00282C30((D_001B1598 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                    colour = state == 4 ? (unsigned long)(int)0x80101010u : (unsigned long)D_001AA43C;
                    func_0028FC48(x - 48, y - 48, right + 48, bottom + 48, pulse, 1);
                    func_0028FC48(x - 16, y - 16, right + 16, bottom + 16, colour, 1);
                }
                if (state == 4)
                    func_0028FC48(x - 64, y - 64, right + 64, bottom + 64, 0x80FFFFFFUL, 1);
                texture = func_0028E588(D_00239BA0[D_00139568[record[3]]].icon, record[1]);
                func_0028EE98(texture, x, y, width, height, 128);
                if (state == 2)
                    func_0028FC48(x - 64, y - 64, right + 64, bottom + 64, 0x60202020UL, 1);
            } else if (active && *(int *)(object + 0x3C) == index) {
                pulse = (unsigned int)(((func_00282C30((D_001B1598 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                colour = (unsigned long)D_001AA43C;
                func_0028FC48(x - 48, y - 48, right + 48, bottom + 48, pulse, 1);
                func_0028FC48(x - 16, y - 16, right + 16, bottom + 16, colour, 1);
            }
            index++;
            record += 5;
            x += xStep;
        }
        y += yStep;
    }
    }
    func_0027C660();
    return 2;
}
