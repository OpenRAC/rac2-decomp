#include "include_asm.h"
#include "common.h"







/* Dispatches an indexed polygon query through the already integrated helper. */
typedef struct { s32 field00; u8 remainder[12]; } JobaPolygonHeaderView;

extern JobaPolygonHeaderView *D_L11_001FF580[];

extern s32 point_in_path_xy(f32 *point, f32 *vertices, s32 count);

/* Consumes one positive counter selected by the measured class identifier. */
typedef struct {
    u8 prefix[0xe0];
    s32 fielde0, fielde4, fielde8, fieldec, fieldf0, fieldf4;
} JobaClassCounterView;


/* bumps the 0xFFFF-saturated counter, then starts the state's timer and reports the object */
extern u8 D_L11_004465F8[];
extern void func_300150(void *);
extern void func_2F8AD0(void *, void *);
extern void func_31F338(void);

/* Counts one more frame for the arena and starts its timer. */
void arena_end_frame(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    u16 *counter = (u16 *)(obj + 0x96);
    if (*counter <= 0xFFFE) {
        *counter = *counter + 1;
    }
    func_300150(state + 0x190);
    func_2F8AD0(D_L11_004465F8, obj);
    func_31F338();
}

/* clears the state's six-word block and its counters, then restarts the object */
extern void func_32C9E0();

/* Clears the arena's counters and slots so a new challenge can start. */
void arena_reset_state(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    s32 *word_ptr = (s32 *)(state + 0x134);
    *(s16 *)(state + 0x1F0) = -1;
    *(s16 *)(state + 0x1E8) = 0;
    *(s16 *)(state + 0x1F2) = -1;
    for (i = 5; i >= 0; i--) {
        *word_ptr = 0;
        word_ptr--;
    }
    *(s32 *)(state + 0x18C) = 0;
    *(s32 *)(state + 0x180) = 0;
    func_32C9E0(obj, 1, -1);
    *(float *)(state + 0x1BC) = 1.0f;
    *(s32 *)(state + 0x170) = 0;
}

/* func_L11_00440238 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */
/* func_L11_00440360 is in L11_0043E1A0-g.c. */

/* func_L11_00440790 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */

/* Finds the class entry the identifier names and hands it to that class's handler. */
extern u8 *g_group_id_lists[];

extern u8 *g_moby_l11_table __attribute__((section(".sdata")));

extern void joba_rail_reset(u8 *);

extern void rotor_reset_group(u8 *);

/* Wakes up the boss of the asked kind and counts it. */
u8 *arena_activate_boss_of_class(u8 *obj, s32 id) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s32 *)(state + 0xC0);
    u16 *cursor;
    u8 *record;
    u8 *list;

    if (index == 0xFF) {
        return 0;
    }
    list = g_group_id_lists[index];
    if (list == 0) {
        return 0;
    }
    cursor = (u16 *)list;
    do {
        u16 value = *cursor & 0x7FFF;
        record = g_moby_l11_table + (value << 8);

        if (record != 0 && record[0x20] != 0xFE && record[0x20] != 0xFD &&
            *(s16 *)(record + 0xAA) == id && record[0x20] == 1) {
            *(u32 *)(record + 0xB8) = (u32)obj;
            switch (id) {
            case 0xD4A /* moby class 3402 */:
                rotor_reset_group(record);
                *(s32 *)(state + 0x118) += 1;
                return record;
            case MOBY_CLASS_ARACHNOID:
                joba_rail_reset(record);
                *(s32 *)(state + 0x11C) += 1;
                return record;
            }
        }
    } while (*(s16 *)cursor++ >= 0);
    return 0;
}

