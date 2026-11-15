#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
typedef struct { unsigned char pad[0x70]; long f70, f78, f80, f88; } QuadPacket;
typedef union {
    QuadPacket packet;
    struct { Vector corners[4]; unsigned int colours[4]; float uv[8]; } geometry;
} RenderQuad;

extern void FastVecAdd(char *, char *, char *);

extern void make_hit_descriptor(char *, int, int, void *, float);

extern int CollLine(void *, void *, int, int, void *);

extern int math_fast_float_d(void *);

extern void snd_play_from_class_bank(int, int, void *, int);

extern void gfx_add_draw_callback_third(void *, int);

extern void EmitJitteredParticleTrail(char *);

extern void part_l20_spawn_spark_burst(char *, int, int);

extern char D_L20_001C0420[];

extern char *D_L20_001FBB20[];

extern char *D_L20_001B2F9C __attribute__((sda));

extern float D_L20_0023E670[];

/* func_L20_0039C448 is defined in L20_0039C448-qcopy.c (its copy needs the grouped-copy profile). */

extern char *CreateMoby(int);

/* func_L20_0039C5D0 is defined in L20_0039C5D0.c (grouped-copy profile). */

/* func_L20_0039C8C8 is defined in L20_0039C8C8.c. */


/* func_L20_0039CF58 is defined in L20_0039CF58.c. */

/* func_L20_0039D340 is defined in L20_0039D340-g8.c (it reads data through $gp). */


extern int D_L20_001B2AC8 __attribute__((sda));

extern int trooper_spawn_parts(char *, int);

extern void SpawnHealthThresholdEffects(char *);

extern void trooper_count_closer_mates(char *);

extern float fast_subtract_rotations(float, float);

extern float math_approach_target_with_direction_mode(char *, char *, float, float, float, float, int);

/* Updates the trooper every frame: its body parts, its aim at the player, and its age counter. */
void trooper_update_body(char *mobyIn) {
    char *moby = mobyIn;
    char *vars;
    f32 turnRate;
    f32 angleDelta;
    u32 unused;
    u16 age;

    vars = *(char **)(moby + 0x68);
    trooper_spawn_parts(moby, 0);
    SpawnHealthThresholdEffects(moby);
    if ((D_L20_001B2AC8 & 7) == (((s32)moby >> 8) & 7)) {
        trooper_count_closer_mates(moby);
    }
    turnRate = 0.009696274995803833f;
    angleDelta = fast_subtract_rotations(*(f32 *)(vars + 0x284), *(f32 *)(moby + 0xF8));
    {
        f32 turnRate2 = turnRate;
        math_approach_target_with_direction_mode(vars + 0x288, vars + 0x28C, angleDelta, turnRate, turnRate2, 0.58177649974823f, 0);
    }
    *(f32 *)(vars + 0x284) = *(f32 *)(moby + 0xF8);
    age = *(u16 *)(moby + 0x96);
    if ((u32)age <= 0xFFFEu) {
        *(u16 *)(moby + 0x96) = age + 1;
    }
}

/* func_L20_0039D880 is defined in L20_0039D880.c. */

extern void anim_start_blended(void *, int, int, int);

/* Plays one animation on the trooper and on its torso part. */
void trooper_play_anim_with_torso(char *moby, int animId, int blendTime, float frame) {
    char *state = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x43) != animId) {
        anim_start_blended(moby, animId, (int)frame, blendTime);
    }
    anim_start_blended(*(char **)(state + 0x254), animId, (int)frame, blendTime);
}

/* func_L20_0039DBC8 is defined in L20_0039DBC8-g8.c (it needs the -G8 profile). */

extern void moby_mark_spawned(int);

extern void moby_set_state(char *, int, int);

/* Takes the trooper apart: resets it and deletes its torso and leg parts. */
void trooper_destroy_parts(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char **slotPtr;
    int i;

    moby_set_state(moby, 6, 2);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    *(int *)(moby + 0x98) = 0;
    if (*(int *)(state + 0x254) != 0) {
        moby_mark_spawned(*(int *)(state + 0x254));
        *(int *)(state + 0x254) = 0;
    }
    slotPtr = (char **)(state + 0x258);
    for (i = 1; i >= 0; i--) {
        if (*slotPtr != 0) {
            moby_mark_spawned(*slotPtr);
            *slotPtr = 0;
        }
        slotPtr++;
    }
}

extern void *func_00325040(int);
extern void func_0033E708(char *, char *);
extern char *func_00338198(char *);
extern void func_00326528(char *, int, char *);
extern f32 func_00303270(f32, f32);
extern void func_00327AD0(void *);
extern void func_003381E0(void *, void *);
extern void func_00338830(void *, u32, int, int);
extern void func_0032F2D0(void *, int, int, int);

