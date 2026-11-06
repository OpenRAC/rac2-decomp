/* func_US2_L10_00422824, the v2.00 copy of func_L10_00421288: the same C, except that state 0
   no longer searches for a record to start from. It sets D_L10_001B1428 to 1 directly, and
   sets D_L10_001B1438 after the zeroed counters instead of before them. */
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
    u8 pad04[0x28 - 0x04];
    s32 moby;                   /* 0x28: index in the moby table */
    u8 pad2C[0x34 - 0x2C];
    s32 f34;                    /* 0x34 */
    u8 pad38[0x40 - 0x38];
    s32 f40;                    /* 0x40 */
    s32 f44;                    /* 0x44 */
    s32 f48;                    /* 0x48 */
    s32 f4C;                    /* 0x4C */
    s32 f50;                    /* 0x50 */
    s32 timer;                  /* 0x54: counted down by func_00282948 */
    s32 f58;                    /* 0x58 */
    s32 f5C;                    /* 0x5C */
} ControllerVars;

/* The mission state the level-5 combat code shares (D_L10_00221CD0). */
typedef struct {
    s32 index;                  /* 0x00: picks a 0x80-byte record of D_001B2614 */
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
    u8 pad7C[0x88 - 0x7C];
    s32 f88;                    /* 0x88: cleared when the selection changes */
    s32 selection;              /* 0x8C: follows D_L10_001B13A0 */
} MissionState;

/* The saved game: Hrugis keeps its four completion counts at 0x66 (func_L10_00425888). */
typedef struct {
    u8 pad00[0x66];
    u8 completions[4];          /* 0x66 */
} SaveGame;

/* The hero (D_00189E20), as far as the controller reads it. */
typedef struct {
    u8 pad0000[0x2290];
    Moby *moby;                 /* 0x2290 */
} Hero;

extern MissionState D_L10_00221CD0;
extern SaveGame D_001395B8;
extern Hero D_00189E20;
extern Moby *D_L10_001B251C;            /* the moby table */
extern s32 D_L10_001B3554;
extern s32 D_L10_001B3558;
extern void (*D_L10_001AA7A0)(void);
extern void (*D_L10_001AA7A8)(void);
/* The completion counts while the level runs: kind 0 at D_L10_001B1390 (sda), 1 to 3
   here (absolute). */
extern s32 D_L10_001B1394;
extern s32 D_L10_001B1398;
extern s32 D_L10_001B139C;
extern s32 D_L10_001A8F00;
extern f32 D_L10_001B2D84;
extern s32 D_0013A170[];
extern s32 D_L10_001B13A0 __attribute__((sda));  /* the selected kind, -2 for none */
extern Moby *D_L10_001B13F0 __attribute__((sda));
extern s32 D_L10_001B1438 __attribute__((sda));  /* set while a kind is being chosen */
extern s32 D_L10_001B1428 __attribute__((sda));  /* index of a D_L10_002A3C70 record */
extern s32 D_L10_001B13A4 __attribute__((sda));
extern s32 D_L10_001B1408 __attribute__((sda));
extern s32 D_L10_001B13D0 __attribute__((sda));
extern s32 D_L10_001B13D4 __attribute__((sda));
extern s32 D_L10_001B13D8 __attribute__((sda));
extern s32 D_L10_001B13E8 __attribute__((sda));
extern s32 D_L10_001B13EC __attribute__((sda));
extern s32 D_L10_001B1424 __attribute__((sda));  /* frames in state 1 */
extern s32 D_L10_001B1430 __attribute__((sda));  /* subtitle 0xA18 queued */
extern s32 D_L10_001B1390 __attribute__((sda));
extern s32 D_L10_001B1444 __attribute__((sda));  /* no kind 0 completion yet */
extern s32 D_L10_001B1420 __attribute__((sda));  /* vars->moby enabled */
extern s32 D_L10_001B142C __attribute__((sda));  /* subtitle 0xA17 queued */
extern s32 D_L10_001B2048 __attribute__((sda));
extern s32 D_L10_001A904C MACRO_ADDR;
extern s32 D_L10_001B1440 __attribute__((sda));

extern void func_L05_00379F18(s32 value);
extern void func_L05_00379F28(s32 value);
extern void func_L05_00379B60(void);
extern void func_L05_0030C930(s32 a0, s32 a1);
extern void func_L00_003294F0(Moby *moby, s32 enabled);
extern s32 func_US2_L00_002C4560(s32 action, s32 animate);
extern void func_L05_00379F48(s32 value);
extern s32 func_US2_L05_00420238(void);
extern void func_L05_00445A98(void);
extern s32 func_US2_00289840(s32 key, s32 selection);
extern s32 func_L10_0037F510(void);
extern s32 func_00282948(s32 *timer);
extern void func_US2_L10_00425CD8(Moby *moby);
extern void func_US2_L10_00425F48(Moby *moby);
extern void func_US2_L10_00426130(Moby *moby);
extern void func_US2_L10_00426260(Moby *moby);
extern void func_US2_0029C548(s32 a0, void (*callback)(void));
extern s32 func_L05_00442860(void);
extern void func_US2_L10_00422CA8(void);
extern void func_US2_L10_00425104(void);
extern void func_US2_L10_004251D0(void);
extern s32 func_L10_00423788(Moby *moby, s32 keep);

