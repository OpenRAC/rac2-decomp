#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef short s16;

typedef int s32;

extern char *g_actor_entry_table __attribute__((sda));

extern s32 func_002F3220(char *, float);

extern int D_L02_002A5520[];

extern int D_L02_002A5560[];

extern int math_fast_float_d(void *);

extern void gfx_add_draw_callback_third(char *, char *);

extern void module_l00_call_handler_2(void);

extern char g_stage_draw_callback[];

extern void moby_set_state(char *, s32, s32);

extern int moby_has_free_child_slot_state2(char *);

extern void moby_attach_child_first_free_slot(char *, char *);

extern s32 func_003D77F8(char *);

extern void func_003D78A8(char *);

extern s32 moby_is_state_two_no_children(char *);

extern char *g_moby_l02_pool __attribute__((sda));

extern u32 g_entity_group_lists[];

extern void enemy_release_effect_record(char *);

extern void chainblade_reset_to_idle(char *);

extern void brawler_switch_off_actor(char *);

extern void actor_tear_down(char *);

extern void flamethrower_robot_knock_out(char *);

extern void blade_ball_explode(char *);

extern s32 arena_start_announcer_message(char *, s32);

extern char g_hero_effect_state[];

extern char *g_matrix_l02_record_table __attribute__((sda));

extern void moby_transform_joint_to_world(char *, s32, char *);

extern float vec_distance_xy(char *, char *);

extern char g_hero_position[];

extern int D_L02_002A5600[];

extern char g_music_state[];

extern int D_0017A80;

/* Checks each entity in the object's list and records, as bits in a mask, which ones passed the check. */
void sway_update_piece_mask(char *actor) {
    char *state = *(char **)(actor + 0x68);
    s32 i;
    s16 *idCursor;
    *(u32 *)(state + 0x84) = 0;
    for (i = 0; i < *(s32 *)(state + 0x80); i++) {
        char *entity;
        idCursor = (s16 *)(state + 0x40 + i * 2);
        entity = g_actor_entry_table + *idCursor * 32;
        if (func_002F3220(entity, *(float *)(entity + 0x10)) != -1)
            *(u32 *)(state + 0x84) |= 1 << i;
    }
}

typedef int TI128 __attribute__((mode(TI)));

extern int g_frame_l02_counter __attribute__((sda));
extern float g_sway_angle_range[2] __attribute__((sda));
extern char *g_sway_piece_table __attribute__((sda));
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float ApproachValue(float *, float, float);
extern void euler_rotation_basis(float *, float *);
extern void mat_multiply_rotation(char *, char *, float *);

/* Runs func_L02_003F5430 first when bit 0 of D_L02_001B30C8 is set. The angle at +0x88 is stepped
   (func_002AA2E8, 0.05 degree) towards the target at +0x8C when func_00282948 reports the timer at
   +0x90 idle or just run out, and towards zero while it is still counting down. When the target lies
   between zero and the angle, the timer gets a random 30..90 and the target a random size with the
   opposite sign. The angle is then the third word of a vector func_002833F0 turns into a matrix,
   which multiplies the 64-byte records of D_L02_001B3B00 that the entries of the list at +0x40 name,
   for each bit set in the mask at +0x84. */
/* Makes a group of pieces sway back and forth by a small random angle each time a timer runs out. */
void sway_update_pieces(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float matrix[12];
    float rotation[4];
    float angles[4];
    s32 i;
    s16 *idCursor;

    if (g_frame_l02_counter & 1)
        sway_update_piece_mask(actor);
    if (math_fast_float_d(state + 0x90) != 0) {
        ApproachValue((float *)(state + 0x88), *(float *)(state + 0x8C), 8.726647356525064e-4f);
        if ((*(float *)(state + 0x88) >= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) >= 0.0f) ||
            (*(float *)(state + 0x88) <= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) <= 0.0f)) {
            *(s32 *)(state + 0x90) = math_random_int_range(0x1E, 0x5A);
            if (0.0f < *(float *)(state + 0x8C))
                *(float *)(state + 0x8C) =
                    -(math_random_float_range(g_sway_angle_range[0], g_sway_angle_range[1]) * 2.908882452175021e-4f);
            else
                *(float *)(state + 0x8C) =
                    math_random_float_range(g_sway_angle_range[0], g_sway_angle_range[1]) * 2.908882452175021e-4f;
        }
    } else {
        ApproachValue((float *)(state + 0x88), 0.0f, 8.726647356525064e-4f);
    }
    *(TI128 *)angles = 0;
    angles[2] = *(float *)(state + 0x88);
    *(TI128 *)rotation = *(TI128 *)angles;
    euler_rotation_basis(matrix, rotation);
    for (i = 0; i < *(s32 *)(state + 0x80); i++) {
        char *piece;
        s32 skip;

        idCursor = (s16 *)(state + 0x40 + i * 2);
        skip = ((*(s32 *)(state + 0x84) >> i) & 1) == 0;
        if (skip)
            continue;
        piece = g_sway_piece_table + *idCursor * 64;
        mat_multiply_rotation(piece, piece, matrix);
    }
}

