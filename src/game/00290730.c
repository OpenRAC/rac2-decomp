#include "include_asm.h"
#include "names.h"

extern int ref_L00_002FC030_00 __attribute__((sda));

extern int ref_L00_002FC048_00 __attribute__((sda));

/* Starts a request if none is running yet. */
void func_00290730(void)
{
    if (ref_L00_002FC030_00 == 0)
        ref_L00_002FC030_00 = 1;
}

/* Tells whether the request has reached its finished state. */
int func_00290748(void)
{
    return ref_L00_002FC048_00 == 3;
}

extern void func_002B6938(void), func_002FC138(void), func_00290B48(void);
extern void func_0027A9F0(void), func_0027AB40(void), func_00280630(void);
extern void func_002FC1D8(void), func_002BA0E0(void), func_002FCD18(void), func_00290978(void);
extern void func_00282A60(void *, int, int);
extern void func_002AD7B8(int);
extern int D_001A72E4;
extern int D_001A72D0[] __attribute__((sda));
extern int D_001A72D4, D_001A79F0, D_001A9A50;
extern char D_001B1740[], D_001CE4E0[], D_001D1580[], D_001D0E00[];
extern char D_00216480[], D_0021D880[], D_0021D480[], D_00212720[], D_00214520[], D_00213F20[];

/* Gets the game systems ready at the start of a level: memory, tables, graphics and the starting items. */
void func_00290758(void)
{
    int base;
    RegisterDiscReadCallback();
    SelectPacketBufferSetup();
    InitMemSlots();
    base = D_001A72E4;
    D_001A72D0[0] = base;
    D_001A72D4 = base;
    ClearMemory(D_001B1740, 0x87654321u, 16);
    ClearMemory(D_001CE4E0, -1, 0x2000);
    ClearMemory(D_001D1580, -1, 0xF00);
    ClearMemory(D_001D0E00, 0, 0xF0);
    ClearMemory(D_00216480, -1, 0x2000);
    ClearMemory(D_0021D880, -1, 0x800);
    ClearMemory(D_0021D480, 0, 0x80);
    ClearMemory(D_00212720, -1, 0x1000);
    ClearMemory(D_00214520, -1, 0x400);
    ClearMemory(D_00213F20, 0, 0x40);
    InitViewContext();
    UpdateViewContext();
    ClearFontQueueBuffer();
    ResetPacketBuffer();
    InitParticleUpdateTable();
    InstallDmaHandlers();
    GrantStartingItems();
    if (gCurrentMapIndex != 0)
        MarkFlagAndAppendToList(gCurrentMapIndex % 28);
    D_001A9A50 = 0;
}
