/* func_PAL_L15_00433068, the PAL copy of func_L15_0042DCE0: the same C, where the timers are
   scaled to 50 Hz, the search of the mission records is gone (the kind index starts at 1
   instead) and D_L15_001B15C4 is set after the other mission state. */
#include "common.h"

/* A moby: one 0x100-byte entry of the moby table. */
typedef struct {
    u8 pad00[0x20];
    u8 state;                   /* 0x20 */
    u8 pad21[0x30 - 0x21];
    u8 updateDistance;          /* 0x30 */
    u8 pad31;
    u16 drawDistance;           /* 0x32 */
    u16 flags;                  /* 0x34 */
    u8 pad36[0x68 - 0x36];
    void *vars;                 /* 0x68: the instance data */
    u8 pad6C[0x100 - 0x6C];
} Moby;

/* The controller's instance data. */
typedef struct {
    s32 index;                  /* 0x00: copied to the mission state */
    u8 pad04[0x24 - 0x04];
    s32 moby;                   /* 0x24: index in the moby table */
    u8 pad28[0x34 - 0x28];
    s32 f34;                    /* 0x34 */
    u8 pad38[0x50 - 0x38];
    s32 f50;                    /* 0x50 */
    s32 f54;                    /* 0x54 */
    u8 pad58[0x64 - 0x58];
    s32 f64;                    /* 0x64 */
    s32 timer;                  /* 0x68: counted down by func_00282948 */
    s32 f6C;                    /* 0x6C */
} ControllerVars;

typedef struct {
    s32 index;                  /* 0x00 */
    u8 pad04[0x14 - 0x04];
    s32 rounds;                 /* 0x14: counted when state 3 ends */
    u8 pad18[0x24 - 0x18];
    s32 f24;                    /* 0x24 */
    u8 pad28[0x2C - 0x28];
    s32 waiting;                /* 0x2C: 1 while the controller's timer runs */
    f32 f30;                    /* 0x30 */
    u8 pad34[0x4C - 0x34];
    void (*reset)(void);        /* 0x4C */
    void (*resetAll)(void);     /* 0x50 */
    s32 (*onHit)(Moby *moby, s32 keep); /* 0x54 */
    u8 pad58[0x78 - 0x58];
    Moby *controller;           /* 0x78 */
} MissionState;

typedef struct {
    u8 pad00[0x6B];
    u8 completions[4];          /* 0x6B */
} SaveGame;

typedef struct {
    u8 pad0000[0x2290];
    Moby *moby;                 /* 0x2290 */
} Hero;

extern MissionState D_L15_00221E10;
extern SaveGame D_001395B8;
extern Hero D_00189E20;
extern Moby *D_L15_001B261C;
extern s32 D_L15_001B369C;
extern s32 D_L15_001B36A0;
extern void (*D_L15_001AA720)(void);
extern void (*D_L15_001AA728)(void);
extern s32 D_L15_001B1524;
extern s32 D_L15_001B1528;
extern s32 D_L15_001B152C;
extern s32 D_L15_001A8F00;
extern f32 D_L15_001B2E84;
extern s32 D_0013A170[];
extern s32 D_L15_001B1530 __attribute__((sda));
extern Moby *D_L15_001B1580 __attribute__((sda));
extern s32 D_L15_001B15C4 __attribute__((sda));
extern s32 D_L15_001B15B0 __attribute__((sda));
extern s32 D_L15_001B1534 __attribute__((sda));
extern s32 D_L15_001B158C __attribute__((sda));
extern s32 D_L15_001B1560 __attribute__((sda));
extern s32 D_L15_001B1564 __attribute__((sda));
extern s32 D_L15_001B1568 __attribute__((sda));
extern s32 D_L15_001B1578 __attribute__((sda));
extern s32 D_L15_001B157C __attribute__((sda));
extern s32 D_L15_001B15AC __attribute__((sda));
extern s32 D_L15_001B15B8 __attribute__((sda));
extern s32 D_L15_001B1520 __attribute__((sda));
extern s32 D_L15_001B15D0 __attribute__((sda));
extern s32 D_L15_001B15A8 __attribute__((sda));
extern s32 D_L15_001B15B4 __attribute__((sda));
extern s32 D_L15_001B2148 __attribute__((sda));
extern s32 D_L15_001A904C MACRO_ADDR;
extern s32 D_L15_001B15CC __attribute__((sda));

extern void func_L05_00379F18(s32 value);
extern void func_L05_00379F28(s32 value);
extern void func_L05_00379B60(void);
extern void func_L05_0030C930(s32 a0, s32 a1);
extern void func_L00_003294F0(Moby *moby, s32 enabled);
extern s32 func_PAL_L00_002C4480(s32 action, s32 animate);
extern void func_L05_00379F48(s32 value);
extern s32 func_PAL_L05_00423A68(void);
extern void func_PAL_L05_0044BEB8(void);
extern s32 func_PAL_00289730(s32 key, s32 selection);
extern s32 func_L10_0037F510(void);
extern s32 func_00282948(s32 *timer);
extern void func_PAL_L15_00436368(Moby *moby);
extern void func_PAL_L15_004366F0(Moby *moby);
extern void func_PAL_L15_00436870(Moby *moby);
extern void func_PAL_L15_00436A10(Moby *moby);
extern void func_PAL_0029C0F0(s32 a0, void (*callback)(void));
extern s32 func_L05_00442860(void);
extern void func_PAL_L15_004334B0(void);
extern void func_PAL_L10_00428C8C(void);
extern void func_PAL_L10_00428D58(void);
extern s32 func_L15_0042FFB8(Moby *moby, s32 keep);