/* Update of the Hrugis mission controller. State 0 sets up the mission state, its
   callbacks and the controller's timers and loads the saved completion counts. State 1 runs the shared update:
   after five frames it lets a kind be chosen, queues two subtitles and runs the chosen
   kind's handler. State 3 waits for func_L05_00442860, then counts the round and goes
   back to state 1. */
void func_US2_L10_00422824(Moby *moby)
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
        D_L10_00221CD0.index = vars->index;
        D_L10_00221CD0.f30 = 8.0f;
        D_L10_001B13A0 = -2;
        D_L10_00221CD0.f24 = 1;
        D_L10_001B13F0 = moby;
        D_L10_001B1428 = 1;
        D_L10_001B13A4 = 0;
        D_L10_001B1408 = 0;
        D_L10_001B13D0 = 0;
        D_L10_001B13D4 = 0;
        D_L10_001B13D8 = 0;
        D_L10_001B13E8 = 0;
        D_L10_001B13EC = 0;
        D_L10_001B1438 = 1;
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        vars->f34 = 0;
        D_L10_001B1424 = 0;
        vars->f40 = 162000;
        vars->f50 = 240;
        vars->f44 = 120;
        vars->timer = 480;
        vars->f58 = 120;
        vars->f48 = 10800;
        vars->f5C = 150;
        D_L10_001B3554 = 540;
        D_L10_001B3558 = 360;
        D_L10_001B1430 = 0;
        D_L10_00221CD0.reset = func_US2_L10_00425104;
        D_L10_00221CD0.resetAll = func_US2_L10_004251D0;
        D_L10_00221CD0.onHit = func_L10_00423788;
        D_L10_00221CD0.controller = moby;
        func_L05_00379F18(1);
        func_L05_00379F28(0);
        completed0 = D_001395B8.completions[0];
        completed1 = D_001395B8.completions[1];
        completed2 = D_001395B8.completions[2];
        completed3 = D_001395B8.completions[3];
        D_L10_001AA7A0 = func_US2_L10_00425104;
        D_L10_001AA7A8 = func_US2_L10_004251D0;
        D_L10_001B1394 = completed1;
        D_L10_001B1398 = completed2;
        D_L10_001B139C = completed3;
        D_L10_001B1390 = completed0;
        if (!D_L10_001B1390)
            D_L10_001B1444 = 1;
        else
            D_L10_001B1444 = 0;
        if (D_00189E20.moby != 0)
            D_00189E20.moby->flags |= 0x41;
        /* fall through */
    case 1: {
        /* One 1 for the stores and the test below: literal 1s compile differently. */
        s32 on = 1;

        func_L05_00379B60();
        func_L05_0030C930((s32)(D_L10_001B2D84 * -230.0f + 0.5f), 2);
        if (D_L10_00221CD0.selection != D_L10_001B13A0) {
            D_L10_00221CD0.selection = D_L10_001B13A0;
            D_L10_00221CD0.f88 = 0;
        }
        if (!D_L10_001B1420) {
            func_L00_003294F0(&D_L10_001B251C[vars->moby], 1);
            D_L10_001B1420 = on;
            D_L10_001B1424 = 0;
        }
        if (D_L10_001B1424++ < 5 || D_L10_001A8F00 == 2)
            break;

        func_US2_L00_002C4560(0x31, 0);
        if (D_L10_001B1438) {
            func_L05_00379F48(on);
            D_L10_001B13A0 = func_US2_L05_00420238();
            if (D_L10_001B13A0 != -2)
                func_L05_00445A98();
            break;
        }
        if (!D_L10_001B142C) {
            func_US2_00289840(0xA17, 0x6E);
            D_L10_001B142C = on;
        }
        if ((D_0013A170[0] == on || D_0013A170[0] == 5 || D_0013A170[0] == 10)
            && !func_L10_0037F510() && !D_L10_001B1430) {
            func_US2_00289840(0xA18, 0x6F);
            D_L10_001B1430 = 1;
        }
        if (func_00282948(&vars->timer))
            D_L10_00221CD0.waiting = 0;
        else
            D_L10_00221CD0.waiting = 1;
        func_L05_00379F48(0);
        if (D_L10_001B13A0 != -2 && D_L10_001B2048 >= 3) {
            switch (D_L10_001B13A0) {
            case 0:
                func_US2_L10_00425CD8(moby);
                break;
            case 1:
                func_US2_L10_00425F48(moby);
                break;
            case 2:
                func_US2_L10_00426130(moby);
                break;
            case 3:
                func_US2_L10_00426260(moby);
                break;
            }
        }
        if (D_L10_001A904C && !D_L10_001B13E8 && !D_L10_001B1440) {
            func_US2_0029C548(0, func_US2_L10_00422CA8);
            D_L10_001B13EC = 0;
            D_L10_001B13E8 = 1;
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (!func_L05_00442860()) {
            D_L10_00221CD0.waiting = 0;
            D_L10_00221CD0.rounds++;
            moby->state = 1;
        }
        break;
    }
}
