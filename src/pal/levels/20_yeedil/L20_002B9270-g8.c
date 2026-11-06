#include "include_asm.h"

/* func_PAL_L20_002B9270, the PAL copy of func_L20_002B93E0: the same C, where the resident
   counter is scaled to 50 Hz at each use, every read of it goes through $gp, the 0xB5
   threshold becomes 0x97 and the 0x39 hand-off id becomes 0x2F. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_L20_001AFF00 __attribute__((sda));
extern s32 D_001A7390 __attribute__((sda));
extern float D_001A7CF8 __attribute__((sda));
extern s32 D_001A79F0;
extern u8 D_0013965E __attribute__((nosda));

extern char D_00189E20[];
extern char D_00189EA0[];
extern char D_0018C958[];
extern float D_002683EC __attribute__((nosda));

extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L18_002D0AF8(void);
extern void func_L00_002ACA08(void);
extern void func_PAL_L00_002ACE70(char *, char *, char *);
extern void func_PAL_L00_002B88A0(void);
extern s32 func_00282978(s32);
extern s32 func_PAL_L20_002D7920(s32, s32);
extern s32 func_PAL_00289730(s32, s32);
extern void func_L20_002DEBE0(void);
extern void func_L00_002AE0C8(void);
extern void func_PAL_L00_002B9C20(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9600(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002A5B40(void);
extern void func_PAL_L00_002A5E98(void);
extern void func_002E5CF8(void *, void *, void *);
extern void func_L00_003080D0(void *);
extern void func_L18_00428100(s32);
extern void func_L00_002A9760(void);
extern void func_002A677C(s32);

/* The hero's per-frame update: the state-1 fixups, then in state 4 (outside cutscenes, not
   in mode 0x6F) the arming check and the resident timestamp catch-up; then the sub-updates,
   gated twice more by the state byte, and the hand-off of the hero's record. Same game code as
   func_L18_002C41F0. */
void func_PAL_L20_002B9270(void)
{
    char *base;
    char *blk;
    char *hero;

    func_PAL_L00_002D29E8();
    func_PAL_L18_002D0AF8();
    func_L00_002ACA08();

    base = D_00189E20;
    if (*(u8 *)(base + 0x22B4) == 1) {
        func_PAL_L00_002ACE70(base + 0x80, base + 0x90, base + 0x550);
        func_PAL_L00_002B88A0();
    }
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (D_L20_001AFF00 == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (func_00282978(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        func_PAL_L20_002D7920(0x91, 1);
                    }
                    if (D_001A79F0 == 0x14) {
                        if (D_0013965E == 0) {
                            blk = D_0018C958;
                            if (((s32)D_001A7390 * 5 + 2) / 6 - *(unsigned int *)(blk + 0x7900) >= 0x97) {
                                if (func_PAL_00289730(0xA15, 0x6C) != 0) {
                                    if (*(unsigned int *)(blk + 0x7900) < ((s32)D_001A7390 * 5 + 2) / 6) {
                                        *(unsigned int *)(blk + 0x7900) = ((s32)D_001A7390 * 5 + 2) / 6;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    base = D_00189E20;
    func_L20_002DEBE0();
    func_L00_002AE0C8();

    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    func_PAL_L00_002B9C20();
    func_L00_002A5368();
    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    func_L00_002A9600();
    func_L00_002A7958();
    func_L00_002A7748();
    if (*(u8 *)(base + 0x22B4) == 1) {
        D_002683EC = D_001A7CF8;
        func_PAL_L00_002A56D0();
        func_PAL_L00_002A5B40();
        func_PAL_L00_002A5E98();
        if (*(u32 *)(base + 0x24E4) != 0) {
            func_002E5CF8((void *)(*(u32 *)(base + 0x24E4) + 0x10), 0,
                          (void *)(*(u32 *)(base + 0x2290)));
            *(u16 *)(base + 0x2520) = 0x2f;
            *(u16 *)(base + 0x2522) = *(u16 *)(base + 0x24E4);
        }
        *(s32 *)(base + 0x24E4) = 0;
    }
    {
        char *pos = D_00189EA0;
        char *g;

        func_L00_003080D0(pos);
        g = pos - 0x80;
        if (*(u8 *)(g + 0x22B4) == 4 && D_L20_001AFF00 == 0 && *(s16 *)(g + 0x1E0) == 0 &&
            *(int *)(g + 0x2294) != 0x6F)
            func_L18_00428100(*(int *)(g + 0x2290));
    }
    func_L00_002A9760();
    hero = D_00189E20;
    func_002A677C(*(int *)(hero + 0x2290));
}
