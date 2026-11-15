#include "names.h"
/* Map cache reset: calls the boot-only stub func_00298170, which is defined
 * in 00294BC8.c, so this level-placed body lives in a unit of its own. */
extern unsigned char D_001A7AFD __attribute__((section(".sdata")));
extern int D_001A79F0_3 __attribute__((sda));
extern int D_001C4FA0[];

extern void func_00298170(void);
extern int D_001F2840[];
extern void func_0029DEA8(int, int);
extern int func_002B7C80(void *, int, int);
extern short func_002B7CE0(int);
extern int func_002EEE50(int, int, int, int);
extern int func_002EEED0(int, int, int, int, int);
extern int func_002E5E58(int, unsigned int, void *);

/* resets the map's cache slots and reloads the current level's entry */
typedef struct { int sector, size; } MapFile;
typedef struct {
    char pad0[0x36C];
    int base;           /* 0x36C */
    char pad370[0x14F0 - 0x370];
    MapFile files0[28]; /* 0x14F0 */
    MapFile files1[28]; /* 0x15D0 */
} MapToc;
extern MapToc D_0014B540;

void func_002954C0(void)
{
    int *arena;
    int bufA, bufB, packedBuf;
    int bytes;
    int *mapState;

    EmptyMapStub();
    func_0029DEA8(gMapOverlayState[0x230 / 4], 1);
    arena = gPauseMenuState;
    bufA = arena[0x10C / 4];
    bufB = arena[0x110 / 4];
    gMapOverlayState[0x248 / 4] = bufA;
    packedBuf = bufA + 0x9A800;
    gMapOverlayState[0x288 / 4] = 0;
    gMapOverlayState[0x28C / 4] = packedBuf;
    arena[0x10C / 4] = packedBuf + 0x48000;
    gMapOverlayState[0x290 / 4] = bufB;
    arena[0x110 / 4] = bufB + 0x48000;
    gMapOverlayState[0x294 / 4] = 0;
    gMapOverlayState[0x298 / 4] = 0;
    gMapOverlayState[0x29C / 4] = -1;
    gMapOverlayState[0x2A0 / 4] = -1;
    gMapOverlayState[0x2A4 / 4] = -1;
    gMapOverlayState[0x2A8 / 4] = -1;
    gMapOverlayState[0x2AC / 4] = -1;
    gMapOverlayState[0x2B0 / 4] = -1;
    if (gMapOverlayState[0x238 / 4] == -1) goto empty;
    if (gMapOverlayState[0x23C / 4] == 0 && D_001A7AFD != 0) {
        MapToc *toc = &gCopySetupData;
        int size = toc->files1[gMapOverlayState[0x230 / 4]].size;
        bytes = size << 7;
        ReadDiscWithPause((void *)packedBuf, toc->files1[gMapOverlayState[0x230 / 4]].sector + toc->base, size);
        PumpMusicAndDiscRead(1);
        gMapOverlayState[0x23C / 4] = 1;
        gMapOverlayState[0x240 / 4] = bytes;
        SendBufferSlotRecords(gMapOverlayState[0x28C / 4], gMapOverlayState[0x238 / 4], 0, bytes);
        gMapOverlayState[0x234 / 4] = -2;
        gMapOverlayState[0x24 / 4] = 1;
        gMapOverlayState[0x2A0 / 4] = D_001A79F0_3 + 0x100;
    } else {
        int size;
        mapState = gMapOverlayState;
        if (mapState[0x238 / 4] == -1) goto empty;
        size = mapState[0x240 / 4];
        mapState[0x2B8 / 4] = size;
        UploadRecordsToBufferSlot(mapState[0x28C / 4], mapState[0x238 / 4], 0, size, 0);
        mapState[0x24 / 4] = 1;
        mapState[0x2A0 / 4] = D_001A79F0_3 + (D_001A7AFD ? 0x100 : 0);
        mapState[0x234 / 4] = -2;
    }
    goto done;
empty:
    gMapOverlayState[0x24 / 4] = 0;
done:
    PlaySoundFromGlobalBank(0x11, 0, 0);
}
