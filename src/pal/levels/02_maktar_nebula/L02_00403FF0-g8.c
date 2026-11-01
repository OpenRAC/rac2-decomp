#include "include_asm.h"

extern void func_002A7750(char *, int, int);
extern char *D_L02_001B1190[] __attribute__((sda));
typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern char *D_L02_001B1190[2] __attribute__((sda));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s32 func_00312B58(char *);
extern s32 func_L02_00416800(char *);
extern s32 func_002A77E0(s32);
extern s32 func_L02_003D77B8(char *);
extern s32 func_L02_003FD000(char *);
extern unsigned char D_001395B8[0x100];
extern int func_L02_003F9B70(int);
extern int func_L02_00400650(char *, int);
extern s32 D_L02_001B30C8;
extern s32 func_002A7820(s32, s32);
extern s32 D_0018C2EC __attribute__((nosda));
extern s32 func_L02_00400650(char *, s32);
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_001395B8[];
extern u8 D_00139568[];
typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L02_003FF9A0_Rec;
extern L02_003FF9A0_Rec D_L02_00264A70[];
extern void func_PAL_L00_002C4480(s32, s32);
extern s32 func_L00_0032EF10(s32, s32, s32 *);
extern s32 func_L02_003F9B70(s32);
extern s32 func_00288D58(void);
extern void func_PAL_L02_004011D8(char *);
extern void func_PAL_L02_00403FF0(char *);
extern void func_L00_002E6CF0(void *, void *);
extern const s32 D_L02_001B1524 __attribute__((sda));
extern s32 D_L02_001B1530 __attribute__((sda));
extern s32 D_001A7A00;
extern s32 func_00282948(void *);

/* Calls func_PAL_L00_002C4480(0x6F, 1) unless D_0018C0B4 already is 0x6F.  When the input test
   func_L00_0032EF10(0x40, 0x3C, 0) holds, the object changes state to 7 and its selection (state
   half-word 0x118) moves to the next entry of the table at D_L02_001B1190 that is usable: the flag
   of D_001395B8 at the index func_L02_003F9B70 gives for the entry's word at +8 is set, entries from
   12 on also pass func_00288D58, and entries 7 and 8 need the byte at +4 of the record of
   D_L02_00264A70 that D_00139568[0x1E] (0x2A) names.  The pick is kept in the state and in
   D_001395B8[0x3C].  Otherwise, when func_L00_0032EF10(0x10, 0x3C, 0) holds, func_PAL_L02_004011D8
   runs; if neither test holds the callback func_PAL_L02_00403FF0 is registered for the object. */
void func_PAL_L02_004042C0(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    s32 i;
    L02_003FF9A0_Rec *r;

    if (D_0018C0B4 != 0x6F)
        func_PAL_L00_002C4480(0x6F, 1);
    if (func_L00_0032EF10(0x40, 0x32, 0) != 0) {
        func_002A7750(a0, 7, -1);
        for (i = *(s16 *)(state + 0x118) + 1; i < 0xE; i++) {
            if (D_001395B8[func_L02_003F9B70(*(s32 *)(D_L02_001B1190[i] + 8))] == 0)
                continue;
            if (i >= 0xC && func_00288D58() == 0)
                continue;
            if (i == 7) {
                r = &D_L02_00264A70[D_00139568[0x1E]];
                if (r->f4 == 0)
                    continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[D_00139568[0x2A]];
                if (r->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x118) = i;
            D_001395B8[0x3C] = *(u8 *)(state + 0x118);
            return;
        }
    } else if (func_L00_0032EF10(0x10, 0x32, 0) != 0) {
        func_PAL_L02_004011D8(a0);
    } else {
        func_L00_002E6CF0(func_PAL_L02_00403FF0, a0);
    }
}
