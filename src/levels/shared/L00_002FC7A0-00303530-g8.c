extern void func_002B72E8();
extern int func_002B49C8();
extern void func_002B6E78();
extern void func_L00_00303418();
extern void func_L00_0032D208();
extern void func_L00_003032F0();
extern void func_002F0FA0();
extern void func_002F0468();
extern void func_L00_00300378();
extern void func_L00_00300090();
extern void func_0029D4D0();
extern void func_0011AEA0();
extern int func_002B7C80(char *, int, int);
extern void func_L00_002FD400();
extern void func_002FC3C0();
extern void func_002B7170();
extern void func_002E5FE0();
extern void func_L00_0035F8D0();
#include "include_asm.h"
#include "names.h"
extern int D_L00_001C9340[];
extern int D_L00_001B2600[];
extern int D_L00_001B2614 __attribute__((section(".sdata")));
extern int D_L00_001B24D4 __attribute__((section(".sdata")));
typedef struct {
    unsigned char pad00[0x529C];
    int base;
    unsigned char pad52A0[0x28];
    struct { int sector, size; } entries[0];
} ChunkDiscTable;
extern ChunkDiscTable D_0014B540;
extern int D_L00_001B2608 __attribute__((section(".sdata")));
extern unsigned char *D_L00_001B24D0 __attribute__((section(".sdata")));

/* Loads a scene chunk, initializes its geometry and batches tfrag lighting. */
void func_L00_00303530(int index, int argument)
{
    int *root = D_L00_001C9340;
    int *block, *first, *second;
    int i;
    if (root[0] == index)
        return;
    ConfigureScreenEffect(0, 0, 0, 0, 0);
    ClearAllSoundVoices();
    WaitForMusicIdle();
    WaitForDmaStatusBits(1);
    root[0] = index;
    block = (int *)D_L00_001B2600[0];
    D_L00_001B2608 = D_L00_001B2600[D_L00_001B2614];
    FlushTableEntryOffsets();
    ReadDiscWithPause((char *)block, gCopySetupData.entries[index].sector + gCopySetupData.base, gCopySetupData.entries[index].size);
    first = (int *)((char *)block + block[0]);
    second = (int *)((char *)block + block[1]);
    FlushCache(0);
    fast_decompress(first, root[2]);
    fast_decompress(second, root[1]);
    FlushCache(0);
    initialize_tfrag_render_data(root[2], root[4]);
    RelocateLevelHeaderBlocks(root[1]);
    {
        int count = D_L00_001B24D4;
        if (count > 0) {
            unsigned short *p = (unsigned short *)(D_L00_001B24D0 + 0x36);
            do {
                *p = 0xffff;
                p += 32;
            } while (--count);
        }
    }
    i = 0;
    while (i < D_L00_001B24D4) {
        unsigned short *p = (unsigned short *)0x70003000;
        int n = 0;
        while (n < 1023 && i < D_L00_001B24D4) {
            *p++ = i;
            n++;
            i++;
        }
        *p = 0xffff;
        func_002F0468((void *)0x70003000);
    }
    ResetRecordList();
    ResetTutorialRecordValues();
    ReloadSoundBank(index);
    UpdateObjectVisibilityForSelection(index);
    StartMusicStreamNoLoop(argument, 1, 1024);
    if (IsCurrentRequestSlot(2))
        music_Pause(0);
}
