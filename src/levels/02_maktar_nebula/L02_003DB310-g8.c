#include "include_asm.h"
#include "names.h"

extern int D_L02_001B04DC __attribute__((sda));

extern void part_spawn_rising();

extern void moby_transform_joint_to_world(char *arg0, int arg1, char *arg2);

extern char D_L02_001B0F60[4] __attribute__((sda));

extern int D_L02_001B0FA0 __attribute__((sda));

extern int D_L02_001B0FA4;

extern void func_2EEFB0(char *, int, char *, char *, int, int, int, int, float);

/* Hands the actor's four widget slots to the effect scheduler. */
void widget_submit_effects(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    func_2EEFB0(D_L02_001B0F60, 4, vars + 0x2A0, vars + 0x3A0,
                *(int *)(vars + 0x4D4), *(int *)(vars + 0x4D0), D_L02_001B0FA0,
                D_L02_001B0FA4, *(float *)(vars + 0x4D8));
}

/* Rebuild the four widget descriptions from the resident template. */
void boss_rebuild_joint_widgets(char *moby) {
    char buffer[16];

    moby_transform_joint_to_world(moby, 2, buffer);
    part_spawn_rising(buffer, D_L02_001B04DC);
    moby_transform_joint_to_world(moby, 4, buffer);
    part_spawn_rising(buffer, D_L02_001B04DC);
    moby_transform_joint_to_world(moby, 8, buffer);
    part_spawn_rising(buffer, D_L02_001B04DC);
    moby_transform_joint_to_world(moby, 6, buffer);
    part_spawn_rising(buffer, D_L02_001B04DC);
}

/* The entity array's base: `sda` with a size over 8 bytes gives the bare-symbol load, which the
   assembler expands to retail's one-register `lui`/`lw` pair instead of a $gp access. */
extern unsigned char *g_moby_l02_pool[3] __attribute__((sda));

extern int D_L02_001B35B8 __attribute__((sda));

extern unsigned short *g_entity_group_lists[];

/* For each entity of the object's group that has class 0xAB0, sets its state byte (+0x20) from
   the first word of its private data: 1 gives 6, 2 gives 7, anything else 3. */
