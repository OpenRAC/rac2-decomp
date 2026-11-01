#include "include_asm.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef unsigned short u16;
extern s32 func_002A8AF0(f32 *point, f32 *vertices, s32 count);
extern u8 D_L11_004465F8[];
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((section(".sdata")));
extern s32 func_417238(s32);
extern s32 func_417270(s32);
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C;
extern void func_L11_0044C4F0(u8 *);
extern void func_L11_00452DF8(u8 *);
extern void func_L11_00454DD8(u8 *);
extern void func_L11_00456540(u8 *);
extern void func_L11_00436A78(u8 *);
extern void func_L11_0043AB28(u8 *);
extern u8 *D_L11_001B368C __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L11_001FC420[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
         p++)
extern s16 func_L02_004024A0(u8 *);
extern s32 func_L02_003D7300(u8 *);
extern s32 func_L11_00441FB8(u8 *, u8 *, s32);
extern void func_L02_003FC248(u8 *, s32, s32);
extern void func_L11_00449970(u8 *, s32, s32);
extern s32 func_L11_0043A800(u8 *);
extern void func_L01_003E9CF8(u8 *, s32, void (*)(u8 *));
extern void func_L00_002B30E8(void);
extern u8 D_00189E20[];
extern u8 D_001A63A8[];

/* Hands every entity of the object's group (state word 0xC0) that the shared test func_L11_00441FB8
   accepts, and whose state byte is not 0xFE, 0xFD or below 3, to the handler of its class (the
   halfword at +0xAA); then runs the test once more on the entity D_00189E20 holds at +0x2290. */
void func_PAL_L11_004479C8(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    u8 *player;

    FOR_EACH_ID(p, 0xC0) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 0xFE)
            continue;
        if (e[0x20] == 0xFD)
            continue;
        if (e[0x20] < 3)
            continue;
        if (func_L11_00441FB8(object, e, 0) == 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0xD98:
            func_L11_00449970(e, 0, 0);
            break;
        case 0xDCF:
            func_L02_003FC248(e, 0, -1);
            func_L11_0044C4F0(e);
            break;
        case 0xDF4:
            func_L02_003FC248(e, 0, -1);
            func_L11_00452DF8(e);
            break;
        case 0xDF7:
            func_L02_003FC248(e, 0, -1);
            func_L11_00454DD8(e);
            break;
        case 0xDF9:
            func_L02_003FC248(e, 0, -1);
            func_L01_003E9CF8(e, 0, func_L11_00456540);
            break;
        case 0xD37:
            func_L02_003FC248(e, 0, -1);
            func_L11_00436A78(e);
            break;
        case 0xD4B:
            if (func_L11_0043A800(e))
                func_L11_0043AB28(e);
            break;
        }
    }
    player = D_00189E20;
    if (func_L11_00441FB8(object, *(u8 **)(player + 0x2290), 1))
        func_L00_002B30E8();
}


extern s32 D_L11_001CAE40;
extern u8 D_001395B8[];
extern s32 D_L11_001AA170 __attribute__((sda));
extern u8 D_00189EA0[];
extern void func_L11_00445D28(u8 *, s32);
extern void func_PAL_L11_00446A20(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern void func_L00_002D7140(s32);
extern void func_PAL_L00_00305110(s32, void *);
extern void func_00282C88(void *);
extern s32 func_L11_0043E108(s32);
extern void func_PAL_L00_002B9CD8(s32, s32, s32, s32);
extern void func_002DF3F8(void *, void *);
extern void func_L01_00323310(void *, void *);

/* Restarts the actor's state machine, releases the level's helper objects and hands
   the state's slots to the two level handlers. */
void func_PAL_L11_00447E20(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    f32 buf[4];

    func_L11_00445D28(obj, 0x20);
    func_002A7750(obj, 1, -1);
    if (*(s32 *)(state + 0x170) != 0) {
        func_L00_002D7140(*(s32 *)(state + 0x170));
        *(s32 *)(state + 0x170) = 0;
    }
    if (D_L11_001CAE40 != 0) {
        func_PAL_L00_00305110(0, *(void **)(state + 0x2F4));
    }
    func_00282C88(buf);
    if (D_001395B8[func_L11_0043E108(1)] != 0) {
        buf[2] = 2.16f;
        func_PAL_L00_002B9CD8((s32)(D_L11_001B368C + (*(s32 *)(state + 0x15C) << 7)) + 0x30, (s32)buf, 0, 1);
    } else {
        buf[2] = -2.52f;
        func_PAL_L00_002B9CD8((s32)(D_L11_001B368C + (*(s32 *)(state + 0x158) << 7)) + 0x30, (s32)buf, 0, 1);
    }
    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
    func_PAL_L11_00446A20(obj);
    func_L01_00323310(*(void **)(state + 0x2F4), *(void **)(state + 0x2FC));
    D_L11_001AA170 = -1;

}