/* func_L11_00440970 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Hands a target point to the first free class-0xD37 moby (state 1) in this moby's
   group: records the caller as its owner, places it at the target facing -pi/2, sets
   its heading toward the target from the caller and starts it; 0 when the group is
   empty or has no free member. */
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 state;
    u8 pad21[0x89];
    short oclass;
    u8 padAC[0xC];
    void *owner;
    u8 padBC[4];
    float rot[12];
    float fF0;
    float fF4;
    float fF8;
} GroupMoby440B28;
typedef struct {
    u8 pad0[0xC0];
    int group;
} GroupVars440B28;
extern char *D_001B359C __attribute__((sda));
extern unsigned short *D_001FC420[];
extern float mat_fast_helper_a(float, float);
extern void euler_rotation_basis(void *, void *);
extern void enemy_init_state(void *, int, int);

/* Sends the first free fighter of one kind toward a target point. */
int arena_launch_fighter_toward_target(u8 *object, float *target)
{
    GroupMoby440B28 *member;
    unsigned short *list;
    unsigned short *cursor;
    int group;
    float dx;

    group = ((GroupVars440B28 *)*(u8 **)(object + 0x68))->group;
    if (group == 0xFF)
        return 0;
    list = D_001FC420[group];
    if (list == 0)
        return 0;
    cursor = list;
    do {
        member = (GroupMoby440B28 *)(D_001B359C + (*cursor & 0x7FFF) * 0x100);
        if (member != 0 && member->state != 0xFE && member->state != 0xFD &&
            member->oclass == 0xD37 /* moby class 3383 */ && member->state == 1) {
            member->owner = object;
            qcopy(member->pos, target);
            member->fF0 = 0.0f;
            member->fF4 = -1.5707965f;
            dx = target[0] - ((float *)arena_get_center_point(object))[0];
            member->fF8 = mat_fast_helper_a(dx, target[1] - ((float *)arena_get_center_point(object))[1]);
            euler_rotation_basis(member->rot, &member->fF0);
            enemy_init_state(member, 0, 1);
            return 1;
        }
    } while ((short)*cursor++ >= 0);
    return 0;
}

/* Returns the state's 0x200 halfword. */
/* Returns how many fighters of one kind the arena counted. */
s16 arena_get_fighter_count(u8 *obj) {
    return *(s16 *)(*(u8 **)(obj + 0x68) + 0x200);
}

extern s32 moby_has_free_child_slot_state2(u8 *);
extern s32 moby_has_any_child_slot_used(u8 *);
extern void moby_attach_child_first_free_slot(u8 *, u8 *);

/* The weight word (+0x20) of OTHER's state. */
#define WEIGHT (*(f32 *)(*(u8 **)(other + 0x68) + 0x20))

/* Adds OTHER to the group in the state's current slot (+0x120, indexed by +0x18C) when that
   group exists and accepts it: the class of OTHER is counted (0xD98 +0x100, 0xDCF +0x104,
   0xDF4 +0x108, 0xDF7 +0x10C, 0xDF9 +0x110 unless the group refuses it, 0xD37 +0x114) and
   its state's weight set to 1.0. Returns 1 when added, else 0. */
/* Adds a fighter to the current squad and counts it by kind. Returns 1 when it was added. */
s32 arena_add_fighter_to_squad(u8 *obj, u8 *other)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *slots = state + 0x120;

    if (*(u8 **)(slots + (*(s32 *)(state + 0x18C) << 2)) != 0 &&
        moby_has_free_child_slot_state2(*(u8 **)(slots + *(s32 *)(state + 0x18C) * 4)) != 0) {
        switch (*(s16 *)(other + 0xAA)) {
        case 0xD98 /* Joba security robot */:
            *(s32 *)(state + 0x100) += 1;
            WEIGHT = 1.0f;
            break;
        case 0xDCF /* Joba smasher robot */:
            *(s32 *)(state + 0x104) += 1;
            WEIGHT = 1.0f;
            break;
        case 0xDF4 /* moby class 3572 */:
            *(s32 *)(state + 0x108) += 1;
            WEIGHT = 1.0f;
            break;
        case 0xDF7 /* moby class 3575 */:
            *(s32 *)(state + 0x10C) += 1;
            WEIGHT = 1.0f;
            break;
        case 0xDF9 /* Joba fighter */:
            if (moby_has_any_child_slot_used(*(u8 **)(slots + (*(s32 *)(state + 0x18C) << 2))) != 0)
                return 0;
            *(s32 *)(state + 0x110) += 1;
            WEIGHT = 1.0f;
            break;
        case 0xD37 /* moby class 3383 */:
            *(s32 *)(state + 0x114) += 1;
            WEIGHT = 1.0f;
            break;
        }
        moby_attach_child_first_free_slot(*(u8 **)(state + (*(s32 *)(state + 0x18C) << 2) + 0x120), other);
        return 1;
    }
    return 0;
}

