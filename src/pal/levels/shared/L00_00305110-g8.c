#include "include_asm.h"

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
extern void func_PAL_0029DE68();
extern void func_0011AEA0();
extern int func_PAL_002B8838(char *, int, int);
extern void func_L00_002FD400();
extern void func_002FC3C0();
extern void func_002B7170();
extern void func_002E5FE0();
extern void func_L00_0035F8D0();
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
void func_PAL_L00_00305110(int index, int argument)
{
    int *root = D_L00_001C9340;
    int *block, *first, *second;
    int i;
    if (root[0] == index)
        return;
    func_L00_0035F8D0(0, 0, 0, 0, 0);
    func_002E5FE0();
    func_002B7170();
    func_002FC3C0(1);
    root[0] = index;
    block = (int *)D_L00_001B2600[0];
    D_L00_001B2608 = D_L00_001B2600[D_L00_001B2614];
    func_L00_002FD400();
    func_PAL_002B8838((char *)block, D_0014B540.entries[index].sector + D_0014B540.base, D_0014B540.entries[index].size);
    first = (int *)((char *)block + block[0]);
    second = (int *)((char *)block + block[1]);
    func_0011AEA0(0);
    func_PAL_0029DE68(first, root[2]);
    func_PAL_0029DE68(second, root[1]);
    func_0011AEA0(0);
    func_L00_00300090(root[2], root[4]);
    func_L00_00300378(root[1]);
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
    func_002F0FA0();
    func_L00_003032F0();
    func_L00_0032D208(index);
    func_L00_00303418(index);
    func_002B6E78(argument, 1, 1024);
    if (func_002B49C8(2))
        func_002B72E8(0);
}
