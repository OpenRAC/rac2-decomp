#include "include_asm.h"
#include "names.h"
typedef unsigned long long u64;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned char u8;
extern int D_001A72DC;
extern int D_001B23C8;
extern void BuildFrameDmaChain(void *, int);

/* FMV GS packet builder: one 0x40-byte header record, then a 0x60-byte record per
   (row, column), then the closing A_B word pair at the end of the run. */
void func_US2_00350B60(void *a0, int a1, int a2, int a3, int t0)
{
    u8 *p = (u8 *)a0;
    int rows = a2 >> 4;
    int cols = a3 >> 4;
    int i, j;
    u64 c00, c10, c18, c28, c38, c40;
    u32 off, addr;

    *(u64 *)(p + 0x00) = 0x10000003;
    *(u64 *)(p + 0x08) = 0;
    *(u64 *)(p + 0x10) = 0x1000000000000002ULL;
    *(u64 *)(p + 0x18) = 0xE;
    *(u64 *)(p + 0x20) = ((ll)D_001A72DC >> 8) << 32 | 0x8000000000000LL;
    *(u64 *)(p + 0x28) = 0x50;
    *(u64 *)(p + 0x30) = 0x1000000010ULL;
    *(u64 *)(p + 0x38) = 0x52;

    p += 0x40;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c00 = 0x10000004;
            c10 = 0x1000000000000002ULL;
            c18 = 0xE;
            c28 = 0x51;
            c38 = 0x53;
            c40 = 0x0800000000000040ULL;
            *(u64 *)(p + 0x00) = c00;
            *(u64 *)(p + 0x08) = 0;
            *(u64 *)(p + 0x10) = c10;
            *(u64 *)(p + 0x18) = c18;
            *(u64 *)(p + 0x20) = (((u64)(i << 4)) << 32) | (((u64)(j << 4)) << 48);
            *(u64 *)(p + 0x28) = c28;
            *(u64 *)(p + 0x30) = 0;
            *(u64 *)(p + 0x38) = c38;
            *(u64 *)(p + 0x40) = c40;
            *(u64 *)(p + 0x48) = 0;
            *(u32 *)(p + 0x50) = 0x30000040;
            *(u32 *)(p + 0x54) = a1 & 0x0FFFFFFF;
            *(u64 *)(p + 0x58) = 0;
            a1 += 0x400;
            p += 0x60;
        }
    }

    *(u32 *)(p + 0x00) = 0x20000000;
    off = (t0 << 14) + 0x1C81C0;
    addr = D_001B23C8 + off;
    *(u32 *)(p + 0x0C) = 0;
    *(u32 *)(p + 0x08) = 0;
    *(u32 *)(p + 0x04) = addr;
    BuildFrameDmaChain((void *)(u32)(D_001B23C8 + off), 1);
}