/* Update of the Gorn mission controller; the same body as Hrugis's func_L10_00421288.
   State 0 sets up the mission state, its callbacks and the controller's timers and
   loads the saved completion counts. State 1 runs the shared update and the chosen kind's handler.
   State 3 waits for func_L05_00442860, then counts the round and goes back to state 1. */
void func_PAL_L15_00433068(Moby *moby)
{
    ControllerVars *vars = moby->vars;
    u8 completed0;
    u8 completed1;
    u8 completed2;
    u8 completed3;

    switch (moby->state) {
    case 0:
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        D_L15_00221E10.index = vars->index;
        D_L15_00221E10.f30 = 8.0f;
        D_L15_001B1530 = -2;
        D_L15_00221E10.f24 = 1;
        D_L15_001B1580 = moby;
        D_L15_001B15B0 = 1;
        D_L15_001B1534 = 0;
        D_L15_001B158C = 0;
        D_L15_001B1560 = 0;
        D_L15_001B1564 = 0;
        D_L15_001B1568 = 0;
        D_L15_001B1578 = 0;
        D_L15_001B157C = 0;
        D_L15_001B15C4 = 1;
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        vars->f34 = 0;
        D_L15_001B15AC = 0;
        vars->f50 = 4500;
        vars->f54 = 100;
        vars->f64 = 200;
        vars->f6C = 150;
        vars->timer = 300;
        D_L15_001B369C = 450;
        D_L15_001B36A0 = 300;
        D_L15_00221E10.reset = func_PAL_L10_00428C8C;
        D_L15_00221E10.resetAll = func_PAL_L10_00428D58;
        D_L15_001B15B8 = 0;
        D_L15_00221E10.onHit = func_L15_0042FFB8;
        D_L15_00221E10.controller = moby;
        func_L05_00379F18(1);
        func_L05_00379F28(0);
        completed0 = D_001395B8.completions[0];
        completed1 = D_001395B8.completions[1];
        completed2 = D_001395B8.completions[2];
        completed3 = D_001395B8.completions[3];
        D_L15_001AA720 = func_PAL_L10_00428C8C;
        D_L15_001AA728 = func_PAL_L10_00428D58;
        D_L15_001B1524 = completed1;
        D_L15_001B1528 = completed2;
        D_L15_001B152C = completed3;
        D_L15_001B1520 = completed0;
        if (!D_L15_001B1520)
            D_L15_001B15D0 = 1;
        else
            D_L15_001B15D0 = 0;
        if (D_00189E20.moby != 0)
            D_00189E20.moby->flags |= 0x41;
        /* fall through */
    case 1: {
        /* One 1 for the stores and the test below: literal 1s compile differently. */
        s32 on = 1;

        func_L05_00379B60();
        func_L05_0030C930((s32)(D_L15_001B2E84 * -230.0f + 0.5f), 2);
        if (!D_L15_001B15A8) {
            func_L00_003294F0(&D_L15_001B261C[vars->moby], 1);
            D_L15_001B15A8 = on;
            D_L15_001B15AC = 0;
        }
        if (D_L15_001B15AC++ < 5 || D_L15_001A8F00 == 2)
            break;

        func_PAL_L00_002C4480(0x31, 0);
        if (D_L15_001B15C4) {
            func_L05_00379F48(on);
            D_L15_001B1530 = func_PAL_L05_00423A68();
            if (D_L15_001B1530 != -2)
                func_PAL_L05_0044BEB8();
            break;
        }
        if (!D_L15_001B15B4) {
            func_PAL_00289730(0xA17, 0x6E);
            D_L15_001B15B4 = on;
        }
        if ((D_0013A170[5] == on || D_0013A170[5] == 5 || D_0013A170[5] == 10)
            && !func_L10_0037F510() && !D_L15_001B15B8) {
            func_PAL_00289730(0xA18, 0x6F);
            D_L15_001B15B8 = 1;
        }
        if (func_00282948(&vars->timer))
            D_L15_00221E10.waiting = 0;
        else
            D_L15_00221E10.waiting = 1;
        func_L05_00379F48(0);
        if (D_L15_001B1530 != -2 && D_L15_001B2148 >= 3) {
            switch (D_L15_001B1530) {
            case 0:
                func_PAL_L15_00436368(moby);
                break;
            case 1:
                func_PAL_L15_004366F0(moby);
                break;
            case 2:
                func_PAL_L15_00436870(moby);
                break;
            case 3:
                func_PAL_L15_00436A10(moby);
                break;
            }
        }
        if (D_L15_001A904C && !D_L15_001B1578 && !D_L15_001B15CC) {
            func_PAL_0029C0F0(0, func_PAL_L15_004334B0);
            D_L15_001B157C = 0;
            D_L15_001B1578 = 1;
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (!func_L05_00442860()) {
            D_L15_00221E10.waiting = 0;
            D_L15_00221E10.rounds++;
            moby->state = 1;
        }
        break;
    }
}
