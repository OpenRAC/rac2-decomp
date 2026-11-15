#include "common.h"

/* snd_StreamSafeCdRead (rac1-decomp src/core/989snd.c). This unit needs
   -mno-split-addresses for the absolute `lui $at; sw` stores and for the return-zero
   constant in the beq's delay slot.

   D_001A7100 and D_001A7110 are the count and error fields of RAC1's CdSafeState
   (sound_read_work), which declares them volatile with these types at offsets 0 and
   0x10; snd_CheckLoadInProgress polls the count. Two volatile stores depend on each other, which
   raises the first store's scheduling priority above the two address loads, so it goes
   first; the second then ranks behind the remaining load, having fewer dependents.
   Without volatile all four tie on priority and the loads, with more dependents, go
   first. */
extern int D_001A748C __attribute__((sda));
extern int D_001A7494 __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern volatile unsigned int D_001A7100 NOT_SDA;
extern volatile int D_001A7110 NOT_SDA;
extern char D_001A713F NOT_SDA;

extern void func_0011B3D0(void *, void *);
extern int func_001253A8(int, int, void *, unsigned char *);
extern int func_00133580(int);
extern void func_00132DF0(int, int, void *, int, long);

int func_001334B8(int lba, int sectors, void *buf, unsigned char *mode) {
    int payload[4];

    if (D_001A748C == 0) {
        return func_001253A8(lba, sectors, buf, mode);
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        return 0;
    }
    D_001A7100 = 1;
    D_001A7110 = 0;
    func_0011B3D0((void *)&D_001A7100, &D_001A713F);
    payload[0] = lba;
    payload[1] = sectors;
    payload[2] = (int)buf;
    D_001A7494 = 1;
    D_001A7498 = 0;
    func_00132DF0(0x38, 0xC, payload, 0, 0);
    return 1;
}
