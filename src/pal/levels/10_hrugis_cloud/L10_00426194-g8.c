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
extern Hero g_hero_state;
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
extern s32 D_L10_001B1428 __attribute__((sda));  /* index of a mission record */
extern s32 g_mission_initialized __attribute__((sda));
extern s32 D_L10_001B1408 __attribute__((sda));
extern s32 D_L10_001B13D0 __attribute__((sda));
extern s32 D_L10_001B13D4 __attribute__((sda));
extern s32 D_L10_001B13D8 __attribute__((sda));
extern s32 D_L10_001B13E8 __attribute__((sda));
extern s32 D_L10_001B13EC __attribute__((sda));
extern s32 D_L10_001B1424 __attribute__((sda));  /* frames in state 1 */
extern s32 D_L10_001B1430 __attribute__((sda));  /* subtitle 0xA18 queued */
extern s32 g_mission_completion_counts __attribute__((sda));
extern s32 D_L10_001B1444 __attribute__((sda));  /* no kind 0 completion yet */
extern s32 D_L10_001B1420 __attribute__((sda));  /* vars->moby enabled */
extern s32 D_L10_001B142C __attribute__((sda));  /* subtitle 0xA17 queued */
extern s32 D_L10_001B2048 __attribute__((sda));
extern s32 D_L10_001A904C MACRO_ADDR;
extern s32 D_L10_001B1440 __attribute__((sda));

extern void hero_set_state_value_a(s32 value);
extern void hero_set_state_value_b(s32 value);
extern void level_select_random_object(void);
extern void level_store_pair_with_increment(s32 a0, s32 a1);
extern void moby_set_flag_bit(Moby *moby, s32 enabled);
extern s32 hero_l00_set_action(s32 action, s32 animate);
extern void hero_set_state_value_c(s32 value);
extern s32 LockedEntryMenuInput(void);
extern void ship_save_transform_state(void);
extern s32 subtitle_request_voice_line(s32 key, s32 selection);
extern s32 status_any_record_nonzero(void);
extern s32 math_fast_float_d(s32 *timer);
extern void func_PAL_L10_00429880(Moby *moby);
extern void func_PAL_L10_00429B20(Moby *moby);
extern void func_PAL_L10_00429D08(Moby *moby);
extern void func_PAL_L10_00429E20(Moby *moby);
extern void level_store_value_pair(s32 a0, void (*callback)(void));
extern s32 cam_is_mode_active(void);
extern void func_PAL_L10_00426618(void);
extern void func_PAL_L10_00428C8C(void);
extern void func_PAL_L10_00428D58(void);
extern s32 func_PAL_L10_00428E38(Moby *moby, s32 keep);

/* func_PAL_L10_00426194, the PAL copy of func_L10_00421288: the same C, where the
   timers are 50 Hz values, record 1 is set instead of searched for, and
   D_L10_001B1438 is set after the other flags.

   Update of the Hrugis mission controller. State 0 sets up the mission state, its
   callbacks and the controller's timers and loads the saved completion counts. State 1
   runs the shared update:
   after five frames it lets a kind be chosen, queues two subtitles and runs the chosen
   kind's handler. State 3 waits for func_L05_00442860, then counts the round and goes
   back to state 1. */
void func_PAL_L10_00426194(Moby *moby)
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
        g_mission_initialized = 0;
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
        vars->f40 = 135000;
        vars->f50 = 200;
        vars->f44 = 100;
        vars->timer = 400;
        vars->f58 = 100;
        vars->f48 = 9000;
        vars->f5C = 125;
        D_L10_001B3554 = 450;
        D_L10_001B3558 = 300;
        D_L10_001B1430 = 0;
        D_L10_00221CD0.reset = func_PAL_L10_00428C8C;
        D_L10_00221CD0.resetAll = func_PAL_L10_00428D58;
        D_L10_00221CD0.onHit = func_PAL_L10_00428E38;
        D_L10_00221CD0.controller = moby;
        hero_set_state_value_a(1);
        hero_set_state_value_b(0);
        completed0 = D_001395B8.completions[0];
        completed1 = D_001395B8.completions[1];
        completed2 = D_001395B8.completions[2];
        completed3 = D_001395B8.completions[3];
        D_L10_001AA7A0 = func_PAL_L10_00428C8C;
        D_L10_001AA7A8 = func_PAL_L10_00428D58;
        D_L10_001B1394 = completed1;
        D_L10_001B1398 = completed2;
        D_L10_001B139C = completed3;
        g_mission_completion_counts = completed0;
        if (!g_mission_completion_counts)
            D_L10_001B1444 = 1;
        else
            D_L10_001B1444 = 0;
        if (g_hero_state.moby != 0)
            g_hero_state.moby->flags |= 0x41;
        /* fall through */
    case 1: {
        /* One 1 for the stores and the test below: literal 1s compile differently. */
        s32 on = 1;

        level_select_random_object();
        level_store_pair_with_increment((s32)(D_L10_001B2D84 * -230.0f + 0.5f), 2);
        if (D_L10_00221CD0.selection != D_L10_001B13A0) {
            D_L10_00221CD0.selection = D_L10_001B13A0;
            D_L10_00221CD0.f88 = 0;
        }
        if (!D_L10_001B1420) {
            moby_set_flag_bit(&D_L10_001B251C[vars->moby], 1);
            D_L10_001B1420 = on;
            D_L10_001B1424 = 0;
        }
        if (D_L10_001B1424++ < 5 || D_L10_001A8F00 == 2)
            break;

        hero_l00_set_action(0x31, 0);
        if (D_L10_001B1438) {
            hero_set_state_value_c(on);
            D_L10_001B13A0 = LockedEntryMenuInput();
            if (D_L10_001B13A0 != -2)
                ship_save_transform_state();
            break;
        }
        if (!D_L10_001B142C) {
            subtitle_request_voice_line(0xA17, 0x6E);
            D_L10_001B142C = on;
        }
        if ((D_0013A170[0] == on || D_0013A170[0] == 5 || D_0013A170[0] == 10)
            && !status_any_record_nonzero() && !D_L10_001B1430) {
            subtitle_request_voice_line(0xA18, 0x6F);
            D_L10_001B1430 = 1;
        }
        if (math_fast_float_d(&vars->timer))
            D_L10_00221CD0.waiting = 0;
        else
            D_L10_00221CD0.waiting = 1;
        hero_set_state_value_c(0);
        if (D_L10_001B13A0 != -2 && D_L10_001B2048 >= 3) {
            switch (D_L10_001B13A0) {
            case 0:
                func_PAL_L10_00429880(moby);
                break;
            case 1:
                func_PAL_L10_00429B20(moby);
                break;
            case 2:
                func_PAL_L10_00429D08(moby);
                break;
            case 3:
                func_PAL_L10_00429E20(moby);
                break;
            }
        }
        if (D_L10_001A904C && !D_L10_001B13E8 && !D_L10_001B1440) {
            level_store_value_pair(0, func_PAL_L10_00426618);
            D_L10_001B13EC = 0;
            D_L10_001B13E8 = 1;
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (!cam_is_mode_active()) {
            D_L10_00221CD0.waiting = 0;
            D_L10_00221CD0.rounds++;
            moby->state = 1;
        }
        break;
    }
}