#undef WEIGHT

/* func_L11_00440E18 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Walks the state's 0x120 slots in order and renews each live entry through the two shared helpers. */
extern s32 func_417238(s32);

extern void func_4172E8(s32);

/* Refreshes every squad slot that is in use. */
void arena_refresh_squad_slots(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    for (i = 0; i <= *(s32 *)(state + 0x18C); i++) {
        s32 *slot = (s32 *)(state + 0x120 + i * 4);
        if (slot[0] == 0) {
            continue;
        }
        if (func_417238(slot[0]) == 0) {
            continue;
        }
        func_4172E8(slot[0]);
    }
}

/* Clears the state's 0x120 slot table once every live entry has been accepted. */
extern s32 func_417270(s32);

/* Empties all squad slots once every squad is finished. */
void arena_clear_squad_slots_when_done(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    s32 accepted = 1;
    for (i = 0; i <= *(s32 *)(state + 0x18C); i++) {
        s32 *slot = (s32 *)(state + 0x120 + i * 4);
        if (slot[0] == 0) {
            continue;
        }
        if (func_417270(slot[0]) != 0) {
            continue;
        }
        accepted = 0;
        break;
    }
    if (accepted != 0) {
        s32 j;
        for (j = 0; j <= *(s32 *)(state + 0x18C); j++) {
            *(s32 *)(state + 0x120 + j * 4) = 0;
        }
        *(s32 *)(state + 0x18C) = 0;
    }
}

/* hands every entry of the class list to its measured handler */
extern u8 *g_group_id_lists[];

extern u8 *g_moby_l11_table;

extern void security_robot_deactivate(u8 *);

extern void smasher_robot_deactivate(u8 *);

extern void flamethrower_robot_deactivate(u8 *);

extern void drone_reset_to_idle(u8 *);

extern void fighter_reset_to_idle(u8 *);

extern void enemy_reset_to_idle(u8 *);

extern void chain_creature_clear_sound_flags(u8 *);

extern void drone_kill_with_effects(u8 *);

extern void joba_enemy_reset(u8 *);

/* The class table base read through an incomplete `sda` array: cc1 emits the one-instruction
   load, which the assembler expands absolute (`lui $r` / `lw $r,%lo($r)`) and which is not
   hoisted out of the loop, as retail has it (docs/build/compiler-notes.md). */
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));

/* Calls the matching handler for every fighter in the arena group. */
void arena_run_member_handlers(u8 *obj)
{
    s32 index = *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
    u16 *cursor;
    u8 *list;
    u8 *entry;

    if (index == 0xFF)
        return;
    list = g_group_id_lists[index];
    if (list == 0)
        return;
    cursor = (u16 *)list;
    do {
        entry = D_L11_001B359C_base[0] + ((*cursor & 0x7FFF) << 8);
        switch (*(s16 *)(entry + 0xAA)) {
        case 0xD98 /* Joba security robot */:
            security_robot_deactivate(entry);
            break;
        case 0xDCF /* Joba smasher robot */:
            smasher_robot_deactivate(entry);
            break;
        case 0xDF4 /* moby class 3572 */:
            flamethrower_robot_deactivate(entry);
            break;
        case 0xDF7 /* moby class 3575 */:
            drone_reset_to_idle(entry);
            break;
        case 0xDF9 /* Joba fighter */:
            fighter_reset_to_idle(entry);
            break;
        case 0xD37 /* moby class 3383 */:
            enemy_reset_to_idle(entry);
            break;
        case 0xD4A /* moby class 3402 */:
            chain_creature_clear_sound_flags(entry);
            break;
        case 0xD4B /* moby class 3403 */:
            drone_kill_with_effects(entry);
            break;
        case MOBY_CLASS_ARACHNOID:
            joba_enemy_reset(entry);
            break;
        }
    } while (*(s16 *)cursor++ >= 0);
}