/* func_L02_003F5710 is defined in L02_003F5430-g8.c (three $gp accesses). */

/* Maps the values 0, 1, 3, 5, 6, 7, 8, 10, 11 and 13 to 0..9 (in no regular order) and any other
   value to -1. The dispatch reads the level's own jump table (fourteen words in the level's data
   at 0x2A5520, one per value); `cases` only keeps the labels alive, and each label is named after
   the value that reaches it. */
s32 arena_get_challenge_progress_index(u32 challenge) {
    static void *cases[14] = {&&c0, &&c1, &&dflt, &&c3, &&dflt, &&c5, &&c6, &&c7, &&c8, &&dflt,
                              &&c10, &&c11, &&dflt, &&c13};
    if (challenge < 14)
        goto *D_L02_002A5520[challenge];
    goto dflt;
c0:
    return 0;
c6:
    return 1;
c3:
    return 2;
c1:
    return 3;
c5:
    return 4;
c7:
    return 5;
c10:
    return 6;
c11:
    return 7;
c8:
    return 8;
c13:
    return 9;
dflt:
    return -1;
}

/* Maps a value below 14 to an id (0x31 to 0x3B and 0x91 to 0x93, in no regular order) and any
   other value to -1. The dispatch reads the level's own jump table (fourteen words in the level's
   data at 0x2A5560, one per value); `cases` only keeps the labels alive, and each label is named
   after the value that reaches it. */
/* Turns a challenge number (0 to 13) into the id of its entry in the save table. */
s32 arena_get_challenge_save_index(s32 challenge) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if ((u32)challenge < 14)
        goto *D_L02_002A5560[challenge];
    goto dflt;
c0:
    return 0x31;
c2:
    return 0x32;
c3:
    return 0x33;
c1:
    return 0x34;
c4:
    return 0x35;
c5:
    return 0x36;
c6:
    return 0x37;
c7:
    return 0x38;
c9:
    return 0x39;
c10:
    return 0x3A;
c11:
    return 0x3B;
c8:
    return 0x91;
c12:
    return 0x92;
c13:
    return 0x93;
dflt:
    return -1;
}

/* Counts the arena controller's timer up by one each frame and runs the usual per-frame upkeep. */
void arena_tick_controller(char *actor) {
    char *actorAlias = actor;
    char *state = *(char **)(actorAlias + 0x68);
    u16 timer = *(u16 *)(actorAlias + 0x96);

    if (timer <= 0xFFFE)
        *(u16 *)(actorAlias + 0x96) = timer + 1;
    math_fast_float_d(state + 0xE4);
    if (*(u8 *)(actorAlias + 0x20) > 1)
        gfx_add_draw_callback_third(g_stage_draw_callback, actorAlias);
    module_l00_call_handler_2();
}

/* Sets the arena controller back to its starting values and puts it in the waiting state. */
void arena_reset_controller(char *actor) {
    char *state = *(char **)(actor + 0x68);
    u32 *cursor;
    s32 i;
    *(s16 *)(state + 0x120) = -1;
    *(s16 *)(state + 0x122) = -1;
    *(u16 *)(state + 0x118) = 0;
    cursor = (u32 *)(state + 0xBC);
    for (i = 5; i >= 0; i--) {
        *cursor = 0;
        cursor--;
    }
    *(u32 *)(state + 0xD8) = 0;
    *(u32 *)(state + 0xD0) = 0;
    moby_set_state(actor, 1, -1);
    *(u32 *)(state + 0xC0) = 0;
}

/* func_L02_003FB000 is defined in L02_003FB000-g8.c. */

/* func_L02_003FB120 is matched in L02_003FB120-g8.c (built with -g). */

extern s32 arena_register_spawned_enemy(char *, char *);

/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; records A0 as that entity's owner and returns func_L02_003FB6C0's result for it.
   The walk is func_L02_003FB5A0's `do { ... } while ((s16)*p++ >= 0);`: a `for (;;)` with the
   test and the increment in the body makes this cc1 annul the loop-bottom slot (`bgezl`). */
s32 arena_claim_enemy(char *actor, s32 classId, char *unused) {
    char *state = *(char **)(actor + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 listAddr;
    u16 *idCursor;
    char *entity;

    if (index == 0xFF)
        return 0;
    listAddr = g_entity_group_lists[index];
    if (listAddr == 0)
        return 0;
    idCursor = (u16 *)listAddr;
    do {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity != 0 && *(u8 *)(entity + 0x20) != 0xFE && *(u8 *)(entity + 0x20) != 0xFD
            && *(s16 *)(entity + 0xAA) == classId && *(u8 *)(entity + 0x20) == 1) {
            *(char **)(entity + 0xB8) = actor;
            return arena_register_spawned_enemy(actor, entity);
        }
    } while ((s16)*idCursor++ >= 0);
    return 0;
}

extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void chainblade_reset_to_start(char *, s32);
extern void ReinitializeActorAndChild(char *, s32);

/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; for the kinds 0x9F8 and 0xA44 it records A0 as that entity's owner, runs the kind's start
   function, counts it in the state and returns it. */
char *arena_claim_boss(char *actor, s32 classId, s32 variant) {
    char *state = *(char **)(actor + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 listAddr;
    u16 *idCursor;
    char *entity;

    if (index == 0xFF)
        return 0;
    listAddr = g_entity_group_lists[index];
    if (listAddr == 0)
        return 0;
    idCursor = (u16 *)listAddr;
    do {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity != 0 && *(u8 *)(entity + 0x20) != 0xFE && *(u8 *)(entity + 0x20) != 0xFD
            && *(s16 *)(entity + 0xAA) == classId && *(u8 *)(entity + 0x20) == 1) {
            *(char **)(entity + 0xB8) = actor;
            switch (classId) {
            case MOBY_CLASS_CHAINBLADE:
                chainblade_reset_to_start(entity, *(s16 *)(state + 0x120) == 0xC);
                *(s32 *)(state + 0xA0) += 1;
                return entity;
            case MOBY_CLASS_B2_BRAWLER_LEGS:
                ReinitializeActorAndChild(entity, variant);
                *(s32 *)(state + 0xA4) += 1;
                return entity;
            }
        }
    } while ((s16)*idCursor++ >= 0);
    return 0;
}

/* Counts the kind of A1 in the state and sets its scale to one. */
s32 arena_register_spawned_enemy(char *actor, char *enemy) {
    char *state = *(char **)(actor + 0x68);
    char **slotList = (char **)(state + 0xA8);
    char **slotPtr = slotList + *(s32 *)(state + 0xD8);
    char *slotEntry = *slotPtr;

    if (slotEntry != 0) {
        if (moby_has_free_child_slot_state2(slotEntry) != 0) {
            char **curSlot = slotList + *(s32 *)(state + 0xD8);

            moby_attach_child_first_free_slot(*curSlot, enemy);
            switch (*(s16 *)(enemy + 0xAA)) {
            case 0x9CA /* moby class 2506 */:
                *(s32 *)(state + 0x90) += 1;
                *(float *)(*(char **)(enemy + 0x68) + 0x20) = 1.0f;
                break;
            case 0xB22 /* moby class 2850 */:
                *(s32 *)(state + 0x94) += 1;
                *(float *)(*(char **)(enemy + 0x68) + 0x20) = 1.0f;
                break;
            case MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER:
                *(s32 *)(state + 0x98) += 1;
                *(float *)(*(char **)(enemy + 0x68) + 0x20) = 1.0f;
                break;
            case MOBY_CLASS_PX6_BLADEBALL:
                *(s32 *)(state + 0x9C) += 1;
                *(float *)(*(char **)(enemy + 0x68) + 0x20) = 1.0f;
                break;
            default:
                return 1;
            }
            return 1;
        }
    }
    return 0;
}

/* func_L02_003FB7E0 is defined in L02_003F5430-g8.c ($gp accesses). */

/* Goes through the arena's spawn slots and starts every enemy that is ready. */
void arena_activate_spawn_slots(char *actor) {
    char **slotPtr;
    char *state = *(char **)(actor + 0x68);
    s32 i;
    for (i = 0; i <= *(s32 *)(state + 0xD8); i++) {
        slotPtr = (char **)(state + 0xA8 + i * 4);
        if (*slotPtr != 0) {
            if (func_003D77F8(*slotPtr) != 0)
                func_003D78A8(*slotPtr);
        }
    }
}

/* True when every occupied slot of the list at +0xA8 has content; then the list is cleared. */
void arena_clear_spawn_slots(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char **slotPtr = (char **)(state + 0xA8);
    s32 i;
    s32 j;
    s32 ok = 1;

    for (i = 0; i <= *(s32 *)(state + 0xD8); i++) {
        if (*slotPtr != 0) {
            if (moby_is_state_two_no_children(*slotPtr) == 0) {
                ok = 0;
                break;
            }
        }
        slotPtr++;
    }
    if (ok) {
        for (j = 0; j <= *(s32 *)(state + 0xD8); j++)
            *(s32 *)(state + 0xA8 + j * 4) = 0;
        *(s32 *)(state + 0xD8) = 0;
    }
}

extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void enemy_release_effect_record(char *);
extern void chainblade_reset_to_idle(char *);
extern void brawler_switch_off_actor(char *);
extern void actor_tear_down(char *);
extern void flamethrower_robot_knock_out(char *);
extern void blade_ball_explode(char *);