/* Creates the torso and leg parts if asked, then puts them on the trooper pose. Returns 0 if a part cannot be made. */
int trooper_spawn_parts(char *mobyIn, int createParts) {
    char *part;
    char *legSlot;
    char *moby = mobyIn;
    char *vars;
    char *work;
    int legIndex;
    char *legSlotPtr;
    int legBlend;
    int result;

    vars = *(char **)(moby + 0x68);
    if (createParts != 0) {
        if (*(char **)(vars + 0x254) == 0) {
            part = (char *)func_00325040(0xD0E);
            if (part == 0) {
                result = 0;
                goto out;
            }
            func_0033E708(part, moby);
            *(u16 *)(part + 0x7C) = 0x3FF;
            *(char **)(vars + 0x254) = part;
        }
        work = 0;
        legSlot = vars + 0x258;
        while ((int)work < 2) {
            if (*(u32 *)legSlot == 0) {
                part = (char *)func_00325040(0xD66);
                if (part == 0) {
                    result = 0;
                    goto out;
                }
                func_0033E708(part, moby);
                *(u32 *)legSlot = (u32)part;
            }
            work++;
            legSlot += 4;
        }
    }
    work = (char *)func_00338198(moby);
    if (*(char **)(vars + 0x254) != 0) {
        func_00326528(moby, 0, *(char **)(vars + 0x254) + 0x10);
        *(f32 *)(*(char **)(vars + 0x254) + 0xF8) = func_00303270(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x288));
        func_00327AD0(*(char **)(vars + 0x254));
        func_003381E0(*(char **)(vars + 0x254), work);
        if (*(u8 *)(*(char **)(vars + 0x254) + 0x43) != *(u8 *)(moby + 0x43)) {
            func_0032F2D0(*(char **)(vars + 0x254), *(u8 *)(moby + 0x43), *(u8 *)(moby + 0x41), 0xA);
        }
    }
    legIndex = 0;
    legBlend = 6;
    legSlotPtr = vars + 0x258;
    while (legIndex < 2) {
        if (*(u32 *)legSlotPtr != 0) {
            func_00338830(*(char **)(vars + 0x254), *(u32 *)legSlotPtr, legIndex, (legIndex == 1) ? legBlend : 0);
            func_003381E0(*(u32 *)legSlotPtr, work);
        }
        legIndex++;
        legSlotPtr += 4;
    }
    result = 1;
out:
    return result;
}

extern int D_L20_001B2FB8;

/* func_L20_0039E0A0 is defined in L20_0039E0A0-g8.c (it needs the -G8 profile). */

extern void weapon_select_aim_target(char *, int, float, float, int, int);

extern char *FindLastGroupMemberInRange(char *, char *);

/* func_L20_0039E158 is in L20_0039E158.c with its grouped-copy profile. */