/* func_L11_00441350 lives below, after the id-list macros it uses. */


/* arms the one-shot flag block when it is idle and the state agrees */
typedef struct { u8 pad[0x284]; s32 field284; s32 field288; } JobaFlagBlockView;

extern JobaFlagBlockView D_L11_001BA780;

/* Remembers which boss is in charge of the arena music and its health bar. */
void arena_set_boss_owner(u8 *object, s32 value) {
    u8 *state = *(u8 **)(object + 0x68);
    if (D_L11_001BA780.field284 == *(s32 *)(state + 0x184)) {
        D_L11_001BA780.field284 = 0;
    }
    if (value != 0 && D_L11_001BA780.field284 == 0) {
        D_L11_001BA780.field284 = value;
        D_L11_001BA780.field288 = 0;
    }
    *(s32 *)(state + 0x184) = value;
}

/* returns the 128-byte entry selected by the state index, at its 0x30-byte payload */
extern u8 *D_L11_001B368C __attribute__((sda));

/* Returns the position of the arena's center point. */
u8 *arena_get_center_point(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    return D_L11_001B368C + (*(s32 *)(state + 0x168) << 7) + 0x30;
}

/* returns zero for a missing state polygon index or dispatches its point query to the integrated crossing-parity helper */
/* Tells whether a point is inside the arena's floor shape. */
s32 arena_is_point_in_polygon(u8 *object, f32 *point) {
    u8 *state = *(u8 **)(object + 0x68);
    s32 index = *(s32 *)(state + 0x164);
    JobaPolygonHeaderView *header;
    s32 result;
    if (index == -1) {
        result = 0;
    } else {
        header = D_L11_001FF580[index];
        result = point_in_path_xy(point, (f32 *)(header + 1), header->field00);
    }
    return result;
}

/* Returns the state's 0xC0 word. */
/* Returns the number of the arena's main group. */
s32 arena_get_group_index(u8 *obj) {
    return *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
}

/* consumes one positive signed state counter selected by a measured class identifier and reports success */
/* Uses up one waiting fighter of the asked kind. Returns 1 if there was one. */
s32 arena_consume_waiting_fighter(u8 *object, s32 class_id) {
    JobaClassCounterView *state = *(JobaClassCounterView **)(object + 0x68);
    switch (class_id) {
        case 0xd98 /* Joba security robot */:
            if (state->fielde0 > 0) { state->fielde0--; return 1; }
            break;
        case 0xdcf /* Joba smasher robot */:
            if (state->fielde4 > 0) { state->fielde4--; return 1; }
            break;
        case 0xdf4 /* moby class 3572 */:
            if (state->fielde8 > 0) { state->fielde8--; return 1; }
            break;
        case 0xdf7 /* moby class 3575 */:
            if (state->fieldec > 0) { state->fieldec--; return 1; }
            break;
        case 0xdf9 /* Joba fighter */:
            if (state->fieldf0 > 0) { state->fieldf0--; return 1; }
            break;
        case 0xd37 /* moby class 3383 */:
            if (state->fieldf4 > 0) { state->fieldf4--; return 1; }
            break;
    }
    return 0;
}

/* increments one signed state counter selected by a measured class identifier */
/* Increments the state counter selected by the measured class identifier. */
/* Adds one waiting fighter of the asked kind. */
void arena_add_waiting_fighter(u8 *object, s32 class_id) {
    JobaClassCounterView *state = *(JobaClassCounterView **)(object + 0x68);
    switch (class_id) {
        case 0xd98 /* Joba security robot */: state->fielde0++; break;
        case 0xdcf /* Joba smasher robot */: state->fielde4++; break;
        case 0xdf4 /* moby class 3572 */: state->fielde8++; break;
        case 0xdf7 /* moby class 3575 */: state->fieldec++; break;
        case 0xdf9 /* Joba fighter */: state->fieldf0++; break;
        case 0xd37 /* moby class 3383 */: state->fieldf4++; break;
    }
}

