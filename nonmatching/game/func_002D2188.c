/* Complete C near miss; not linked and no matching credit.
 * Measured related menu profile: -O2 -G8 -fno-expensive-optimizations
 * -ffunction-sections -fno-builtin, 580/592 bytes, USA 0/28 places.
 * Seven trials: ordinary G0 600 bytes, tied absolute SDATA scalar model 604,
 * G8 580 with extra cached address/FPR lifetimes; fine force-mem control and
 * GCSE suppression both 584. The qualified 002D2538 menu profile restores
 * in-place address loads and immediate float arguments, but still omits the
 * retail unused s1 save/reload and has a shorter frame. -g ties.
 * Real nonvoid lookup/text returns and 64-bit text/rectangle colours retained.
 * No local buffers. Reopen with measured menu expression/lifetime evidence;
 * do not add a padding object or synthetic live value to force a save.
 */
#include "common.h"

extern void func_0027C540(long);
extern void func_0027C660(void);
extern s32 func_00336D50(u8 *, s32);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002CE5D0(int, int);
extern void func_0028FC48(int, int, int, int, u64, int);
extern s32 func_00288FB8(s32);
extern int func_0027FAA8(int, int, u64, u8 *, int);
extern u8 *D_001A8CFC;
extern int D_001A7340;
extern int D_001ABA6C __attribute__((sda));
extern int D_001ABA68 __attribute__((sda));
extern float D_001B23A8;
extern float D_001B23A4;
extern struct { s16 text; s16 reserved; } D_001ABD68[];

int func_002D2188(void)
{
    float zero;
    int offset;
    int center;
    func_0027C540(0);
    offset = 0x8710;
    zero = 0.0f;
    func_00300A00((char *)func_00336D50(D_001A8CFC + offset, 0xDE), 0x60442D00,
                 D_001A7340 / 2, D_001ABA6C, 1.0f, D_001B23A8, zero);
    func_00300A00((char *)func_00336D50(D_001A8CFC + offset, 0xDF), 0x60241700,
                 D_001A7340 / 2, D_001ABA6C, 1.0f, D_001B23A8, zero);
    func_00300A00((char *)func_00336D50(D_001A8CFC + offset, 0xE0), 0x55F0C070,
                 D_001A7340 / 2, D_001ABA6C, 1.0f, D_001B23A8, zero);
    func_002CE5D0(D_001ABA68 != 0, D_001ABA68 != 5);
    func_0028FC48(66, (int)(D_001B23A4 * 330.0f + 0.5f), 463,
                 (int)(D_001B23A4 * 332.0f + 0.5f), 0x55F0C070, 0);
    center = D_001A7340 / 2;
    func_0027FAA8(center, 311, 0x80F0F0F0ULL,
                 (u8 *)func_00288FB8(D_001ABD68[D_001ABA68].text), -1);
    func_0027FAA8(432, 375, 0x80F0F0F0ULL, (u8 *)func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
