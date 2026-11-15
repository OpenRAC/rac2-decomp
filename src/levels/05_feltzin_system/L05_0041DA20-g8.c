#include "common.h"

typedef struct {
    int id, pad4[4], count, pad18[3], enabled, pad28, pending;
    float radius;
    int pad34[6]; void *callbacks[3]; int pad58[8];
    char *object; int pad7C[5]; int mode; int pad94[2];
    int settings[4];
} Control05;
extern Control05 D_L05_00221D10;
typedef struct {
    int id, a4, a8, aC, a10;
    char pad14[0x28 - 0x14];
    int target; char pad2C[8]; int stage; char pad38[8];
    int warmup, delay, first, second, third, fourth, fifth, timeout;
} State05;
extern unsigned char D_001395B8[];
extern char g_hero_state[];
extern char D_L05_002A1800[];
extern unsigned char D_L05_001B2000[] __attribute__((sda)), D_L05_001B2001[] __attribute__((sda)), D_L05_001B2002[] __attribute__((sda));
extern float D_L05_001B2004[] __attribute__((sda)), D_L05_001B2008[] __attribute__((sda)), D_L05_001B200C[] __attribute__((sda)), D_L05_001B2010[] __attribute__((sda));
extern int D_L05_001B2014[] __attribute__((sda));
extern unsigned char D_L05_001B3558[] __attribute__((sda)), D_L05_001B3559[] __attribute__((sda)), D_L05_001B355A[] __attribute__((sda));
extern float D_L05_001B355C[] __attribute__((sda)), D_L05_001B3560[] __attribute__((sda)), D_L05_001B3564[] __attribute__((sda)), D_L05_001B3568[] __attribute__((sda));
extern int D_L05_001B356C[] __attribute__((sda)), D_L05_001B3554[] __attribute__((sda));
extern int D_L05_001AA6A0[] __attribute__((sda)), D_L05_001AA6A8[] __attribute__((sda));
extern int D_L05_001B1354[] __attribute__((sda)), D_L05_001B1358[] __attribute__((sda)), D_L05_001B135C[] __attribute__((sda));
extern int D_L05_001A8F00[] __attribute__((sda));
extern int D_L05_001A904C MACRO_ADDR;
extern float D_L05_001B2D84[] __attribute__((sda));
extern char *D_L05_001B251C[] __attribute__((sda));
extern int slot_find_active_in_chain(int);
extern void hero_set_state_value_a(int), hero_set_state_value_b(int), level_select_random_object(void);
extern void level_store_pair_with_increment(int, int), moby_set_flag_bit(void *, int);
extern int hero_l00_set_action(int, int);
extern void hero_set_state_value_c(int);
extern int LockedEntryMenuInput(void);
extern void ship_save_transform_state(void);
extern int subtitle_request_voice_line(int, int);
extern int math_fast_float_d(void *);
extern void feltzin_mission_one_update(void *), feltzin_mission_two_update(void *);
extern void feltzin_mission_three_update(void *), UpdateFeltzinGateCourse(void *);
extern void level_store_value_pair(int, void *);
extern int cam_is_mode_active(void);
extern void feltzin_challenge_reset_free_records(void), feltzin_challenge_shutdown(void), DrawFeltzinCombatHud(void);
extern int feltzin_target_damage(char *, int);
extern int D_L05_001B1360 __attribute__((sda));
extern int D_L05_001B13B0 __attribute__((sda));
extern int D_L05_001B13E8 __attribute__((sda));
extern int D_L05_001B13DC __attribute__((sda));
extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13B4 __attribute__((sda));
extern int D_L05_001B13B8 __attribute__((sda));
extern int D_L05_001B13BC __attribute__((sda));
extern int D_L05_001B1390 __attribute__((sda));
extern int D_L05_001B1394 __attribute__((sda));
extern int D_L05_001B1398 __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D4 __attribute__((sda));
extern int D_L05_001B13E0 __attribute__((sda));
extern int D_L05_001B2048 __attribute__((sda));
extern int D_L05_001B13F0 __attribute__((sda));
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
/* Per-frame update. The first frame resets the control record, the timers in the moby's state and
   the saved mode record, picks the first usable D_L05_002A1800 entry and sets flags on the hero's
   moby; later frames run func_L05_00379B60 and, after five settled frames, put the hero in action
   0x31 and dispatch on the mode in D_L05_001B1360. */
