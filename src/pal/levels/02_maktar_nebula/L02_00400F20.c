#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
extern s32 func_002F3220(char *, float);
extern s32 func_003D77F8(char *);
extern s32 func_L02_003D7830(char *);
extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern void func_L02_003F18E8(char *);
extern void func_L02_0040B980(char *);
extern void func_L02_0040D180(char *);
extern s32 func_L02_00400650(char *, s32);
extern char D_00189EA0[];
extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern void func_L02_003F18E8(char *);
extern void func_L02_0040B980(char *);
extern void func_L02_0040D180(char *);
extern char *D_L02_001B359C __attribute__((section(".sdata")));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s16 func_L02_004024A0(char *);
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L02_001FC060[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)
extern s32 func_L02_003D7300(char *);
extern void func_L02_003D2488(char *, int, int);
extern void func_L02_003FC248(char *, int, int);
extern int func_L00_003206B8(void *, int);
extern void func_L00_002B30E8(void);
extern u8 D_001395B8[];

/* Walks the entities of the group the object names (the group word is re-read for every
   test: the handlers may change it).  Each live, unflagged one that passes the screen
   against the two bounds is handed to the handler of its type.  Afterwards the follow-up is
   called unless the resident record passes the screen. */
void func_PAL_L02_00400F20(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    u8 c;

    FOR_EACH_ID(p, 0x40) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        c = *(u8 *)(e + 0x20);
        if (c == 0xFE)
            continue;
        if (c == 0xFD)
            continue;
        if (c < 3)
            continue;
        if (*(u16 *)(e + 0x34) & 2)
            continue;
        if (func_L00_003206B8(e + 0x10, *(s32 *)(state + 0x80)) == 0 &&
            func_L00_003206B8(e + 0x10, *(s32 *)(state + 0x7C)) != 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0x9CA:
            func_L02_003D2488(e, 0, 0);
            break;
        case 0xB22:
            func_L02_003FC248(e, 0, -1);
            func_L02_003F18E8(e);
            break;
        case 0xC3B:
            func_L02_003FC248(e, 0, -1);
            func_L02_0040B980(e);
            break;
        case 0xC3E:
            func_L02_003FC248(e, 0, -1);
            func_L02_0040D180(e);
            break;
        }
    }
    if (func_L00_003206B8(D_00189EA0, *(s32 *)(state + 0x7C)) == 0)
        func_L00_002B30E8();
}


extern void func_002A7750(char *, s32, s32);
extern char *D_L02_001B368C __attribute__((sda));
extern int func_002A77E0(int);
extern void func_L00_002D7140(char *);
extern void func_L00_00303530(int, int);
extern void func_00282C88(void *);
extern int func_L02_003F9B70(int);
extern void func_L00_002B9D60(char *, float *, int, int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_00323310(int, int);
extern int D_L02_001CAA80;
extern char *D_L02_001B369C __attribute__((sda));
extern int D_L02_001AA1B0 __attribute__((sda));

/* Starts the actor: calls func_L02_00400650 with 0x25 plus a random pick below 2, sets state 1,
   releases the object held at +0xC0 and, by a per-slot flag, hands a vector whose third float
   is -1.59 or 2.16, with the matching 128-byte record, to func_L00_002B9D60; ends by setting
   D_L02_001AA1B0 to -1. */
void func_PAL_L02_004011D8(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    float v[4];

    func_L02_00400650(a0, func_002A77E0(2) + 0x25);
    func_002A7750(a0, 1, -1);
    if (*(char **)(s1 + 0xC0) != 0) {
        func_L00_002D7140(*(char **)(s1 + 0xC0));
        *(s32 *)(s1 + 0xC0) = 0;
    }
    if (D_L02_001CAA80 != 0)
        func_L00_00303530(0, *(s32 *)(s1 + 0x224));
    func_00282C88(v);
    if (D_001395B8[func_L02_003F9B70(0)] != 0) {
        v[2] = -1.59f;
        func_L00_002B9D60(D_L02_001B369C + *(s32 *)(s1 + 0x74) * 128 + 0x30, v, 0, 1);
    } else {
        v[2] = 2.16f;
        func_L00_002B9D60(D_L02_001B368C + *(s32 *)(s1 + 0x78) * 128 + 0x30, v, 0, 1);
    }
    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
    func_L02_003FBB90(a0);
    func_L02_003FC268(a0, 0);
    func_L02_003FC518(a0, 0);
    func_L01_00323310(*(s32 *)(s1 + 0x224), *(s32 *)(s1 + 0x22C));
    D_L02_001AA1B0 = -1;
}