/* Each group word of the object's state names an id list in D_L11_001FC420: halfwords whose low
   15 bits index the 256-byte records of D_L11_001B359C, the last one with its sign bit set. A
   walk stops when the group word (re-read after every callback) is 0xFF or above the limit
   kept at D_L11_001B35B8. */
extern s32 D_L11_001B35B8[] __attribute__((sda));

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L11_001FC420[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
         p++)

extern s16 moby_get_vars_counter(u8 *);
extern void moby_set_vars_counter_to_1(u8 *);
extern void moby_clear_vars_counter(u8 *);

/* Counts the entities of the object's group (state word 0xC8) for which func_L02_004024A0
   holds, then sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count
   equals the second argument. */
/* Switches fighters in the first group on or off until the wanted number are active. */
void arena_set_group_a_active_count(u8 *object, s32 count) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *cursor;
    u8 *member;
    s32 active_count = 0;

    FOR_EACH_ID(cursor, 0xC8) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (moby_get_vars_counter(member))
            active_count++;
    }
    if (active_count < count) {
        FOR_EACH_ID(cursor, 0xC8) {
            member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (!moby_get_vars_counter(member)) {
                moby_set_vars_counter_to_1(member);
                active_count++;
                if (active_count >= count)
                    break;
            }
        }
    } else if (active_count > count) {
        FOR_EACH_ID(cursor, 0xC8) {
            member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (moby_get_vars_counter(member)) {
                moby_clear_vars_counter(member);
                active_count--;
                if (active_count <= count)
                    break;
            }
        }
    }
}

extern s32 moby_get_busy_flag(u8 *);
extern void moby_set_busy_flag(u8 *);
extern void moby_clear_busy_flag(u8 *);

/* Counts the entities of the object's group (state word 0xCC) for which func_L02_003D7300
   holds, then sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count
   equals the second argument. */
/* Switches fighters in the second group on or off until the wanted number are active. */
void arena_set_group_b_active_count(u8 *object, s32 count) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *cursor;
    u8 *member;
    s32 active_count = 0;

    FOR_EACH_ID(cursor, 0xCC) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (moby_get_busy_flag(member))
            active_count++;
    }
    if (active_count < count) {
        FOR_EACH_ID(cursor, 0xCC) {
            member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (!moby_get_busy_flag(member)) {
                moby_set_busy_flag(member);
                active_count++;
                if (active_count >= count)
                    break;
            }
        }
    } else if (active_count > count) {
        FOR_EACH_ID(cursor, 0xCC) {
            member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (moby_get_busy_flag(member)) {
                moby_clear_busy_flag(member);
                active_count--;
                if (active_count <= count)
                    break;
            }
        }
    }
}

extern float vec_distance_squared_xy(void *, void *);
extern char g_hero_position[];

/* Over the entities of the object's group (state word 0xC0): first resets the "armed" halfword
   (1 -> 0) of the state of every entity of the four measured classes and reports its class to
   func_L11_00441978. Then, twice: picks the entity of those classes (state byte not 0xFE or 0xFD
   and at least 4, halfword not 1) that func_L02_002F21C0 puts nearest to D_00189EA0, and arms
   its halfword when func_L11_00441868 consumes the class's counter. */
