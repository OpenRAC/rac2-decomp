#include "common.h"

typedef int Quad_Dobbo __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern float IntToFloat(int);
extern char *part_spawn_scaling(void *, void *, int, int, int, int, int, int);

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern void moby_set_group_flags();

extern int moby_l01_turn_toward_target(char *, char *);

extern int moby_turn_toward_target_and_step(char *, float *, float);

extern char *D_L09_001B285C __attribute__((sda));

extern char *D_L09_001FFFB560[];

extern void func_2EA110(char *p);

extern void func_31F500(char *a0, char *a1, s32 a2, f32 f12, f32 f13);

extern void func_322578(char *a0, char *a1, s32 a2, s32 a3, f32 f12);

extern void dobbo_apply_setting_by_index(char *a0, s32 a1, char *a2, s32 a3);

extern void dobbo_apply_setting_linked(char *a0, char *a1, s32 a2, s32 a3, s32 a4);

extern s32 func_325E78(char *a0, s32 a1);

extern void func_318450(char *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                        f32 f12, f32 f13, f32 f14);

extern char D_L09_00189EA0[];

extern void dobbo_set_linked_state(s32 a0, u8 a1);

extern char D_L09_001B9C30[];

extern f32 func_2EA578(char *a0, char *a1);

extern f32 func_2EA3E0(f32 x);

extern void func_2EACD0(char *a0, char *a1);

extern void dobbo_set_mode_flags(char *a0, s32 a1, s32 a2, s32 a3);

extern float func_2EB5C0(int a0);
extern int func_2EB698(float *a0, float f12);
extern float func_316AC0(float lo, float hi);
extern void func_30D8D0(char *a0, int a1, float *a2);
extern char *func_32E560(float *a0, float *a1, int a2, int a3, int t0, int t1, int t2, int t3);
extern int func_2EB5D0(float a);

/* func_L09_0040AC48 is in L09_0040AC48-g8.c. */

/* func_L09_0040B0C8 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_0041D650 is in L09_0041D650-g8.c. */

/* func_L09_00421B80 is in L09_003FEA48-zp-g8.c. */