/* Walks the 16-bit stream the object's table entry points at and calls the handler of the
   entity type each word names; a negative word ends the stream. */
void arena_reset_group_enemies(char *actor) {
    char *state = *(char **)(actor + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 listAddr;
    short *idCursor;
    char *entity;
    s16 classId;

    if (index == 0xFF)
        return;
    listAddr = g_entity_group_lists[index];
    if (listAddr == 0)
        return;
    idCursor = (short *)listAddr;
    do {
        entity = g_moby_l02_pool + ((*(u16 *)idCursor & 0x7FFF) << 8);
        classId = *(s16 *)(entity + 0xAA);
        switch (classId) {
        case 0x9CA /* moby class 2506 */:
            enemy_release_effect_record(entity);
            break;
        case 0xB22 /* moby class 2850 */:
            actor_tear_down(entity);
            break;
        case MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER:
            flamethrower_robot_knock_out(entity);
            break;
        case MOBY_CLASS_PX6_BLADEBALL:
            blade_ball_explode(entity);
            break;
        case MOBY_CLASS_CHAINBLADE:
            chainblade_reset_to_idle(entity);
            break;
        case MOBY_CLASS_B2_BRAWLER_LEGS:
            brawler_switch_off_actor(entity);
            break;
        }
    } while (*idCursor++ >= 0);
}

extern s32 g_group_max_index[] __attribute__((sda));
extern void IncrementMaktarTypeCounter(char *, s32);

/* The test of the entity walks below: the group word at +0x40 is read again for every condition,
   as the handlers may change it. */
#define GROUP_LEFT(p) \
    ((*(s32 *)(state + 0x40) & 0xFF) != 0xFF && *(s32 *)(state + 0x40) <= D_L02_001B35B8[0] && \
     p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[*(s32 *)(state + 0x40)]))

/* Clears the flag (+0x2F6 of a 0x9CA entity's block, +0x4EA of a 0xB22 one) of every entity of
   the group that has it set and passes the entity's kind to func_L02_003FC1B0; then, twice, picks
   among the group's entities of those two kinds that are not 0xFE/0xFD, have a state byte (+0x20)
   of 4 or more and the flag not set, the one nearest to D_00189EA0, sets its flag and takes one
   off its kind's count (+0x50, +0x54). */
void arena_pick_nearest_attackers(char *actor) {
    char *state = *(char **)(actor + 0x68);
    u16 *idCursor;
    char *entity;
    char *best;
    float bestDistance;
    float distance;
    s32 i;
    u16 kind;
    s16 flag;

    for (idCursor = (u16 *)g_entity_group_lists[*(s32 *)(state + 0x40)]; GROUP_LEFT(idCursor); idCursor++) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        switch (*(s16 *)(entity + 0xAA)) {
        case 0x9CA /* moby class 2506 */: {
            char *q = *(char **)(entity + 0x68);

            if (*(s16 *)(q + 0x2F6) == 1) {
                *(s16 *)(q + 0x2F6) = 0;
                IncrementMaktarTypeCounter(actor, *(s16 *)(entity + 0xAA));
            }
            break;
        }
        case 0xB22 /* moby class 2850 */: {
            char *q = *(char **)(entity + 0x68);

            if (*(s16 *)(q + 0x4EA) == 1) {
                *(s16 *)(q + 0x4EA) = 0;
                IncrementMaktarTypeCounter(actor, *(s16 *)(entity + 0xAA));
            }
            break;
        }
        }
    }
    for (i = 0; i < 2; i++) {
        best = 0;
        bestDistance = 10000.0f;
        for (idCursor = (u16 *)g_entity_group_lists[*(s32 *)(state + 0x40)]; GROUP_LEFT(idCursor); idCursor++) {
            entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
            if (entity == 0)
                break;
            flag = -1;
            kind = *(u16 *)(entity + 0xAA);
            switch (*(s16 *)(entity + 0xAA)) {
            case 0x9CA /* moby class 2506 */:
                flag = *(s16 *)(*(char **)(entity + 0x68) + 0x2F6);
                break;
            case 0xB22 /* moby class 2850 */:
                flag = *(s16 *)(*(char **)(entity + 0x68) + 0x4EA);
                break;
            }
            if (entity != 0 && *(u8 *)(entity + 0x20) != 0xFE && *(u8 *)(entity + 0x20) != 0xFD &&
                ((s16)kind == 0x9CA /* moby class 2506 */ || (s16)kind == 0xB22 /* moby class 2850 */) && flag != 1 &&
                *(u8 *)(entity + 0x20) >= 4) {
                if (best == 0) {
                    best = entity;
                    bestDistance = vec_distance_xy(best + 0x10, g_hero_position);
                } else {
                    distance = vec_distance_xy(entity + 0x10, g_hero_position);
                    if (distance < bestDistance) {
                        best = entity;
                        bestDistance = distance;
                    }
                }
            }
        }
        if (best != 0) {
            switch (*(s16 *)(best + 0xAA)) {
            case 0x9CA /* moby class 2506 */:
                *(s16 *)(*(char **)(best + 0x68) + 0x2F6) = 1;
                *(s32 *)(state + 0x50) -= 1;
                break;
            case 0xB22 /* moby class 2850 */:
                *(s16 *)(*(char **)(best + 0x68) + 0x4EA) = 1;
                *(s32 *)(state + 0x54) -= 1;
                break;
            }
        }
    }
}

