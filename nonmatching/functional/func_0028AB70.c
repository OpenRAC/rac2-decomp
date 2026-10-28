/* functional: high. Same clear loop, lazy allocations and calls in retail order; retail keeps -1 in a saved register, which does not change behaviour. */
#include "include_asm.h"
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
extern char *D_001B18E0;
extern int D_001B18E4;
extern char D_001A8E08[];
extern char *D_001B18DC __attribute__((sda));
extern char *func_0028B2B8(int, int, char *, int);
extern void func_0028B3D0(int, int, int, int, int, int, int);
extern char *func_00282A88(char *, int);
extern void func_0028BCE8(void);
extern void func_0028A278(void);

/* Clears the thirteen HUD element slots and lazily creates the HUD moby table. */
void func_0028AB70(void)
{
    int *q = (int *)((char *)D_00255330 + 0x24);
    int i = 0;

    D_001B1870 = 0;
    D_001B1874 = 0;
    q[16] = -1;
    do {
        q[-1] = 0x10000;
        func_0028B3D0(i, 0xffff, 0, 0, 0, 0, 1);
        i++;
        q[22] = 0;
        q[18] = -6;
        q[-8] = 0;
        q[0] = 0;
        q = (int *)((char *)q + 0x90);
    } while (i < 13);
    if (D_001B18D8 == 0) {
        char *file = D_001A8E08;
        D_001B18D8 = func_0028B2B8(0x2800, 0, file, 0x2AB);
        D_001B18E4 = (int)func_0028B2B8(0x1400, 0, file, 0x2AC);
    }
    D_001B18E0 = D_001B18D8 + 0x2800;
    D_001B18DC = D_001B18D8;
    func_00282A88(D_001B18D8, 0x2800);
    *((unsigned char *)D_001B18D8 + 0x20) = 0xFF;
    func_0028BCE8();
    func_0028A278();
}