/* Marks the fighters nearest to the player as the next ones to attack. */
void arena_mark_nearest_fighters_to_attack(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *cursor;
    u8 *member;
    u8 *nearest;
    f32 best_distance;
    f32 distance;
    s32 i;
    s32 ready_flag;

    FOR_EACH_ID(cursor, 0xC0) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        switch (*(s16 *)(member + 0xAA)) {
        case 0xD98 /* Joba security robot */:
            if (*(s16 *)(*(u8 **)(member + 0x68) + 0x366) == 1) {
                *(s16 *)(*(u8 **)(member + 0x68) + 0x366) = 0;
                arena_add_waiting_fighter(object, *(s16 *)(member + 0xAA));
            }
            break;
        case 0xDCF /* Joba smasher robot */:
            if (*(s16 *)(*(u8 **)(member + 0x68) + 0x4CA) == 1) {
                *(s16 *)(*(u8 **)(member + 0x68) + 0x4CA) = 0;
                arena_add_waiting_fighter(object, *(s16 *)(member + 0xAA));
            }
            break;
        case 0xDF9 /* Joba fighter */:
            if (*(s16 *)(*(u8 **)(member + 0x68) + 0x256) == 1) {
                *(s16 *)(*(u8 **)(member + 0x68) + 0x256) = 0;
                arena_add_waiting_fighter(object, *(s16 *)(member + 0xAA));
            }
            break;
        case 0xD37 /* moby class 3383 */:
            if (*(s16 *)(*(u8 **)(member + 0x68) + 0x282) == 1) {
                *(s16 *)(*(u8 **)(member + 0x68) + 0x282) = 0;
                arena_add_waiting_fighter(object, *(s16 *)(member + 0xAA));
            }
            break;
        }
    }

    for (i = 0; i < 2; i++) {
        nearest = 0;
        best_distance = 10000.0f;
        FOR_EACH_ID(cursor, 0xC0) {
            member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            ready_flag = -1;
            switch (*(s16 *)(member + 0xAA)) {
            case 0xD98 /* Joba security robot */:
                ready_flag = *(s16 *)(*(u8 **)(member + 0x68) + 0x366);
                break;
            case 0xDCF /* Joba smasher robot */:
                ready_flag = *(s16 *)(*(u8 **)(member + 0x68) + 0x4CA);
                break;
            case 0xDF9 /* Joba fighter */:
                ready_flag = *(s16 *)(*(u8 **)(member + 0x68) + 0x256);
                break;
            case 0xD37 /* moby class 3383 */:
                ready_flag = *(s16 *)(*(u8 **)(member + 0x68) + 0x282);
                break;
            }
            /* Retail tests the entity again after the switch and reads its class a second time as
               an unsigned halfword: both are needed for the same words. */
            if (member == 0)
                continue;
            if (member[0x20] == 0xFE)
                continue;
            if (member[0x20] == 0xFD)
                continue;
            if ((s16)*(u16 *)(member + 0xAA) != 0xD98 /* Joba security robot */ && (s16)*(u16 *)(member + 0xAA) != 0xDCF /* Joba smasher robot */ &&
                (s16)*(u16 *)(member + 0xAA) != 0xDF9 /* Joba fighter */ && (s16)*(u16 *)(member + 0xAA) != 0xD37 /* moby class 3383 */)
                continue;
            if (ready_flag == 1)
                continue;
            if (member[0x20] < 4)
                continue;
            if (nearest == 0) {
                nearest = member;
                best_distance = vec_distance_squared_xy(nearest + 0x10, g_hero_position);
            } else {
                distance = vec_distance_squared_xy(member + 0x10, g_hero_position);
                if (distance < best_distance) {
                    nearest = member;
                    best_distance = distance;
                }
            }
        }
        if (nearest != 0) {
            switch (*(s16 *)(nearest + 0xAA)) {
            case 0xD98 /* Joba security robot */:
                if (arena_consume_waiting_fighter(object, 0xD98 /* Joba security robot */))
                    *(s16 *)(*(u8 **)(nearest + 0x68) + 0x366) = 1;
                break;
            case 0xDCF /* Joba smasher robot */:
                if (arena_consume_waiting_fighter(object, 0xDCF /* Joba smasher robot */))
                    *(s16 *)(*(u8 **)(nearest + 0x68) + 0x4CA) = 1;
                break;
            case 0xDF9 /* Joba fighter */:
                if (arena_consume_waiting_fighter(object, 0xDF9 /* Joba fighter */))
                    *(s16 *)(*(u8 **)(nearest + 0x68) + 0x256) = 1;
                break;
            case 0xD37 /* moby class 3383 */:
                if (arena_consume_waiting_fighter(object, 0xD37 /* moby class 3383 */))
                    *(s16 *)(*(u8 **)(nearest + 0x68) + 0x282) = 1;
                break;
            }
        }
    }
}

