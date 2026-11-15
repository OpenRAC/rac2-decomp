#include "include_asm.h"
#include "names.h"

typedef struct {
    int unk00;
    int unk04;
    unsigned char pad08[0x18];
    int unk20;
    int unk24;
    unsigned char pad28[0x3C];
    int key;
    unsigned char pad68[4];
    int unk6C;
    unsigned char pad70[0xC];
    int unk7C;
    unsigned char pad80[0x10];
} HudSlot;

extern HudSlot D_00255330[13];
extern int D_001B1870;
extern int D_001B1874;
extern char *D_001B18D8;
extern char *D_001B18E0_1;
extern int D_001B18E4;
extern char ref_L00_0028AB70_00[];
extern char *D_001B18DC_1 __attribute__((sda));
extern char *func_0028B2B8(int, int, char *, int);
extern void func_0028B3D0(int, int, int, int, int, int, int);
extern char *func_00282A88(char *, int);
extern void func_0028BCE8(void);
extern void func_0028A278(void);

/* Clears the thirteen HUD slots and lazily allocates their drawing buffers. */
void func_0028AB70(void)
{
    int *cursor = (int *)gHudElements;
    int *slotWords;
    int i = 0;

    gHudState = 0;
    D_001B1874 = 0;
    do {
        slotWords = cursor + 9;
        slotWords[16] = -1;
        slotWords[-1] = 0x10000;
        SetHudSlotContents(i, 0xffff, 0, 0, 0, 0, 1);
        i++;
        slotWords[22] = 0;
        slotWords[18] = -6;
        slotWords[-8] = 0;
        slotWords[0] = 0;
        cursor = slotWords + 27;
    } while (i < 13);
    if (D_001B18D8 == 0) {
        char *sourceFile = ref_L00_0028AB70_00;
        D_001B18D8 = AllocHudMemory(0x2800, 0, sourceFile, 0x2AB);
        D_001B18E4 = (int)AllocHudMemory(0x1400, 0, sourceFile, 0x2AC);
    }
    D_001B18E0_1 = D_001B18D8 + 0x2800;
    D_001B18DC_1 = D_001B18D8;
    FastMemoryHelperB(D_001B18D8, 0x2800);
    *((unsigned char *)D_001B18D8 + 0x20) = 0xFF;
    InitWeaponMenuSlots();
    ResetBoltCounterDisplay();
}