extern f32 math_random_float_range(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_fast_normalize_helper(char *, char *, f32);
extern f32 vec_distance_xy(void *, void *);
extern char g_hero_state[];
extern float D_L20_001B9FD8;

/* func_L20_0039E1E8: picks a point state[0x260] 8 to 12 units (in xy) from a target.
 * When the target at state[0x200] is the hero's moby (D_00189E20 + 0x2290), the point
 * is placed around the hero's position (D_00189E20 + 0x80) at an angle within 45
 * degrees of D_L20_001B9FD8.  Otherwise it is the offset from the target to this
 * moby, shortened to that distance when longer, added back to the target's position.
 * state + 0x260 and arg0 + 0x10 are written at each use rather than kept in variables:
 * that is what gives retail's copy of the pointer in a register live after the if. */
/* Picks a spot near the target where the trooper wants to stand. */
void trooper_choose_stand_point(char *moby) {
    char *state = *(char **)(moby + 0x68);
    f32 dist;
    f32 angle;
    char *hero;

    dist = math_random_float_range(8.0f, 12.0f);
    hero = g_hero_state;
    if (*(char **)(state + 0x200) == *(char **)(hero + 0x2290)) {
        angle = math_random_float_range(-45.0f, 45.0f);
        angle = FastAddRotations(angle * 0.017453294f, D_L20_001B9FD8);
        *(f32 *)(state + 0x260) = math_fast_sin_or_cos_a(angle) * dist;
        *(f32 *)(state + 0x264) = math_fast_sin_or_cos_b(angle) * dist;
        *(int *)(state + 0x268) = 0;
        FastVecAdd(state + 0x260, state + 0x260, hero + 0x80);
    } else {
        FastVecSub(state + 0x260, moby + 0x10, *(char **)(state + 0x200) + 0x10);
        if (dist < FastVecLength(state + 0x260)) {
            vec_fast_normalize_helper(state + 0x260, state + 0x260, dist);
        }
        FastVecAdd(state + 0x260, state + 0x260, *(char **)(state + 0x200) + 0x10);
    }
    *(f32 *)(state + 0x11C) = vec_distance_xy(moby + 0x10, state + 0x260);
}


/* func_L20_0039E5F0 is defined in L20_0039C448-g8.c (it reaches a global through $gp). */
/* func_L20_0039E770 is defined in L20_0039E770.c for its grouped-copy profile. */

/* func_L20_0039E890 is defined in L20_0039C448-g8.c (it reaches a global through $gp). */


/* func_L20_0039EBB8 is defined in L20_0039EBB8-qcopy.c (it needs the grouped-copy profile with -g). */


/* func_L20_0039EEC8 is defined in L20_0039EEC8-g8-qcopy.c (it reaches data through $gp and needs the qcopy profile with -g). */

/* func_L20_0039F210 is in L20_0039F210.c with its grouped-copy scheduling profile. */

extern void electric_orb_draw_arms(char *);

extern void electric_orb_draw_ball(char *);

extern void electric_orb_update_trails(char *);

/* Draws the electric orb effect by running its three drawing steps in order. */
void electric_orb_draw(char *moby) {
    electric_orb_draw_arms(moby);
    electric_orb_draw_ball(moby);
    electric_orb_update_trails(moby);
}

/* func_L20_0039F268 is defined in L20_0039F268-g8.c (it reaches data through $gp and needs the qcopy profile). */

/* func_L20_0039F560 is defined in L20_0039F560-g8.c (it reaches data through $gp and needs the qcopy profile without interblock scheduling). */

/* func_L20_0039F968 is defined in L20_0039F968-g8.c. */


/* func_L20_003AB090 is defined in L20_003AB090.c. */

/* func_L20_003AB4A8 is defined in L20_003AB090.c. */




/* Lowers every object of a group by 20 units, hides them, and remembers their old heights. */
void group_lower_save_heights(char *moby) {
    s32 index = *(s32 *)(*(char **)(moby + 0x68));
    u16 *idList = (u16 *)D_L20_001FBB20[index];

    if (idList != 0) {
        char *base = D_L20_001B2F9C;
        f32 twenty = 20.0f;
        f32 *savedZ = D_L20_0023E670;

        do {
            u16 entry = *idList;
            char *member = base + ((entry & 0x7FFF) << 8);

            *savedZ = *(f32 *)(member + 0x18);
            savedZ++;
            *(u16 *)(member + 0x34) |= 0x41;
            *(f32 *)(member + 0x18) = *(f32 *)(member + 0x18) - twenty;
        } while (*(s16 *)idList++ >= 0);
    }
}

extern float IntToFloat(int);

extern float cubic_hermite_scalar(float, float, float, float, float);

/* Lifts a group of objects back from their lowered height as a timer runs, then shows them again. */
void group_raise_from_saved_heights(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    u16 *idList = (u16 *)D_L20_001FBB20[*(s32 *)vars];
    f32 *savedZ;
    char *base;
    f32 scale;

    if (idList == 0) {
        return;
    }
    {
        f32 progress = IntToFloat(*(s32 *)(vars + 4)) * *(f32 *)(vars + 8);
        scale = cubic_hermite_scalar(-1.0f, 0.0f, 1.0f, 0.0f, 1.0f - progress);
    }
    savedZ = D_L20_0023E670;
    base = D_L20_001B2F9C;
    do {
        f32 oldZ = *savedZ;
        u16 entry = *idList;
        char *member = base + ((entry & 0x7FFF) << 8);
        f32 lowZ = oldZ - 20.0f;

        savedZ++;
        *(u16 *)(member + 0x34) &= 0xFFBE;
        *(f32 *)(member + 0x18) = lowZ + (oldZ - lowZ) * scale;
    } while (*(s16 *)idList++ >= 0);
}

/* func_L20_003E6728 is defined in L20_003E6728.c. */



/* func_L20_00409480 is defined in L20_00409480-g8.c (it needs the -G8 profile). */

/* func_L20_004095D0 is defined in L20_0039C448-g8.c (this unit has no $gp access for it). */

extern s32 path_check_entry_for_moby(char *, s32);

extern f32 vec_distance_xy(void *, void *);

extern char *D_L20_001FEC80[];

/* Tells whether this object is done or close enough to its goal point. */
s32 moby_is_near_goal_point(char *mobyIn, s32 tableId) {
    char *moby = mobyIn;
    s32 id = tableId;
    char *vars;
    s32 result;
    f32 distance;

    vars = *(char **)(moby + 0x68);
    result = path_check_entry_for_moby(moby, id);
    if (result == 0) {
        if (id != -1) {
            distance = vec_distance_xy(moby + 0x10,
                               D_L20_001FEC80[id] + ((*(s16 *)(vars + 0x1CA) << 4) + 0x10));
            if (!(*(f32 *)(vars + 0x134) > distance)) {
            } else {
                result = 1;
            }
        }
    }
    return result;
}


/* func_L20_004395B0 is in L20_0039C448-g8.c (it reads three floats through $gp); its
   near miss is in nonmatching/levels/func_L20_004395B0.c. */
/* func_L20_0043D470 is defined in L20_0039C448-qcopy.c (its copy needs the grouped-copy profile). */

/* func_L20_0043D4D8 is defined in L20_0043D4D8.c. */
