#include "include_asm.h"
#include "common.h"

extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));

/* Returns the first boss flag and clears it, so each event is seen only once. */
s32 hrugis_take_boss_flag_a(void) {
    s32 value = D_L10_001B0F44;
    D_L10_001B0F44 = 0;
    return value;
}

/* Returns the second boss flag and clears it, so each event is seen only once. */
s32 hrugis_take_boss_flag_b(void) {
    s32 value = D_L10_001B0F48;
    D_L10_001B0F48 = 0;
    return value;
}

extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));
extern u8 D_L10_00265BA0[];
extern u8 *D_L10_001FB1E0[];
extern u8 *D_001B251C;

/* Clears the arena's 128 records of 0x60 bytes and then walks the entry's two-byte
   id list, flagging every live object of one class. */
void hrugis_init_group_states(u8 *group) {
    s32 *clearPtr;
    s32 i;
    u8 *idList;
    u16 *idPtr;
    u8 *moby;

    D_L10_001B0F44 = 0;
    clearPtr = (s32 *)D_L10_00265BA0;
    D_L10_001B0F48 = 0;
    clearPtr = (s32 *)((u8 *)clearPtr + 0x2FE0);
    for (i = 0x7F; i >= 0; i--) {
        *clearPtr = 0;
        clearPtr -= 0x18;
    }
    idList = D_L10_001FB1E0[group[0x21]];
    if (idList == 0)
        return;
    idPtr = (u16 *)idList;
    do {
        moby = D_001B251C + ((*idPtr & 0x7FFF) << 8);
        moby[0x20] = 1;
        if ((s16)*idPtr < 0)
            break;
        idPtr++;
    } while (1);
}

extern void func_0032BD98(s32 a0, u8 *a1);
extern void func_0032AF78(s32 a0);

/* Releases both timed effects the entry's live objects still hold: the id list walks the
   same arena records as func_L10_00417440, one record per id, and tears down the two
   effect slots at +0x2C4 and +0x2C0 of each record. */
void hrugis_release_group_effects(u8 *group) {
    u16 *idPtr;
    u8 *moby;
    u8 *vars;
    u8 *idList;
    u32 childVars;

    idList = D_L10_001FB1E0[group[0x21]];
    if (idList == 0)
        return;
    idPtr = (u16 *)idList;
    do {
        moby = D_001B251C + ((*idPtr & 0x7FFF) << 8);
        vars = *(u8 **)(moby + 0x68);
        if (*(u8 **)(vars + 0x2C4) != 0) {
            func_0032BD98((s32)*(u8 **)(vars + 0x2C4), vars + 0x370);
            func_0032BD98((s32)*(u8 **)(vars + 0x2C4), vars + 0x3B0);
            childVars = *(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2C4) + 0x68) + 0x18);
            if (childVars != 0)
                func_0032AF78(childVars);
            func_0032AF78((s32)*(u8 **)(vars + 0x2C4));
            *(u32 *)(vars + 0x2C4) = 0;
        }
        if (*(u8 **)(vars + 0x2C0) != 0) {
            func_0032BD98((s32)*(u8 **)(vars + 0x2C0), vars + 0x2F0);
            func_0032BD98((s32)*(u8 **)(vars + 0x2C0), vars + 0x330);
            childVars = *(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2C0) + 0x68) + 0x18);
            if (childVars != 0)
                func_0032AF78(childVars);
            func_0032AF78((s32)*(u8 **)(vars + 0x2C0));
            *(u32 *)(vars + 0x2C0) = 0;
        }
    } while ((s16)*idPtr++ >= 0);
}

/* The mission state (D_L10_00221CD0), as far as func_L10_00423500 resets it. */
typedef struct {
    u8 pad00[0x10];
    s32 f10;                    /* 0x10 */
    s32 rounds;                 /* 0x14 */
    u8 pad18[0x28 - 0x18];
    s32 f28;                    /* 0x28 */
    s32 waiting;                /* 0x2C */
    f32 f30;                    /* 0x30 */
} MissionState;

/* A 40-byte reward slot of D_L10_002A3C70: available while value has not reached limit. */
typedef struct {
    u8 pad[16];
    s32 limit;                  /* 0x10 */
    s32 value;                  /* 0x14 */
    u8 tail[16];
} RewardSlot;

extern s32 D_L10_001B13A0 __attribute__((sda));  /* the selected kind, -2 for none */
extern s32 g_mission_initialized __attribute__((sda));
extern s32 D_L10_001B1438 __attribute__((sda));  /* set while a kind is being chosen */
extern MissionState D_L10_00221CD0;
extern RewardSlot D_L10_002A3C70[];

extern s32 table_find_last_used_entry(s32 kind);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_b(s32 value);
extern void table_reset_working_values(void);
extern void level_clear_object_records(void);

/* Resets the mission state and refills the reward slot of kind 6. */
void hrugis_reset_mission_state(void *object) {
    s32 slot;

    D_L10_001B13A0 = -2;
    D_L10_001B1438 = 1;
    D_L10_00221CD0.waiting = 1;
    D_L10_00221CD0.f28 = 100;
    g_mission_initialized = 0;
    D_L10_00221CD0.rounds = 0;
    slot = table_find_last_used_entry(6);
    D_L10_002A3C70[slot].value = D_L10_002A3C70[slot].limit;
    entry_init_all_registered();
    D_L10_00221CD0.f30 = 8.0f;
    D_L10_00221CD0.f10 = 0;
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
}