/* Makes the given boss the arena's current boss and plays its announcer line. */
void arena_set_current_boss(char *actor, char *boss) {
    char *state = *(char **)(actor + 0x68);
    char *shared = g_hero_effect_state;
    s16 classId;
    if (*(u32 *)(shared + 0x284) == *(u32 *)(state + 0xD0))
        *(u32 *)(shared + 0x284) = 0;
    if (*(u32 *)(shared + 0x284) == 0) {
        *(u32 *)(shared + 0x284) = (u32)boss;
        *(u32 *)(shared + 0x288) = 0;
    }
    *(u32 *)(state + 0xD0) = (u32)boss;
    classId = *(s16 *)(boss + 0xAA);
    if (classId == MOBY_CLASS_CHAINBLADE)
        arena_start_announcer_message(actor, 0xF);
    else if (classId == MOBY_CLASS_B2_BRAWLER_LEGS)
        arena_start_announcer_message(actor, 0x15);
}

/* Returns the position of the arena's current camera point. */
char *arena_get_camera_point(char *actor) {
    char *state = *(char **)(actor + 0x68);
    return g_matrix_l02_record_table + *(u32 *)(state + 0x88) * 128 + 0x30;
}

/* Returns one stored number from the arena controller's data. */
s32 arena_get_state_word(char *actor) {
    char *state = *(char **)(actor + 0x68);
    return *(s32 *)(state + 0x84);
}

/* Counts down one of the four timers named by a1; true when it was still running. */
/* Uses up one of the stored enemy counts for this enemy type. Returns 1 if there was one left. */
s32 arena_take_enemy_quota(char *actor, s32 classId) {
    char *state = *(char **)(actor + 0x68);

    switch (classId) {
    case 0x9CA /* moby class 2506 */:
        if (*(s32 *)(state + 0x50) > 0) {
            *(s32 *)(state + 0x50) -= 1;
            return 1;
        }
        break;
    case 0xB22 /* moby class 2850 */:
        if (*(s32 *)(state + 0x54) > 0) {
            *(s32 *)(state + 0x54) -= 1;
            return 1;
        }
        break;
    case MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER:
        if (*(s32 *)(state + 0x58) > 0) {
            *(s32 *)(state + 0x58) -= 1;
            return 1;
        }
        break;
    case MOBY_CLASS_PX6_BLADEBALL:
        if (*(s32 *)(state + 0x5C) > 0) {
            *(s32 *)(state + 0x5C) -= 1;
            return 1;
        }
        break;
    case MOBY_CLASS_CHAINBLADE:
    case MOBY_CLASS_B2_BRAWLER_LEGS:
        return 0;
    default:
        break;
    }
    return 0;
}

/* Adds one back to the stored enemy count for this enemy type. */
void IncrementMaktarTypeCounter(char *actor, s32 classId) {
    s32 *counts = *(s32 **)(actor + 0x68);
    s32 result = MOBY_CLASS_B2_BRAWLER_LEGS;
    if (classId == result)
        goto low_return;
    if (classId >= 0xA45)
        goto high;
    result = 0x9CA /* moby class 2506 */;
    if (classId == result)
        goto inc50;
low_return:
    return;
high:
    result = MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER;
    if (classId == result)
        goto inc58;
    if (classId >= 0xC3C)
        goto highest;
    result = 0xB22 /* moby class 2850 */;
    if (classId == result)
        goto inc54;
    return;
highest:
    result = MOBY_CLASS_PX6_BLADEBALL;
    if (classId == result)
        goto inc5c;
    return;
inc50:
    ++counts[0x14];
    return;
inc54:
    ++counts[0x15];
    return;
inc58:
    ++counts[0x16];
    return;
inc5c:
    ++counts[0x17];
    return;
}

extern char *g_moby_l02_pool __attribute__((section(".sdata")));
extern s32 g_group_max_index[] __attribute__((sda));
extern s16 moby_get_vars_counter(char *);
extern void moby_set_vars_counter_to_1(char *);
extern void moby_clear_vars_counter(char *);

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L02_001FC060[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)

/* Counts the entities of the object's group (state word 0x48) for which func_L02_004024A0 holds, then
   sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count equals A1. */