void group_set_moby_states_from_mode(unsigned char *moby) {
    unsigned short *groupEntry;
    unsigned char *entity;

    if (moby[0x21] == 0xFF)
        return;
    groupEntry = g_entity_group_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L02_001B35B8 && groupEntry != 0 &&
           ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == g_entity_group_lists[moby[0x21]])) {
        entity = g_moby_l02_pool[0] + ((*groupEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (*(short *)(entity + 0xAA) == 0xAB0 /* moby class 2736 */) {
            int kind = **(int **)(entity + 0x68);

            entity[0x20] = (kind == 1) ? 6 : ((kind == 2) ? 7 : 3);
        }
        groupEntry++;
    }
}

/* 0 when an entity of the object's group has class 0xAB0 and a state byte (+0x20) other than
   6 or 7, else 1. */
int group_are_mobys_settled(unsigned char *moby) {
    unsigned short *groupEntry;
    unsigned char *entity;

    if (moby[0x21] == 0xFF)
        return 1;
    groupEntry = g_entity_group_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L02_001B35B8 && groupEntry != 0 &&
           ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == g_entity_group_lists[moby[0x21]])) {
        entity = g_moby_l02_pool[0] + ((*groupEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        groupEntry++;
        if (*(short *)(entity + 0xAA) == 0xAB0 /* moby class 2736 */ && (unsigned char)(entity[0x20] - 6) >= 2)
            return 0;
    }
    return 1;
}

extern int D_L02_001B35B8 __attribute__((sda));

/* The word D_L02_001B359C, read here through $gp; the walks above reach it as a bare symbol. */
extern char *D_L02_001B359C_gp;

extern unsigned short *g_entity_group_lists[];

extern char g_hero_state[];

extern char *moby_get_private_value_2(char *);

extern void mat_combine_and_store(void *, void *, void *, void *);

/* For every entity of the object's group, copies the word at +0x10 of its +0x24 record into
   its word at +0x98. */
void group_reset_moby_hit_points(unsigned char *moby) {
    unsigned short *groupEntry;
    char *entity;

    for (groupEntry = g_entity_group_lists[moby[0x21]];
         moby[0x21] != 0xFF && moby[0x21] <= D_L02_001B35B8 && groupEntry != 0 &&
         ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == g_entity_group_lists[moby[0x21]]);
         groupEntry++) {
        entity = D_L02_001B359C_gp + ((*groupEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        *(int *)(entity + 0x98) = *(int *)(*(char **)(entity + 0x24) + 0x10);
    }
}

/* Walks the entities of the actor's group (D_L02_001FC060[actor[0x21]], ids masked with 0x7FFF,
   0x100-byte records at D_L02_001B359C, the list ends after an id with bit 15 set). Each entity
   of class 0xAAF has its effect (func_002AD0B0) handed to func_002AD6F0; the result says whether
   one of them is the entity D_00189E20 tracks at +0x33C while its flag at +0x340 is set.

   The loop condition tests p twice, the second time as the guard of the p[-1] read, as a list
   macro written on top of a pointer check produces. That second test is what makes retail's
   loop: its `||` leaves a label in the exit test, so jump.c keeps the test at the bottom instead
   of copying it in front of the loop (retail enters with `b test`); GCSE's %hi copy then lands
   after the loop note, which makes loop.c skip the loop (no hoisted constants) and the
   scheduler leave the copy last (the delay slot of `b test`); the loop depth puts that copy in
   $s3 and a1 in $s4. CSE removes the repeated test afterwards. Without it the test is copied in
   front of the loop and the function grows to 364 bytes. */
int group_update_effect_mobys(unsigned char *moby, void *effectArg) {
    int result = 0;
    unsigned short *groupEntry;
    char *entity;

    for (groupEntry = g_entity_group_lists[moby[0x21]];
         moby[0x21] != 0xFF && moby[0x21] <= D_L02_001B35B8 && groupEntry != 0 &&
         ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == g_entity_group_lists[moby[0x21]]);
         groupEntry++) {
        entity = D_L02_001B359C_gp + ((*groupEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (*(short *)(entity + 0xAA) == 0xAAF /* moby class 2735 */) {
            char *heroBlock = g_hero_state;
            void *effect;

            if (entity == *(char **)(heroBlock + 0x33C)) {
                if (*(int *)(heroBlock + 0x340) != 0)
                    result = 1;
            }
            effect = (void *)moby_get_private_value_2(entity);
            if (effect != 0)
                mat_combine_and_store(effect, effectArg, moby + 0xF0, moby + 0xF0);
        }
    }
    return result;
}

extern unsigned char D_001395B8[0x100];

extern int D_0018C2EC __attribute__((nosda));

extern int D_001A7A00;

/* The six weights, read through $gp: `sda` with a size of at most 8 bytes, indexed past it. */
extern int D_L02_001B0938[2] __attribute__((sda));

extern char D_L02_001B09E0[];

extern char D_L02_001B09F0[];

extern void STUB_printf(const char *, ...);

extern int math_random_int_below(int);

extern int math_random_int_range(int, int);

/* Rolls the state's mode (+0x5C) against the six weights, turns mode 4 into 1 when the two
   reference words agree and mode 5 into 1 while the counter at D_001395B8[0x8F] is under 4,
   copies it into the three slots at +0x90, and for mode 0 rolls three values from 1 to 5 until
   they are not all the same. The jump pass peels the loop's first test in front of it; the unit
   is built with -frac2-gcse-unsplit-edges (config/cflags.txt), so the two high halves gcse hoists
   sit above that copy as in retail. */
void slot_machine_roll_result(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int roll;
    int i;
    int mode;

    roll = math_random_int_below(1000);
    STUB_printf(D_L02_001B09E0, roll);
    *(int *)(vars + 0x5C) = 0;
    for (i = 0; i < 6; i++) {
        roll -= D_L02_001B0938[i];
        if (roll < 0) {
            *(int *)(vars + 0x5C) = i;
            break;
        }
    }
    if (*(int *)(vars + 0x5C) == 4) {
        if (D_0018C2EC == D_001A7A00)
            *(int *)(vars + 0x5C) = 1;
    }
    if (D_001395B8[0x8F] < 4) {
        if (*(int *)(vars + 0x5C) == 5)
            *(int *)(vars + 0x5C) = 1;
    }
    mode = *(int *)(vars + 0x5C);
    *(int *)(vars + 0x90) = *(int *)(vars + 0x94) = *(int *)(vars + 0x98) = mode;
    STUB_printf(D_L02_001B09F0, mode);
    if (*(int *)(vars + 0x5C) == 0) {
        int thirdRoll;

        *(int *)(vars + 0x90) = math_random_int_range(1, 5);
        *(int *)(vars + 0x94) = math_random_int_range(1, 5);
        do {
            thirdRoll = math_random_int_range(1, 5);
            *(int *)(vars + 0x98) = thirdRoll;
        } while (*(int *)(vars + 0x90) == *(int *)(vars + 0x94) &&
                 *(int *)(vars + 0x90) == thirdRoll);
    }
}

extern unsigned char D_001A7AFA;
extern char g_hero_position[];
extern unsigned short D_0018C31C[];
extern int IsPointInCuboid(void *, int);
extern void hero_trigger_spawn_effect(void);
extern void moby_set_state(char *, int, int);

/* Per-frame update for moby class 2647. It sets itself up once, then keeps checking the hero for a special trigger. */
void trigger_l02_update(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x30) = 0xFF;
        if (D_001A7AFA == 0)
            D_0018C31C[0] = 1;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        hero_trigger_spawn_effect();
        if (IsPointInCuboid(g_hero_position, *(int *)vars))
            *(unsigned short *)(g_hero_position + 0x19A) = 5;
        break;
    }
}

/* D_L02_001CAA80 is read as the first word of a larger object: cc1 then splits the address and
   retail's `lui $v0` / `lw $v1,%lo($v0)` come out in two registers, where a one-word extern is a bare
   symbol that gas expands in one. */
extern int D_L02_001CAA80[3];

extern int g_hovering_object_count;

extern int D_L02_001B41DC;

extern int g_frame_l02_counter;

extern int D_L02_001B0A60 __attribute__((sda));

extern float D_L02_001B0A20 __attribute__((sda));

extern float D_L02_001B0A28 __attribute__((sda));

extern float D_L02_001B0A30 __attribute__((sda));

extern void moby_set_state();

extern void *part_find_owned_effect_slot(void *, int, int);

extern void gfx_add_draw_callback_first(void *, void *);

extern void DrawRotatingObjectGroupEffects();

extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);