/* func_L11_00441FB8 lives in L11_00441FB8.c. */

extern s32 arena_is_target_outside(u8 *, u8 *, s32);
extern void moby_set_anim_type_three(u8 *, s32, s32);
extern void security_robot_kill(u8 *, s32, s32);
extern s32 drone_is_state_at_least_four(u8 *);
extern void part_queue_moby_for_glow(u8 *, s32, void (*)(u8 *));
extern void hero_record_play_counters(void);
extern u8 g_hero_state[];

/* Hands every entity of the object's group (state word 0xC0) that the shared test func_L11_00441FB8
   accepts, and whose state byte is not 0xFE, 0xFD or below 3, to the handler of its class (the
   halfword at +0xAA); then runs the test once more on the entity D_00189E20 holds at +0x2290. */
/* Lets every fighter that is inside the arena act, and checks the player too. */
void arena_update_fighters_inside(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *cursor;
    u8 *member;
    u8 *player;

    FOR_EACH_ID(cursor, 0xC0) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (member[0x20] == 0xFE)
            continue;
        if (member[0x20] == 0xFD)
            continue;
        if (member[0x20] < 3)
            continue;
        if (arena_is_target_outside(object, member, 0) == 0)
            continue;
        switch (*(s16 *)(member + 0xAA)) {
        case 0xD98 /* Joba security robot */:
            security_robot_kill(member, 0, 0);
            break;
        case 0xDCF /* Joba smasher robot */:
            moby_set_anim_type_three(member, 0, -1);
            smasher_robot_deactivate(member);
            break;
        case 0xDF4 /* moby class 3572 */:
            moby_set_anim_type_three(member, 0, -1);
            flamethrower_robot_deactivate(member);
            break;
        case 0xDF7 /* moby class 3575 */:
            moby_set_anim_type_three(member, 0, -1);
            drone_reset_to_idle(member);
            break;
        case 0xDF9 /* Joba fighter */:
            moby_set_anim_type_three(member, 0, -1);
            part_queue_moby_for_glow(member, 0, fighter_reset_to_idle);
            break;
        case 0xD37 /* moby class 3383 */:
            moby_set_anim_type_three(member, 0, -1);
            enemy_reset_to_idle(member);
            break;
        case 0xD4B /* moby class 3403 */:
            if (drone_is_state_at_least_four(member))
                drone_kill_with_effects(member);
            break;
        }
    }
    player = g_hero_state;
    if (arena_is_target_outside(object, *(u8 **)(player + 0x2290), 1))
        hero_record_play_counters();
}

/* func_L11_004423F8 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* func_L11_004425C8 is defined in its dedicated source unit. */

/* func_L11_00442B60 is defined in its dedicated source unit. */

extern void moby_finish_release_child(u8 *);

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0x178 and
   0x174); an empty group, or a group word of 0xFF, ends the function. */
/* Runs the same helper on every member of the two spawn point groups. */
void arena_run_helper_on_spawn_groups(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *cursor;
    u16 *first_entry;
    u8 *member;

    if (GROUP(0x178) == 0xFF)
        return;
    first_entry = (u16 *)g_group_id_lists[GROUP(0x178)];
    if (first_entry == 0)
        return;
    for (cursor = first_entry; (GROUP(0x178) & 0xFF) != 0xFF && GROUP(0x178) <= D_L11_001B35B8[0] && cursor != 0 &&
                ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)g_group_id_lists[GROUP(0x178)]);
         cursor++) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        moby_finish_release_child(member);
    }
    if (GROUP(0x174) == 0xFF)
        return;
    first_entry = (u16 *)g_group_id_lists[GROUP(0x174)];
    if (first_entry == 0)
        return;
    for (cursor = first_entry; (GROUP(0x174) & 0xFF) != 0xFF && GROUP(0x174) <= D_L11_001B35B8[0] && cursor != 0 &&
                ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)g_group_id_lists[GROUP(0x174)]);
         cursor++) {
        member = g_moby_l11_table + ((*cursor & 0x7FFF) << 8);
        if (member == 0)
            break;
        moby_finish_release_child(member);
    }
}