void arena_match_active_count_a(char *actor, s32 wantedCount) {
    char *state = *(char **)(actor + 0x68);
    u16 *idCursor;
    char *entity;
    s32 count = 0;

    FOR_EACH_ID(idCursor, 0x48) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (moby_get_vars_counter(entity))
            count++;
    }
    if (count < wantedCount) {
        FOR_EACH_ID(idCursor, 0x48) {
            entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (!moby_get_vars_counter(entity)) {
                moby_set_vars_counter_to_1(entity);
                count++;
                if (count >= wantedCount)
                    break;
            }
        }
    } else if (count > wantedCount) {
        FOR_EACH_ID(idCursor, 0x48) {
            entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (moby_get_vars_counter(entity)) {
                moby_clear_vars_counter(entity);
                count--;
                if (count <= wantedCount)
                    break;
            }
        }
    }
}

extern s32 moby_get_busy_flag(char *);
extern void moby_set_busy_flag(char *);
extern void moby_clear_busy_flag(char *);

/* Counts the entities of the object's group (state word 0x4C) for which func_L02_003D7300 holds, then
   sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count equals A1. */
void arena_match_active_count_b(char *actor, s32 wantedCount) {
    char *state = *(char **)(actor + 0x68);
    u16 *idCursor;
    char *entity;
    s32 count = 0;

    FOR_EACH_ID(idCursor, 0x4C) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (moby_get_busy_flag(entity))
            count++;
    }
    if (count < wantedCount) {
        FOR_EACH_ID(idCursor, 0x4C) {
            entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (!moby_get_busy_flag(entity)) {
                moby_set_busy_flag(entity);
                count++;
                if (count >= wantedCount)
                    break;
            }
        }
    } else if (count > wantedCount) {
        FOR_EACH_ID(idCursor, 0x4C) {
            entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (moby_get_busy_flag(entity)) {
                moby_clear_busy_flag(entity);
                count--;
                if (count <= wantedCount)
                    break;
            }
        }
    }
}

extern void armed_enemy_drop_held_and_reset(char *, int, int);
extern void moby_set_anim_type_three(char *, int, int);
extern int coll_point_inside_record_volume(void *, int);
extern void hero_record_play_counters(void);

/* Walks the entities of the group the object names (the group word is re-read for every
   test: the handlers may change it).  Each live, unflagged one that passes the screen
   against the two bounds is handed to the handler of its type.  Afterwards the follow-up is
   called unless the resident record passes the screen. */
/* Updates each enemy of the arena group that is near enough to the hero. */
void arena_update_group_enemies(char *actor) {
    char *state = *(char **)(actor + 0x68);
    u16 *idCursor;
    char *entity;
    u8 entityState;

    FOR_EACH_ID(idCursor, 0x40) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        entityState = *(u8 *)(entity + 0x20);
        if (entityState == 0xFE)
            continue;
        if (entityState == 0xFD)
            continue;
        if (entityState < 3)
            continue;
        if (*(u16 *)(entity + 0x34) & 2)
            continue;
        if (coll_point_inside_record_volume(entity + 0x10, *(s32 *)(state + 0x80)) == 0 &&
            coll_point_inside_record_volume(entity + 0x10, *(s32 *)(state + 0x7C)) != 0)
            continue;
        switch (*(s16 *)(entity + 0xAA)) {
        case 0x9CA /* moby class 2506 */:
            armed_enemy_drop_held_and_reset(entity, 0, 0);
            break;
        case 0xB22 /* moby class 2850 */:
            moby_set_anim_type_three(entity, 0, -1);
            actor_tear_down(entity);
            break;
        case MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER:
            moby_set_anim_type_three(entity, 0, -1);
            flamethrower_robot_knock_out(entity);
            break;
        case MOBY_CLASS_PX6_BLADEBALL:
            moby_set_anim_type_three(entity, 0, -1);
            blade_ball_explode(entity);
            break;
        }
    }
    if (coll_point_inside_record_volume(g_hero_position, *(s32 *)(state + 0x7C)) == 0)
        hero_record_play_counters();
}

/* func_L02_003FC9C0 is matched in L02_003F5430-g8.c. */