extern int func_316A68(int a, int b);
extern void func_316958(char *a0, int a1, int a2);
extern int func_2EA0E0(char *p);
extern void func_2E8450(char *a0, float *a1, float *a2, int a3, int a4, float f12, float f13, float f14, float f15, float f16);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.c (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.c. */

/* Spawns red and white sparkle particles that float up from two joints of the object. */
void part_spawn_joint_sparkles(char *obj) {
    EffectVector origin;
    EffectVector jointPos;
    EffectVector velocity;
    EffectVector drift;
    int i;
    int j;
    char *particle;

    qcopy(origin.value, obj + 0x10);
    origin.value[3] = 6.0f;
    if (func_2EB698(origin.value, func_2EB5C0(*(s16 *)(obj + 0x32))) == -1)
        return;
    for (i = 12; i < 14; i++) {
        drift.bits = 0;
        drift.value[2] = -(func_316AC0(3.5f, 4.5f) * 0.016666668f);
        velocity.bits = drift.bits;
        for (j = 0; j < 2; j++) {
            func_30D8D0(obj, i, jointPos.value);
            jointPos.value[2] += func_2EB5C0(j) * 0.015f + 0.5f;
            if (j & 1)
                particle = func_32E560(jointPos.value, velocity.value, 0x77FF0000, 0x00FF0060, 0x13, 200, -100, 1);
            else
                particle = func_32E560(jointPos.value, velocity.value, 0x77FF0060, 0x00FF0000, 0x15, 300, -100, 1);
            if (particle)
                particle[9] = ((*(s16 *)(obj + 0x32) >> 5) << 4) + func_2EB5D0(0.0f);
            particle = func_32E560(jointPos.value, velocity.value, 0x77FFFFFF, 0x00FF0000, 0xC, 100, -100, 1);
            if (particle)
                particle[9] = ((*(s16 *)(obj + 0x32) >> 5) << 4) + func_2EB5D0(0.0f);
        }
    }
}

/* func_L09_003FEF00 is in L09_003FEA48-patrol-g8.c. */

/* func_L09_00402D50 is in L09_00402D50-g8.c. */

/* Level 09 helpers. */
/* Tells every moby of class 3415 in the object's group to raise its alert flag. */
void dobbo_alert_path_enemies(char *obj) {
    s16 *list;
    s32 listPtr;
    char *member;
    char *mobyTable;
    if (*(u8 *)(obj + 0x21) == 0xFF) {
        return;
    }
    listPtr = (s32)D_L09_001FFFB560[*(u8 *)(obj + 0x21)];
    if (listPtr == 0) {
        return;
    }
    list = (s16 *)listPtr;
    mobyTable = D_L09_001B285C;
    do {
        member = mobyTable + ((*(u16 *)list & 0x7FFF) << 8);
        if (*(s8 *)(member + 0x20) >= 0) {
            if (*(s16 *)(member + 0xAA) == 0xD57 /* moby class 3415 */) {
                *(u16 *)(*(char **)(member + 0x68) + 0x270) = 1;
            }
        }
    } while (*(s16 *)list++ >= 0);
}

extern s32 moby_count_group_not_in_state(s32 a0, s32 a1);

/* Alerts the group, and for modes 4 and 5 also makes the first idle group member start its next action. */
void dobbo_alert_group_wake_first(char *obj, s32 mode) {
    char *self = obj;
    char *mobyTable;
    u16 *list;
    char *member;
    char *memberVars;

    if (mode == 0) {
        return;
    }
    dobbo_alert_path_enemies(obj);
    if ((u32)(mode - 4) >= 2) {
        return;
    }
    if (*(u8 *)(self + 0x21) == 0xFF) {
        return;
    }
    if (moby_count_group_not_in_state(*(u8 *)(self + 0x21), -1) < 2) {
        return;
    }
    mobyTable = D_L09_001B285C;
    list = (u16 *)D_L09_001FFFB560[*(u8 *)(self + 0x21)];
    do {
        member = mobyTable + ((*list & 0x7FFF) << 8);
        if (*(s16 *)(member + 0xAA) == 0xD57 /* moby class 3415 */) {
            memberVars = *(char **)(member + 0x68);
            if (*(s16 *)(memberVars + 0x26A) == 0) {
                *(s16 *)(memberVars + 0x26A) = 1;
                return;
            }
        }
    } while ((s16)*list++ >= 0);
}

/* Puts the object back at its saved height unless it is in state 9. */
void dobbo_restore_saved_height(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    if (*(u8 *)(obj + 0x20) == 9) {
        return;
    }
    *(f32 *)(obj + 0x18) = *(f32 *)(vars + 0x288);
}

/* func_L09_00403270 reads small data through $gp, so it is defined in
   L09_003FEA48-g8.c. */


/* func_L09_00403700: 152 bytes, one register off - the loop's trip test compares
   into $v0 where retail compares into $v1.  Deposited in
   nonmatching/levels/func_L09_00403700.c. */

/* func_L09_00403798 is in L09_00403798-g8.c. */

/* func_L09_00404C50 is in L09_00404C50-g8.c. */

/* Moves the object toward a point, using one of two movement helpers depending on the mode. */
void dobbo_move_toward_point(char *obj, char *dest, s32 mode) {
    char *vars = *(char **)(obj + 0x68);
    if (mode == 0) {
        moby_l01_turn_toward_target(obj, dest);
    } else {
        moby_turn_toward_target_and_step(obj, (float *)dest, *(f32 *)(vars + 0x33C));
    }
}

/* Counts down the object's two timers, bumps its frame counter and updates its two effects. */
void dobbo_tick_timers_effects(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    u16 frames;
    func_2EA110(vars + 0x330);
    func_2EA110(vars + 0x332);
    frames = *(u16 *)(obj + 0x96);
    if (frames < 0xFFFF) {
        *(u16 *)(obj + 0x96) = frames + 1;
    }
    func_31F500(obj, vars + 0x280, 0, 0.03f, 0.3f);
    func_322578(obj, vars + 0x360, 0, 1, 1.5f);
}

/* Tells every moby of class 3472 in the object's group to raise its alert flag. */
void dobbo_alert_wandering_group(char *obj) {
    s16 *list;
    s32 listPtr;
    char *member;
    char *mobyTable;
    if (*(u8 *)(obj + 0x21) == 0xFF) {
        return;
    }
    listPtr = (s32)D_L09_001FFFB560[*(u8 *)(obj + 0x21)];
    if (listPtr == 0) {
        return;
    }
    list = (s16 *)listPtr;
    mobyTable = D_L09_001B285C;
    do {
        member = mobyTable + ((*(u16 *)list & 0x7FFF) << 8);
        if (*(s8 *)(member + 0x20) >= 0) {
            if (*(s16 *)(member + 0xAA) == 0xD90 /* moby class 3472 */) {
                *(u16 *)(*(char **)(member + 0x68) + 0x336) = 1;
            }
        }
    } while (*(s16 *)list++ >= 0);
}

/* Defined in L09_004050E0.c. */

/* func_L09_004052F8 is defined in L09_003FEA48-g8.c (it reads the group count through $gp). */

/* func_L09_00405490 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_00405610 is defined in L09_00405610-g8.c (small data through $gp, and its own .rodata). */

/* Sets the state byte of the linked object (a switch or door) with the given index. */
void dobbo_set_linked_state(s32 mobyIndex, u8 newState) {
    char *moby;
    if (mobyIndex == -1) {
        return;
    }
    moby = D_L09_001B285C;
    moby += mobyIndex << 8;
    if (moby == 0) {
        return;
    }
    if (*(u8 *)(moby + 0x20) == 0xFE) {
        return;
    }
    if (*(u8 *)(moby + 0x20) == 0xFD) {
        return;
    }
    if (*(s16 *)(moby + 0xAA) == 0x102 /* moby class 258 */ || *(s16 *)(moby + 0xAA) == 0xDE0 /* moby class 3552 */) {
        *(u8 *)(moby + 0x95) = newState;
    }
}

/* Calls the linked-object helper unless the index is empty. */
void dobbo_activate_linked_if_valid(s32 mobyIndex) {
    if (mobyIndex == -1) {
        return;
    }
    moby_set_group_flags(mobyIndex);
}

/* func_L09_00406BF8: 112 bytes against retail's 108, one saved register too many.
   Deposited in nonmatching/levels/func_L09_00406BF8.c. */

/* Marks the linked object as finished and clears the link. */
void dobbo_release_linked(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    s32 linkIndex = *(s32 *)(vars + 0x5C);
    if (linkIndex == -1) {
        return;
    }
    *(u8 *)((char *)((linkIndex << 8) + (s32)D_L09_001B285C) + 0xBC) = 1;
    *(s32 *)(vars + 0x5C) = -1;
}

/* func_L09_00406CC0 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406E78 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406FC8 is in L09_00406FC8-g8.c. */

/* Sets an entity's colour key, or hands an off-kind entity to the shared body. */
void dobbo_apply_setting_linked(char *controller, char *target, s32 enable, s32 activeMode, s32 modelMode)
{
    u8 byteValue;
    s16 cls;
    char *targetVars;

    if (target == 0) {
        return;
    }
    byteValue = *(u8 *)(target + 0x20);
    if (byteValue == 0xFE) {
        return;
    }
    if (byteValue == 0xFD) {
        return;
    }
    cls = *(s16 *)(target + 0xAA);
    if (cls == 0xD0F /* Megacorp Trooper Legs */) {
        targetVars = *(char **)(target + 0x68);
        *(u8 *)(targetVars + 0x31C) = enable;
        byteValue = *(u8 *)(target + 0x30);
        if (byteValue != 0xFF) {
            *(u8 *)(targetVars + 0x31E) = byteValue;
        }
        if (enable != 0) {
            *(u8 *)(target + 0x30) = 0xFF;
        }
        return;
    }
    if (cls == 0xD09 /* moby class 3337 */ || cls == 0xCEA /* moby class 3306 */) {
        dobbo_set_mode_flags(target, 0, activeMode, modelMode);
        return;
    }
    if (cls == 0xDE0 /* moby class 3552 */) {
        *(u8 *)(target + 0x95) = *(u8 *)(controller + 0x95);
        return;
    }
    dobbo_set_mode_flags(target, enable, activeMode, modelMode);
}

/* Hands the record's colour key to every entry the index names, negating the
   three offsets when the caller asks for it. */
void dobbo_apply_setting_by_index(char *controller, s32 index, char *settings, s32 enable) {
    char *vars = settings;
    char *target = D_L09_001B285C + (index << 8);

    if (target == 0) {
        return;
    }
    if (enable != 0) {
        dobbo_apply_setting_linked(controller, target, *(s8 *)(vars + 0xBC), *(s8 *)(vars + 0xBD),
                          *(s8 *)(vars + 0xBF));
    } else {
        dobbo_apply_setting_linked(controller, target, -*(s8 *)(vars + 0xBC), -*(s8 *)(vars + 0xBD),
                          -*(s8 *)(vars + 0xBF));
    }
}

/* Sends the on/off setting to every moby in the given group. */
void dobbo_apply_setting_group(char *controller, char *settings, s32 group, s32 enable) {
    s16 *list;
    list = (s16 *)D_L09_001FFFB560[group];
    if (list == 0) {
        return;
    }
    do {
        dobbo_apply_setting_by_index(controller, *(u16 *)list & 0x7FFF, settings, enable);
    } while (*(s16 *)list++ >= 0);
}

/* func_L09_004082D0 is in L09_004082D0.c. */

/* func_L09_00408478 reads D_001A7AF8[k] and stores D_L09_001B25A0[2] as elements of sda arrays:
 * (mem (const (plus sym k))) is a two-word move, so these stay out of delay slots. */
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 D_001395D7[];
extern u8 D_001395D8[];
typedef struct { char pad[0x5c]; int state; int flags; } DobboPlayerFlags;
extern DobboPlayerFlags D_00139768;
extern char g_hero_position[];
extern u8 D_0019B2E8[];
extern int D_00138324;
extern char D_L09_001B1458[], D_L09_001B1480[], D_L09_001B1498[], D_L09_001B14C0[], D_L09_001B14E8[], D_L09_001B14F8[], D_L09_001B1518[], D_L09_001B1540[];
extern char D_L09_001BFC00[], D_L09_0021DDE0[];
extern int g_player_bolts SDATA(D_001A79F8);
extern int g_current_map_index SDATA(D_001A79F0);
extern char *D_L09_001B294C SDATA(D_L09_001B294C);
extern int D_L09_001A8F00[] __attribute__((sda));
extern int D_L09_001B25A0[] __attribute__((sda));
extern int D_L09_0028E350[];
extern int D_L09_0028E360, D_L09_0028E364;
extern void STUB_printf(char *, ...);
extern void moby_set_state(char *, int, int);
extern void moby_reset_vars_defaults(char *);
extern int IsPointInCuboid(char *, int);
extern int req_push_queue(char *, int);
extern void level_apply_index_for_key(char *);
extern void req_launch_queued(char *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(char *, char *, int, int);
extern int flag_is_third_pending_set(char *);
extern void game_set_slowdown_factor(void);
extern int hero_is_reachable_for_count(char *, int, float);
extern void text_print_localized_formatted(int, int, int);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed(int);
extern void record_add_or_update_entry(char *, int, char *, int, char *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(char *, char *);
extern void MemcardSave(int, int);
/* Per-frame update of the bolt-trading character (moby class 3600): it talks to the hero, offers a deal for bolts, and takes the payment when he accepts. */
void UpdateDobboPaidOfferNpc(u8 *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *entry;
    int startCurrency;
    int offerCurrency;
    int currency;
    int balance;
    int remaining;

    switch (obj[0x20]) {
    case 0:
        if (g_item_owned_flags[0xDA]) {
            moby_set_state(obj, 9, -1);
            break;
        }
        if (D_00139768.flags & 1) {
            STUB_printf(D_L09_001B1458);
            startCurrency = g_player_bolts;
            if (g_item_owned_flags[0x197]) {
                if (startCurrency < D_L09_0028E364)
                    goto start_six;
                else
                    moby_set_state(obj, 7, 1);
            } else {
                if (startCurrency < D_L09_0028E360) {
                start_six:
                    moby_set_state(obj, 6, 1);
                } else
                    moby_set_state(obj, 7, 1);
            }
        } else if (D_00139768.state < 0) {
            STUB_printf(D_L09_001B1480);
            if (D_001395D7[0]) {
                obj[0x30] = 0xff;
                STUB_printf(D_L09_001B1498);
                moby_set_state(obj, 4, 1);
            } else {
                obj[0x30] = 0xff;
                STUB_printf(D_L09_001B14C0);
                moby_set_state(obj, 3, 0);
            }
        } else {
            STUB_printf(D_L09_001B14E8);
            moby_set_state(obj, 1, 0);
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)vars)) {
            STUB_printf(D_L09_001B14F8);
            if (req_push_queue(D_L09_001BFC00, 0x5f)) {
                level_apply_index_for_key(obj);
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(vars + 8) != -1) {
            entry = D_L09_001B294C;
            entry += *(int *)(vars + 8) << 7;
            hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        moby_set_state(obj, 3, -1);
        break;
    case 3:
        obj[0x30] = 0xff;
        if (flag_is_third_pending_set(obj)) {
            D_001395D7[0] = 1;
            moby_set_state(obj, 4, 1);
        }
        break;
    case 4:
        obj[0x30] = 0xff;
        if (IsPointInCuboid(g_hero_position, *(int *)vars)) {
            STUB_printf(D_L09_001B1518);
            if (req_push_queue(D_L09_001BFC00, 0x60)) {
                req_launch_queued(D_L09_001BFC00);
                game_set_slowdown_factor();
                moby_set_state(obj, 5, -1);
            }
        }
        break;
    case 5:
        obj[0x30] = 0x40;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        D_L09_001B25A0[2] = 1;
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(vars + 8) != -1) {
            entry = D_L09_001B294C;
            entry += *(int *)(vars + 8) << 7;
            hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        D_001395D8[0] = 1;
        offerCurrency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (offerCurrency < D_L09_0028E364)
                goto offer_six;
            else
                moby_set_state(obj, 7, -1);
        } else {
            if (offerCurrency < D_L09_0028E360) {
            offer_six:
                moby_set_state(obj, 6, -1);
            } else
                moby_set_state(obj, 7, -1);
        }
        break;
    case 6:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (D_L09_0028E350[5] < currency)
                goto change_seven;
        } else {
            if (D_L09_0028E350[4] < currency) {
            change_seven:
                moby_set_state(obj, 7, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x27d1, g_item_owned_flags[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 7:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (currency < D_L09_0028E350[5])
                goto change_six;
        } else {
            if (currency < D_L09_0028E350[4]) {
            change_six:
                moby_set_state(obj, 6, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x27d2, g_item_owned_flags[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            level_apply_index_for_key(obj);
            if ((D_00138324 & 0x10) && req_push_queue(D_L09_001BFC00, 10)) {
                STUB_printf(D_L09_001B1540);
                balance = g_player_bolts;
                if (g_item_owned_flags[0x197])
                    remaining = balance - D_L09_0028E350[5];
                else
                    remaining = balance - D_L09_0028E350[4];
                g_player_bolts = remaining;
                req_push_queue(D_L09_001BFC00, 0x61);
                req_push_queue(D_L09_001BFC00, 0x62);
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 8, -1);
            }
        }
        break;
    case 8:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        moby_mark_flag_and_append_to_list(10);
        snd_play_indexed(10);
        moby_set_state(obj, 9, -1);
        record_add_or_update_entry(obj + 0x20, 1, obj, 1, D_L09_0021DDE0);
        if (obj[0xb0] != 0xff) {
            if (!(D_0019B2E8[obj[0xb0] + (g_current_map_index << 4)] & 0x80))
                moby_mark_table_entry_flagged(obj[0xb0]);
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        } else
            MemcardSave(0, -1);
        break;
    }
}

/* Throws red and white sparks out of the object as it dies. */
void part_spawn_death_sparks(char *obj)
{
    float pos[4];
    float vel[4];
    float initial[4];
    int i;
    *(Quad_Dobbo *)initial = 0;
    initial[2] = -(math_random_float_range(3.5f, 4.5f) * 0.0166666675f);
    *(Quad_Dobbo *)vel = *(Quad_Dobbo *)initial;
    for (i = 0; i < 2; i++) {
        moby_transform_joint_to_world(obj, 2, pos);
        pos[2] += IntToFloat(i) * 0.015f;
        if (i & 1)
            part_spawn_scaling(pos, vel, 0x77FF0000, 0xFF0060, 17, 150, -100, 1);
        else
            part_spawn_scaling(pos, vel, 0x77FF0060, 0xFF0000, 19, 220, -100, 1);
        part_spawn_scaling(pos, vel, 0x77FFFFFF, 0xFF0000, 10, 80, -80, 1);
    }
}

/* func_L09_00409308 is in L09_00409308.c. */

/* func_L09_0040A2E8 is in L09_0040A2E8-g8.c. */

/* Gets a door ready to open: sets its starting slide values and picks which of its two halves moves first. */
void door_init_slide_motion(char *obj) {
    char *self = obj;
    char *rotation = self + 0xC0;
    char *vars = *(char **)(self + 0x68);
    f32 angleA, angleB;
    *(s32 *)(vars + 0x8) = 0;
    *(s32 *)(vars + 0xC) = 0;
    *(f32 *)(vars + 0x0) = 0.2f;
    *(f32 *)(vars + 0x4) = 0.2f;
    func_2EACD0(rotation, self + 0xF0);
    angleA = func_2EA3E0(func_2EA578(rotation, D_L09_001B9C30));
    angleB = func_2EA3E0(func_2EA578(self + 0xD0, D_L09_001B9C30));
    if (angleB < angleA) {
        *(s32 *)(vars + 0x14) = 1;
    } else {
        *(s32 *)(vars + 0x14) = 0;
    }
}

/* Every so often puffs out a burst of particles, using a random timer between bursts. */
void part_update_periodic_emitter(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(int *)vars = func_316A68(0, 0xF0);
        func_316958(obj, 1, -1);
        break;
    case 1:
        if (func_2EA0E0(vars)) {
            if (*(u8 *)(obj + 0x31)) {
                EffectVector a;
                EffectVector b;
                a.bits = 0;
                b.bits = 0;
                a.value[1] = -0.033333335f;
                a.value[2] = 0.016666668f;
                b.value[2] = 2.0f;
                func_2E8450(obj, b.value, a.value, func_316A68(3, 7), 0, 0.0f, 0.033333335f, 0.7f, 15.0f, 1.0f);
            }
            *(int *)vars = func_316A68(0x78, 0xF0);
        }
        break;
    }
}