/* func_L11_00442E38 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* func_L11_00443380 and func_L11_004433D8 live in the sibling small-data unit
   (L11_0043E1A0-g8.c): they reach the level's globals through $gp. */

/* func_L11_00443498 is in L11_00443498-g8.c. */

/* func_L11_00443940 is in L11_00443940-g8.c. */

/* maps the class index to its measured identifier */
extern u32 D_L11_002BB0E0[];

/* The level's own jump table: the address of each case body. */
extern void *jtbl_002BB0E0[13];

/* Returns the text number of a challenge's title. */
s32 arena_get_challenge_title_text_id(s32 index) {
    static void * volatile tab[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7,
        &&c8, &&c9, &&c10, &&c11, &&c12
    };

    if ((u32)index >= 13) {
        goto def;
    }
    goto *jtbl_002BB0E0[index];
c0:
    return 0x2F66;
c1:
    return 0x2F67;
c2:
    return 0x2F68;
c3:
    return 0x2F69;
c4:
    return 0x2F6A;
c5:
    return 0x2F6B;
c6:
    return 0x2F6C;
c7:
    return 0x2F6D;
c8:
    return 0x2F70;
c9:
    return 0x2F71;
c10:
    return 0x3243;
c11:
    return 0x3244;
c12:
    return 0x3245;
def:
    return 0x2F66;
}

/* func_L11_00443D78 is in L11_00443D78-g8.c. */

/* func_L11_00444400 is in L11_00444400-g8.c. */

/* func_L11_004456A0 is in L11_004456A0-g8.c. */

/* func_L11_00445990 is defined in L11_00445990-g8.c ($gp accesses). */

/* func_L11_00445B30 is defined in L11_00445B30-g-g8.c. */

/* Claims the shared call slot for the state entry the identifier names. */
typedef struct {
    u8 pad0[0x24];
    s32 field24;
    s32 field28;
    u8 pad2[0x3C];
    s32 field68;
} JobaCallSlotView;

extern u8 g_music_state[];

/* Claims the shared call slot for the state entry the caller's class identifier
   selects, unless the slot is already busy or waiting. */

/* Starts a voice line for the arena. Returns 1 if the line could be started. */
s32 arena_queue_voice_line(u8 *obj, s32 idx) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 line_value;

    if ((u32)idx >= 0x27) {
        return 0;
    }
    if (idx < 0x14) {
        s32 *slot_ptr = (s32 *)((u8 *)state + idx * 4);
        line_value = slot_ptr[0x84];
    } else {
        s32 *slot_ptr = (s32 *)((u8 *)state + (idx - 0x14) * 4);
        line_value = slot_ptr[0x98];
    }
    {
        JobaCallSlotView *slot = (JobaCallSlotView *)g_music_state;

        if (slot->field68 != 0) {
            goto fail;
        }
        if (slot->field24 != -1) {
            goto fail;
        }
        slot->field24 = (line_value & 0x3FFF) + 0x7D0;
        slot->field28 = 0;
        {
            s16 *slot_ptr = (s16 *)((u8 *)state + idx * 2 + 0x2A0);
            *slot_ptr = 1;
        }
    }
    return 1;
fail:
    return 0;
}
/* func_L11_00445DF8 is defined in L11_00445DF8-g8.c ($gp accesses). */

/* func_L11_00446020 lives in L11_00446020-g8.c. */

/* hands the state's 0x1C4 field to the shared helper, after the caller's argument */
extern int coll_point_inside_record_volume(void *, int);

/* Tells whether a point is inside the arena's inner zone. */
int arena_is_point_in_inner_zone(u8 *object, u8 *point) {
    u8 *state = *(u8 **)(object + 0x68);
    return coll_point_inside_record_volume(point, *(int *)(state + 0x1C4));
}