extern int math_random_int_below(int);
extern void cam_end_override(char *);
extern void load_scene_chunk(int, int);
extern void vec_clear_128(void *);
extern int arena_get_challenge_save_index(int);
extern void hero_reset_position_and_direction(char *, float *, int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void script_queue_keyed_request(int, int);
extern int g_arena_l02_active_flag;
extern u8 g_game_flag_table[];
extern char *g_hero_position_records __attribute__((sda));
extern int g_arena_challenge_index __attribute__((sda));

/* Starts the actor: calls func_L02_00400650 with 0x25 plus a random pick below 2, sets state 1,
   releases the object held at +0xC0 and, by a per-slot flag, hands a vector whose third float
   is -1.59 or 2.16, with the matching 128-byte record, to func_L00_002B9D60; ends by setting
   D_L02_001AA1B0 to -1. */
/* Cancels the challenge menu: puts the hero back at the arena entrance and returns to the waiting state. */
void arena_cancel_challenge_menu(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float heroPos[4];

    arena_start_announcer_message(actor, math_random_int_below(2) + 0x25);
    moby_set_state(actor, 1, -1);
    if (*(char **)(state + 0xC0) != 0) {
        cam_end_override(*(char **)(state + 0xC0));
        *(s32 *)(state + 0xC0) = 0;
    }
    if (g_arena_l02_active_flag != 0)
        load_scene_chunk(0, *(s32 *)(state + 0x224));
    vec_clear_128(heroPos);
    if (g_game_flag_table[arena_get_challenge_save_index(0)] != 0) {
        heroPos[2] = -1.59f;
        hero_reset_position_and_direction(g_hero_position_records + *(s32 *)(state + 0x74) * 128 + 0x30, heroPos, 0, 1);
    } else {
        heroPos[2] = 2.16f;
        hero_reset_position_and_direction(g_matrix_l02_record_table + *(s32 *)(state + 0x78) * 128 + 0x30, heroPos, 0, 1);
    }
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    arena_reset_group_enemies(actor);
    arena_match_active_count_a(actor, 0);
    arena_match_active_count_b(actor, 0);
    script_queue_keyed_request(*(s32 *)(state + 0x224), *(s32 *)(state + 0x22C));
    g_arena_challenge_index = -1;
}

/* func_L02_003FCBF0 is defined in L02_003F5430-g8.c (this unit has no $gp access for it). */

/* func_L02_003FCCA0 is defined in L02_003F5430-g8.c (D_001A79F8 is a $gp access in a delay slot). */

/* Returns 1 when the entity's marker is on and it is more than 25 units away from the hero. */
s32 arena_is_entity_far_from_hero(char *entity) {
    char pos[16];
    s32 result = 0;
    moby_transform_joint_to_world(entity, 0, pos);
    if (*(u8 *)(entity + 0x31) != 0) {
        if (vec_distance_xy(pos, g_hero_position) > 25.0f)
            result = 1;
    }
    return result;
}

extern void moby_finish_release_child(char *);

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0xC8 and
   0xC4); an empty group, or a group word of 0xFF, ends the function. */
