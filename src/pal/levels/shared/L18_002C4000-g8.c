#include "include_asm.h"

/* func_PAL_L18_002C4000, the PAL copy of func_L18_002C41F0: the same C, where the resident
   counter is scaled to 50 Hz at each use, every read of it goes through $gp, and the 0xB5
   threshold becomes 0x97. */
typedef unsigned char u8;
typedef short s16;
typedef int s32;

extern char D_00189E20[];
extern char D_0018C958[];
extern unsigned char D_0013965E __attribute__((nosda));
extern int D_001A79F0;
extern int D_L18_001AFBB0;
extern int D_L18_001AFBB0_sda __attribute__((sda));
extern int D_001A7390_sda __attribute__((sda));

extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L18_002D0AF8(void);
extern void ref_L18_002C41F0_00(void);
extern int func_00282978(int a0);
extern void ref_L18_002C41F0_01(int a0, int a1);
extern int func_PAL_00289730(int a0, int a1);
extern void ref_L18_002C41F0_02(void);
extern void func_L00_002AE0C8(void);
extern void func_PAL_L00_002B9C20(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9600(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_L00_003080D0(void *a0);
extern void func_L18_00428100(void *a0);
extern void func_L00_002A9760(void);
extern void func_002A677C(int a0);

void func_PAL_L18_002C4000(void)
{
    char *base;
    char *hero;
    char *blk;

    func_PAL_L00_002D29E8();
    func_PAL_L18_002D0AF8();
    ref_L18_002C41F0_00();

    base = D_00189E20;
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (D_L18_001AFBB0 == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (func_00282978(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        ref_L18_002C41F0_01(0x91, 1);
                    }
                    if (D_001A79F0 == 0x14) {
                        if (D_0013965E == 0) {
                            blk = D_0018C958;
                            if (((s32)D_001A7390_sda * 5 + 2) / 6 - *(unsigned int *)(blk + 0x7900) >= 0x97) {
                                if (func_PAL_00289730(0xA15, 0x6C) != 0) {
                                    if (*(unsigned int *)(blk + 0x7900) < ((s32)D_001A7390_sda * 5 + 2) / 6) {
                                        *(unsigned int *)(blk + 0x7900) = ((s32)D_001A7390_sda * 5 + 2) / 6;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ref_L18_002C41F0_02();

    base = D_00189E20;
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
    func_L00_003080D0(base + 0x80);
    if (*(u8 *)(base + 0x22B4) == 4 && D_L18_001AFBB0_sda == 0 && *(s16 *)(base + 0x1E0) == 0 &&
        *(int *)(base + 0x2294) != 0x6F) {
        func_L18_00428100(*(int *)(base + 0x2290));
    }
    func_L00_002A9760();
    hero = D_00189E20;
    func_002A677C(*(int *)(hero + 0x2290));
}
