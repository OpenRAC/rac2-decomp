#include "include_asm.h"

extern void func_L02_003FDDE8(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(float, float, long long, char *, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_L02_003F9B70(int);
extern unsigned char D_001395B8[0x100];
extern unsigned char D_PAL_001A7C3C;
extern int D_PAL_L02_001B14D0[2] __attribute__((sda));
extern float D_PAL_L02_001B14C8 __attribute__((sda));
extern int D_PAL_L02_001B14CC __attribute__((sda));
extern int D_PAL_L02_001B14E8 __attribute__((sda));
extern int D_PAL_L02_001B14EC __attribute__((sda));
extern int D_PAL_L02_001B14F0 __attribute__((sda));
extern int D_PAL_L02_001B14F4 __attribute__((sda));
extern int D_PAL_L02_001B14F8 __attribute__((sda));
extern int D_PAL_L02_001B14FC __attribute__((sda));
extern int D_PAL_L02_001B1500 __attribute__((sda));
extern int D_PAL_L02_001B1508 __attribute__((sda));
extern int D_PAL_L02_001B1518 __attribute__((sda));
extern int D_PAL_L02_001B150C;
extern int D_PAL_L02_001B1510;
extern int D_PAL_L02_001B1514;
extern float D_PAL_L02_001B3EA4;
extern int D_PAL_L02_001B3EA0;
extern char D_PAL_L02_001B1258[];
extern char D_PAL_L02_0028E790[];

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_PAL_L02_001B3EA0;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* func_PAL_L02_00403FF0, the PAL copy of func_L02_003FF6E8 (src/levels/02_maktar_nebula/
   L02_003FF6E8-g8.c) with this release's data and text ids; the first x is taken per language
   from D_PAL_L02_001B14D0. Its data is named D_PAL_L02_<PAL address>: several D_L02_ spellings
   of these addresses already name other data in functions linked into this level. */
void func_PAL_L02_00403FF0(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    func_L02_003FDDE8(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)func_00288FB8(0xE6A);
    one = 1;
    s = D_PAL_L02_001B3EA4;
    x = (float)D_PAL_L02_001B14D0[D_PAL_001A7C3C];
    r0 = scaled_coord(D_PAL_L02_001B14E8, s, half, one);
    func_0027F640(x, (float)r0, D_PAL_L02_001B14CC, text, D_PAL_L02_001B14C8, -1,
                  func_0027C878(1), D_PAL_L02_0028E790);
    s = D_PAL_L02_001B3EA4;
    r1 = scaled_coord(D_PAL_L02_001B1508, s, half, one);
    r2 = scaled_coord(D_PAL_L02_001B150C, s, half, one);
    r3 = scaled_coord(D_PAL_L02_001B14F4, s, half, one);
    func_002802E0(buf1, r1, r2, D_PAL_L02_001B1510, D_PAL_L02_001B1514, D_PAL_L02_001B14F0, r3,
                  D_PAL_L02_001B1518, 3);
    if (*(short *)(state + 0x118) == 0 && D_001395B8[func_L02_003F9B70(0)] < 2) {
        text = (char *)func_00288FB8(0xE6B);
        func_00280270(buf1, D_PAL_L02_001B14EC, text, func_001157AC(text));
    } else {
        text = (char *)func_00288FB8(0xE87);
        msg = (char *)func_00288FB8(0xE83);
        func_00115DA8(buf2, D_PAL_L02_001B1258, text, *(int *)(state + 0x110), msg);
        func_00280270(buf1, D_PAL_L02_001B14EC, buf2, func_001157AC(buf2));
    }
    text = (char *)func_00288FB8(0xE6C);
    {
        float half = 0.5f;
        int one = 1;

        s = D_PAL_L02_001B3EA4;
        r1 = scaled_coord(D_PAL_L02_001B1508, s, half, one);
        r2 = scaled_coord(D_PAL_L02_001B150C, s, half, one);
        r3 = scaled_coord(D_PAL_L02_001B1500, s, half, one);
        func_002802E0(buf1, r1, r2, D_PAL_L02_001B1510, D_PAL_L02_001B1514, D_PAL_L02_001B14FC, r3,
                      D_PAL_L02_001B1518, 3);
    }
    func_00280190(buf1, D_PAL_L02_001B14F8, text, func_001157AC(text));
}

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