/* Runs the setup function on every entity of the arena's two scenery groups. */
void arena_run_scenery_setup(char *actor) {
    char *state = *(char **)(actor + 0x68);
    u16 *idCursor;
    u16 *listStart;
    char *entity;

    if (GROUP(0xC8) == 0xFF)
        return;
    listStart = (u16 *)g_entity_group_lists[GROUP(0xC8)];
    if (listStart == 0)
        return;
    for (idCursor = listStart; (GROUP(0xC8) & 0xFF) != 0xFF && GROUP(0xC8) <= g_group_max_index[0] && idCursor != 0 &&
                ((idCursor != 0 && (s16)idCursor[-1] >= 0) || idCursor == (u16 *)g_entity_group_lists[GROUP(0xC8)]);
         idCursor++) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        moby_finish_release_child(entity);
    }
    if (GROUP(0xC4) == 0xFF)
        return;
    listStart = (u16 *)g_entity_group_lists[GROUP(0xC4)];
    if (listStart == 0)
        return;
    for (idCursor = listStart; (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= g_group_max_index[0] && idCursor != 0 &&
                ((idCursor != 0 && (s16)idCursor[-1] >= 0) || idCursor == (u16 *)g_entity_group_lists[GROUP(0xC4)]);
         idCursor++) {
        entity = g_moby_l02_pool + ((*idCursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        moby_finish_release_child(entity);
    }
}

/* func_L02_003FD228 is defined in L02_003F5430-g8.c (it reads its globals through $gp). */

/* func_L02_003FD7C8 is defined in L02_003F5430-g8.c ($gp accesses). */


/* func_L02_003FDDE8 is in L02_003FDDE8-g8.c. */

/* Maps a value below 14 to an id (0x2F48 to 0x2F51, 0x2F6E and 0x3240 to 0x3242, in no regular
   order); any other value gives 0x2F48. The dispatch reads the level's own jump table (fourteen
   words in the level's data at 0x2A5600, one per value); `cases` only keeps the labels alive, and
   each label is named after the value that reaches it. */
/* Returns the text id for a challenge's name. */
s32 arena_get_challenge_name_text(u32 challenge) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if (challenge < 14)
        goto *D_L02_002A5600[challenge];
    goto dflt;
c0:
    return 0x2F48;
c2:
    return 0x2F49;
c4:
    return 0x2F4A;
c9:
    return 0x2F4B;
c6:
    return 0x2F4C;
c3:
    return 0x2F4D;
c1:
    return 0x2F4E;
c5:
    return 0x2F4F;
c7:
    return 0x2F6E;
c10:
    return 0x2F50;
c11:
    return 0x2F51;
c8:
    return 0x3240;
c12:
    return 0x3241;
c13:
    return 0x3242;
dflt:
    return 0x2F48;
}

/* func_L02_003FE250 is in L02_003FE250-g8.c. */

/* func_L02_003FE8B8 is in L02_003FE8B8-g8.c. */


/* func_L02_003FF9A0 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_003FFDB0 is defined in L02_003FFDB0-g8.c ($gp accesses). */

/* func_L02_004002E0 is matched in L02_004002E0-g8.c (built with -g). */

/* func_L02_004004D0 is matched in its own unit, src/levels/shared/L02_004004D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Timer for one of the thirty-nine messages, refused while one is running. */
s32 arena_start_announcer_message(char *actor, s32 messageId) {
    char *state = *(char **)(actor + 0x68);
    s32 messageTime;

    if ((u32)messageId >= 0x27)
        return 0;
    if (messageId < 0x14) {
        s32 index = messageId;
        char *table = state + 0x130;
        messageTime = *(s32 *)(table + index * 4);
    } else {
        s32 index = messageId - 0x14;
        char *table = state + 0x180;
        messageTime = *(s32 *)(table + index * 4);
    }
    {
        char *hudState = g_music_state;

        if (*(s32 *)(hudState + 0x68) != 0)
            goto fail;
        if (*(s32 *)(hudState + 0x24) != -1)
            goto fail;
        *(s32 *)(hudState + 0x28) = 0;
        *(s32 *)(hudState + 0x24) = (messageTime & 0x3FFF) + 0x7D0;
    }
    {
        char *table = state + 0x1D0;
        *(u16 *)(table + messageId * 2) = 1;
    }
    return 1;
fail:
    return 0;
}

/* func_L02_00400720 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_00400948 is defined in L02_003F5430-g8.c ($gp accesses). */

extern char *g_moby_l02_list_head __attribute__((sda));
extern void explosion_effect_update(char *);
extern void moby_explode_and_hurt_nearby(char *);
extern void moby_copy_sub_byte_40_to_25(char *);
extern void moby_copy_vars_byte_40_to_25(char *);
extern void moby_raise_state_to_eight(char *);
extern void moby_raise_state_to_eight_copy(char *);
extern void moby_release_slots_retire(char *);
extern void moby_call_helper_10000(char *);
extern void moby_mark_spawned(char *);

/* Walks the list of objects at D_L02_001B35A8 (linked through +0x28) and hands each one to the
   handler of its kind, the half-word at +0xAA. */
/* Gives each object in the world a start-of-challenge call, depending on what kind of object it is. */
void arena_notify_mobys_challenge_start(void) {
    char *moby;

    for (moby = g_moby_l02_list_head; moby != 0; moby = *(char **)(moby + 0x28)) {
        switch (*(s16 *)(moby + 0xAA)) {
        case MOBY_CLASS_SHEEP:
            explosion_effect_update(moby);
            break;
        case MOBY_CLASS_DARK_SHEEP:
            moby_explode_and_hurt_nearby(moby);
            break;
        case MOBY_CLASS_SYNTHENOID:
            moby_copy_sub_byte_40_to_25(moby);
            break;
        case MOBY_CLASS_KILONOID:
            moby_copy_vars_byte_40_to_25(moby);
            break;
        case MOBY_CLASS_MINITURRET:
            moby_raise_state_to_eight(moby);
            break;
        case MOBY_CLASS_MEGATURRET:
            moby_raise_state_to_eight_copy(moby);
            break;
        case 0x326 /* moby class 806 */:
            moby_release_slots_retire(moby);
            break;
        case MOBY_CLASS_SHIELD_CHARGER:
        case MOBY_CLASS_TESLA_BARRIER:
            moby_call_helper_10000(moby);
            break;
        case 0xAE0:
        case 0xAE1:
        case 0xAE2:
        case 0xAEC:
        case 0xB06:
        case 0xB09:
        case 0xCC0:
        case 0xCC1:
        case 0xCC2:
        case 0xCC3:
        case 0xCC4:
        case 0xCC5:
        case 0xCC6:
        case 0xCC7:
        case 0xCC8:
        case 0xCC9:
        case MOBY_CLASS_AMMO:
            moby_mark_spawned(moby);
            break;
        }
    }
}

/* True when the field at +0xAA is 0xB59, the global at D_0017A80 is 1 and bit 3 of the
   byte at +0x20 is clear. */
/* Returns 1 when this object is the arena controller and it is running a challenge (state 8). */
s32 arena_is_challenge_running(char *moby) {
    s32 result = 0;
    if (*(s16 *)(moby + 0xAA) == 0xB59 /* moby class 2905 */ && D_0017A80 == 1)
        result = (*(u8 *)(moby + 0x20) ^ 8) ? 0 : D_0017A80;
    return result;
}



/* func_L02_00401BF8 is matched in L02_00401BF8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_00401D38 is defined in L02_003F5430-g8.c ($gp accesses). */