extern void part_spawn_scaled_bolts(void *, int, float);

extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Per-frame update for moby class 2724. One step of an actor, by its state byte (+0x20). State 0 marks the actor (+0x30), moves it to
   state 1 and lowers the counter D_L02_001AEC78 when its private word is set. Unless
   D_L02_001CAA80 is 1, state 1 registers the callback func_L02_003E80F8 once per value of
   D_L02_001B30C8 and, when func_002A9640 finds something and the private word is clear, lowers
   the counter and moves to state 2; it always ends by setting the byte at +0xA8. State 2 starts
   the effects and moves to state 3, which sets the half-word at +0x7C. */
void effect_l02_spawner_update(unsigned char *moby) {
    int stateByte = moby[0x20];
    int *vars = *(int **)(moby + 0x68);

    switch (stateByte) {
    case 0:
        moby[0x30] = 0xFF;
        moby_set_state(moby, 1, -1);
        if (*vars != 0)
            g_hovering_object_count--;
        break;
    case 1:
        if (D_L02_001CAA80[0] != 1) {
            if (D_L02_001B41DC != g_frame_l02_counter) {
                D_L02_001B41DC = g_frame_l02_counter;
                gfx_add_draw_callback_first(DrawRotatingObjectGroupEffects, moby);
            }
            if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *vars == 0) {
                g_hovering_object_count--;
                moby_set_state(moby, 2, -1);
            }
            moby[0xA8] = 0xFF;
        }
        break;
    case 2:
        part_explode_object_into_pieces(moby, &D_L02_001B0A30, &D_L02_001B0A28, &D_L02_001B0A20, 0xFFFF, 0,
                          D_L02_001B0A60, 1, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts(moby, 5, 0.5f);
        SpawnExplosion(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        *(unsigned short *)(moby + 0x7C) = 0x8020;
        break;
    }
}

extern int math_is_below_plane_within_depth(float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern float coll_probe_ground_height_below(void *, int, float);

extern float math_random_float_range(float, float);

extern void *part_spawn_puff(void *, int, float, float);

extern float D_L02_001B0530 __attribute__((sda));

extern float D_L02_001B0534;

/* Looks for a trigger in the hero block (D_00189E20): its half-word at +0x1490 is 10, its word at
   +0x340 is set, and either its words at +0x1B8 and +0x2294 are 1 and 2 (the selector then comes
   from func_002A77E0) or the object at +0x2290 has kind 3 or 4 (byte +0x43), the word at +0xC2C
   is clear and func_L00_002B3998 accepts one of two distances (selector 0 or 1). On a trigger it
   places a point on the object's joint (selector + 0x16), moved by the hero's heading (+0x98)
   and raised, and hands it to func_002C3D80. The block's address is taken three times, once for
   each of the tests, the kind switch and the effect, as three separate pointers. */
void hero_trigger_spawn_effect(void) {
    int found = 0;
    int sel = 0;
    float v[4];
    char *g;
    char *h;
    char *k;

    g = g_hero_state;
    if (*(short *)(g + 0x1490) == 10 && *(int *)(g + 0x340) != 0) {
        if (*(int *)(g + 0x1B8) == 1 && *(int *)(g + 0x2294) == 2) {
            sel = math_random_int_below(2);
            found = 1;
        } else {
            h = g_hero_state;
            switch (*(unsigned char *)(*(char **)(h + 0x2290) + 0x43)) {
            case 3:
                if (*(int *)(h + 0xC2C) == 0) {
                    if (math_is_below_plane_within_depth(49.5f) != 0) {
                        found = 1;
                        sel = 0;
                    }
                    if (math_is_below_plane_within_depth(17.0f) != 0) {
                        found = 1;
                        sel = 1;
                    }
                }
                break;
            case 4:
                if (*(int *)(h + 0xC2C) == 0) {
                    if (math_is_below_plane_within_depth(12.5f) != 0) {
                        found = 1;
                        sel = 0;
                    }
                    if (math_is_below_plane_within_depth(1.0f) != 0) {
                        found = 1;
                        sel = 1;
                    }
                }
                break;
            }
        }
    }
    if (found) {
        k = g_hero_state;
        moby_transform_joint_to_world(*(char **)(k + 0x2290), sel + 0x16, (char *)v);
        v[0] += math_fast_sin_or_cos_a(*(float *)(k + 0x98)) * 0.15f;
        v[1] += math_fast_sin_or_cos_b(*(float *)(k + 0x98)) * 0.15f;
        v[2] = coll_probe_ground_height_below(v, 0, 0.5f) + 0.04f;
        part_spawn_puff(v, -1, math_random_float_range(D_L02_001B0530, D_L02_001B0534), 5250.0f);
    }
}
