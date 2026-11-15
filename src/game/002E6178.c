#include "common.h"

typedef struct { char pad[8]; void *active; char gap[20]; float data[4]; } EquipState;

typedef struct {
    char pad00[0x30];
    unsigned char alpha;
    char pad31;
    unsigned short drawMask;
    unsigned short flags;
    char pad36[0x63 - 0x36];
    unsigned char mode;
    char pad64[4];
    EquipState *state;
} EquipPiece;

extern EquipPiece *func_0029EFD0(int);
extern void func_002E6120(void);
extern EquipPiece *D_00152C00;
extern unsigned int D_001A7AF0 MACRO_ADDR;
extern short D_001A8C28[] MACRO_ADDR, D_001A8C30[] MACRO_ADDR, D_001A8C38[] MACRO_ADDR, D_001A8C40[] MACRO_ADDR;
extern short D_001A8C48[] MACRO_ADDR, D_001A8C50[] MACRO_ADDR, D_001A8C58[] MACRO_ADDR;
extern EquipPiece *D_00214920[];

/* Spawns the hero's equipment pieces from the equipment bits and flags them. */
void func_002E6178(EquipPiece *base)
{
    EquipPiece **parts;
    EquipPiece **p;
    EquipPiece *piece;
    EquipState *state;
    unsigned int equipment;
    int chassis, partA, partB, partC, partD, partE, partF, count;

    if (!base)
        base = gHeroMoby_00152C00;
    DestroyEquipmentPieces();
    count = 5;
    base->alpha = 255;
    parts = gEquipmentPieces;
    equipment = gEquipmentBits;
    chassis = (equipment >> 2) & 3;
    partA = (equipment >> 4) & 1;
    partB = (equipment >> 6) & 1;
    partC = (equipment >> 7) & 3;
    partD = (equipment >> 9) & 1;
    partE = (equipment >> 10) & 3;
    partF = (equipment >> 14) & 3;
    parts[0] = CreateMoby(D_001A8C28[chassis]);
    parts[1] = CreateMoby(D_001A8C28[chassis]);
    parts[1]->flags |= 0x8000;
    parts[2] = CreateMoby(D_001A8C30[partA]);
    parts[3] = CreateMoby(D_001A8C38[partB]);
    parts[4] = CreateMoby(D_001A8C38[partB]);
    parts[4]->flags |= 0x8000;
    if (D_001A8C40[partC]) {
        parts[5] = CreateMoby(D_001A8C40[partC]);
        parts[6] = CreateMoby(D_001A8C40[partC]);
        count = 7;
        parts[6]->flags |= 0x8000;
    }
    parts[count++] = CreateMoby(D_001A8C48[partD]);
    piece = parts[count++] = CreateMoby(D_001A8C48[partD]);
    piece->flags |= 0x8000;
    parts[count++] = CreateMoby(D_001A8C50[partE]);
    piece = parts[count++] = CreateMoby(D_001A8C50[partE]);
    piece->flags |= 0x8000;
    if ((gEquipmentBits >> 12) & 1)
        parts[count++] = CreateMoby(0x10E2 /* moby class 4322 */);
    if ((gEquipmentBits >> 13) & 1)
        parts[count++] = CreateMoby(0x10E4 /* moby class 4324 */);
    if (partF)
        parts[count] = CreateMoby(D_001A8C58[partF]);
    if (*parts) {
        p = parts;
        do {
            if ((*p)->mode)
                (*p)->mode = 8;
            (*p)->flags |= 0x124;
            (*p)->drawMask = 0x1FF;
            (*p)->state->active = (*p)->state->data;
        } while (*++p);
    }
    base->flags |= 0x20;
    state = base->state;
    state->active = state->data;
}