void feltzin_challenge_controller_update(char *object)
{
    State05 *sub = *(State05 **)(object + 0x68);
    int one;
    char *hero, *p;
    switch ((unsigned char)object[0x20]) {
    case 0:
        *(short *)(object + 0x32) = 0x1FF;
        *(unsigned char *)(object + 0x30) = 0xFF;
        object[0x20] = 1;
        D_L05_00221D10.id = sub->id;
        D_L05_00221D10.radius = 8.0f;
        D_L05_001B1360 = -2;
        D_L05_00221D10.enabled = 1;
        D_L05_001B13B0 = (int)object;
        D_L05_001B13E8 = 1;
        D_L05_001B13DC = 0;
        D_L05_001B1364 = 0;
        D_L05_001B13B4 = 0;
        D_L05_001B13B8 = 0;
        D_L05_001B13BC = 0;
        D_L05_001B1390 = 0;
        D_L05_001B1394 = 0;
        D_L05_001B1398 = 0;
        D_L05_001B13A8 = 0;
        D_L05_001B13AC = 0;
        *(short *)(object + 0x32) = 0x1FF;
        *(unsigned char *)(object + 0x30) = 0xFF;
        object[0x20] = 1;
        sub->stage = 0;
        D_L05_001B13D8 = 0;
        sub->warmup = 5400; sub->delay = 7200;
        sub->first = 150; sub->second = 180;
        sub->third = 300; sub->fourth = 480;
        sub->fifth = 120; sub->timeout = 108000;
        D_L05_001B3554[0] = 540;
        D_L05_00221D10.callbacks[0] = feltzin_challenge_reset_free_records;
        D_L05_00221D10.callbacks[1] = feltzin_challenge_shutdown;
        D_L05_00221D10.callbacks[2] = feltzin_target_damage;
        D_L05_00221D10.object = object;
        hero_set_state_value_a(1);
        hero_set_state_value_b(0);
        while (!I(D_L05_002A1800 + slot_find_active_in_chain(D_L05_001B13DC)*40,0) ||
               !*(short *)(D_L05_002A1800 + slot_find_active_in_chain(D_L05_001B13DC)*40 + 0x1E))
            D_L05_001B13DC++;
        D_L05_001AA6A0[0] = (int)feltzin_challenge_reset_free_records;
        D_L05_001AA6A8[0] = (int)feltzin_challenge_shutdown;
        D_L05_001B1350 = D_001395B8[0x61];
        D_L05_001B1354[0] = D_001395B8[0x62];
        D_L05_001B1358[0] = D_001395B8[0x63];
        D_L05_001B135C[0] = D_001395B8[0x64];
        if (!D_L05_001B1350) D_L05_001B13F4 = 1;
        else D_L05_001B13F4 = 0;
        hero = g_hero_state;
        D_L05_001B3558[0] = D_L05_001B2000[0];
        D_L05_001B3559[0] = D_L05_001B2001[0];
        D_L05_001B355A[0] = D_L05_001B2002[0];
        D_L05_001B3560[0] = D_L05_001B2008[0];
        D_L05_001B3568[0] = D_L05_001B2010[0];
        D_L05_001B355C[0] = D_L05_001B2004[0];
        D_L05_001B3564[0] = D_L05_001B200C[0];
        D_L05_001B356C[0] = D_L05_001B2014[0];
        D_L05_00221D10.mode = 4;
        D_L05_00221D10.settings[0] = sub->a4;
        D_L05_00221D10.settings[1] = sub->a8;
        D_L05_00221D10.settings[2] = sub->aC;
        D_L05_00221D10.settings[3] = sub->a10;
        p = *(char **)(hero + 0x2290);
        if (p)
            *(short *)(p+0x34) |= 0x41;
        /* fall through */
    case 1:
        one = 1;
        level_select_random_object();
        level_store_pair_with_increment((int)(D_L05_001B2D84[0] * -230.0f + 0.5f), 2);
        if (!D_L05_001B13D4) {
            moby_set_flag_bit(D_L05_001B251C[0] + sub->target*256,1);
            D_L05_001B13D4 = one;
            D_L05_001B13D8 = 0;
        }
        if (D_L05_001B13D8++ < 5 || D_L05_001A8F00[0] == 2) break;
        hero_l00_set_action(0x31,0);
        if (D_L05_001B13E8) {
            hero_set_state_value_c(1);
            D_L05_001B1360 = LockedEntryMenuInput();
            if (D_L05_001B1360 != -2) ship_save_transform_state();
            break;
        }
        if (!D_L05_001B13E0) {
            subtitle_request_voice_line(0xA17,110);
            D_L05_001B13E0 = one;
        }
        if (math_fast_float_d((char *)sub+0x54)) D_L05_00221D10.pending = 0;
        else D_L05_00221D10.pending = one;
        hero_set_state_value_c(0);
        if (D_L05_001B1360 != -2 && D_L05_001B2048 >= 3) {
            switch (D_L05_001B1360) {
            case 0: feltzin_mission_one_update(object); break;
            case 1: feltzin_mission_two_update(object); break;
            case 2: feltzin_mission_three_update(object); break;
            case 3: UpdateFeltzinGateCourse(object); break;
            }
        }
        if (D_L05_001A904C && !D_L05_001B13A8 && !D_L05_001B13F0) {
            level_store_value_pair(0,DrawFeltzinCombatHud);
            D_L05_001B13AC = 0;
            D_L05_001B13A8 = 1;
        }
        break;
    case 2: break;
    case 3:
        if (!cam_is_mode_active()) {
            D_L05_00221D10.pending = 0;
            D_L05_00221D10.count++;
            object[0x20] = 1;
        }
        break;
    }
}
