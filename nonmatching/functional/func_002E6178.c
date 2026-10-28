/* functional: medium. One captured call. Spawns the hero equipment pieces from the equipment bits (same calls and writes in the same order); near-miss draft of the retail code, differing only in scheduling and register allocation. */
#include "common.h"

typedef struct {
    char pad00[0x30];
    unsigned char alpha;
    char pad31;
    unsigned short drawMask;
    unsigned short flags;
    char pad36[0x63 - 0x36];
    unsigned char mode;
    char pad64[4];
    char *state;
} EquipPiece;

extern EquipPiece *func_0029EFD0(int);
extern void func_002E6120(void);
extern EquipPiece *D_00152C00;
extern unsigned int D_001A7AF0 MACRO_ADDR;
extern short D_001A8C28[], D_001A8C30[], D_001A8C38[], D_001A8C40[];
extern short D_001A8C48[], D_001A8C50[], D_001A8C58[];
extern EquipPiece *D_00214920[];

/* Spawns the hero's equipment pieces from the equipment bits and flags them. */
void func_002E6178(EquipPiece *base)
{
    EquipPiece **parts;
    EquipPiece **p;
    EquipPiece *piece;
    char *state;
    unsigned int equipment;
    int chassis, partA, partB, partC, partD, partE, partF, count;

    if (!base)
        base = D_00152C00;
    func_002E6120();
    count = 5;
    base->alpha = 255;
    parts = D_00214920;
    equipment = D_001A7AF0;
    chassis = (equipment >> 2) & 3;
    partA = (equipment >> 4) & 1;
    partB = (equipment >> 6) & 1;
    partC = (equipment >> 7) & 3;
    partD = (equipment >> 9) & 1;
    partE = (equipment >> 10) & 3;
    partF = (equipment >> 14) & 3;
    parts[0] = func_0029EFD0(D_001A8C28[chassis]);
    parts[1] = func_0029EFD0(D_001A8C28[chassis]);
    parts[1]->flags |= 0x8000;
    parts[2] = func_0029EFD0(D_001A8C30[partA]);
    parts[3] = func_0029EFD0(D_001A8C38[partB]);
    parts[4] = func_0029EFD0(D_001A8C38[partB]);
    parts[4]->flags |= 0x8000;
    if (D_001A8C40[partC]) {
        parts[5] = func_0029EFD0(D_001A8C40[partC]);
        parts[6] = func_0029EFD0(D_001A8C40[partC]);
        count = 7;
        parts[6]->flags |= 0x8000;
    }
    parts[count++] = func_0029EFD0(D_001A8C48[partD]);
    piece = parts[count++] = func_0029EFD0(D_001A8C48[partD]);
    piece->flags |= 0x8000;
    parts[count++] = func_0029EFD0(D_001A8C50[partE]);
    piece = parts[count++] = func_0029EFD0(D_001A8C50[partE]);
    piece->flags |= 0x8000;
    if ((D_001A7AF0 >> 12) & 1)
        parts[count++] = func_0029EFD0(0x10E2);
    if ((D_001A7AF0 >> 13) & 1)
        parts[count++] = func_0029EFD0(0x10E4);
    if (partF)
        parts[count] = func_0029EFD0(D_001A8C58[partF]);
    for (p = parts; *p; p++) {
        if ((*p)->mode)
            (*p)->mode = 8;
        (*p)->flags |= 0x124;
        (*p)->drawMask = 0x1FF;
        state = (*p)->state;
        *(char **)(state + 8) = state + 0x20;
    }
    base->flags |= 0x20;
    state = base->state;
    *(char **)(state + 8) = state + 0x20;
}
