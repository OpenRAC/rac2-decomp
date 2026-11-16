#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;

/* Level 08 data.  tools/build.py binds D_L08_XXXXXXXX at its address in level 08, and the
   `sda` declaration is what makes cc1 emit the one-instruction form the assembler can turn
   into `lw $v,offs($gp)` at a site inside a `.set nomacro` region (a compiler delay slot). */
extern s32 g_moby_array __attribute__((sda));

extern char *func_32A170(s32 a, s32 b, s32 c);
extern void func_328A38(s32 a, s32 b);

/* func_L08_00423970 is isolated in L08_00423970-g8.c. */

/* Walks the 0x68 context's two counters: one stamps the record's byte 0x20D and the other
   gives the modulus the first is folded by, or zero when it is not positive. */
/* Passes the turn to the next member of the creature's group. */
void group_advance_turn(char *moby) {
    char *vars;
    s32 groupSize;
    if (*(u8 *)(moby + 0x21) == 0xFF) {
        return;
    }
    vars = *(char **)(moby + 0x68);
    if (*(u8 *)(vars + 0x20D) == *(s32 *)(*(char **)(vars + 0x1F8))) {
        *(s32 *)(*(char **)(vars + 0x1F8)) = *(u8 *)(vars + 0x20D) + 1;
    }
    groupSize = *(s32 *)(*(char **)(vars + 0x1FC));
    if (groupSize > 0) {
        *(s32 *)(*(char **)(vars + 0x1F8)) = *(s32 *)(*(char **)(vars + 0x1F8)) % groupSize;
    } else {
        *(s32 *)(*(char **)(vars + 0x1F8)) = 0;
    }
}

/* func_L08_00424FF8 is isolated in L08_00423970-spawn.c. */

/* Not C: the success arm is the single word 0x4600A028 (COP1 fmt=S funct=0x28,
   fd=$f0 fs=$f0 ft=$f20). See nonmatching/levels/func_L08_00425328.c - this cc1 has no
   max.s pattern, so the ternary and the if-assignment both come out eight bytes larger. */


/* Stops the sounds this creature is playing and marks it as finished. */
void creature_release_sounds(char *moby) {
    char *vars;
    vars = *(char **)(moby + 0x68);
    if (*(u8 *)(moby + 0x21) != 0xFF) {
        func_328A38(*(u8 *)(moby + 0x21), 1);
    }
    if (*(s32 *)(vars + 0x224) != -1) {
        func_328A38(*(s32 *)(vars + 0x224), 1);
    }
    if (*(s32 *)(vars + 0x228) != -1) {
        func_328A38(*(s32 *)(vars + 0x224), 1);
    }
    *(u8 *)(moby + 0xBC) = 1;
}

/* Returns 1 when the moby with this handle is missing or gone, otherwise 0. */
s32 moby_handle_is_gone(s32 handle) {
    s32 table;
    s32 offset;
    s32 entry;
    table = g_moby_array;
    if (handle != -1) {
        offset = handle << 8;
        entry = table + offset;
        handle = 0;
        if (entry == 0 || *(u8 *)(entry + 0x20) == 0xFE || *(u8 *)(entry + 0x20) == 0xFD) {
            handle = 1;
        }
        return handle;
    }
    return 1;
}

/* Returns 1 when the moby with this handle is missing, gone, or past its early states, otherwise 0. */
s32 moby_handle_is_past_early_state(s32 handle) {
    s32 entry;
    s32 offset;
    u8 state;
    if (handle != -1) {
        offset = handle << 8;
        entry = g_moby_array;
        entry = entry + offset;
        state = *(u8 *)(entry + 0x20);
        handle = 0;
        if (state >= 3 || entry == 0 || state == 0xFE || state == 0xFD) {
            handle = 1;
        }
        return handle;
    }
    return 1;
}


extern f32 math_random_float_range(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern char g_hero_position[];

/* func_L08_00425628 is isolated in L08_00425628.c. */

extern void UpdateTaboraSwingTarget(char *);

/* The swing angle is folded into the moby's frame and the subobject is ticked. */
/* Picks a random spot around the creature (kept away from the hero), then picks its final target point. */
void creature_pick_random_target(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    f32 local[4];
    f32 minAngle = -3.1415927f;
    f32 maxAngle = 3.1415927f;
    f32 angle;

    angle = math_random_float_range(minAngle, maxAngle);
    *(f32 *)(vars + 0x180) = math_fast_sin_or_cos_a(angle) * (f32)*(u8 *)(vars + 0x20F);
    angle = math_random_float_range(minAngle, maxAngle);
    *(f32 *)(vars + 0x184) = math_fast_sin_or_cos_b(angle) * (f32)*(u8 *)(vars + 0x20F);
    *(f32 *)(vars + 0x188) = 0.0f;
    FastVecAdd(vars + 0x180, vars + 0x180, vars + 0x170);
    *(f32 *)(vars + 0x188) = *(f32 *)(vars + 0x188) + 6.5f;
    if (*(s16 *)(vars + 0x1B6) != 0) {
        FastVecSub(local, vars + 0x180, (void *)g_hero_position);
        *(s32 *)&local[2] = 0;
        vec_scale_to_length(local, local, 3.0f);
        FastVecAdd(vars + 0x180, vars + 0x180, local);
    }
    UpdateTaboraSwingTarget(moby);
}

extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 math_closest_point_on_polygon_edge(void *, void *, void *, s32);
extern int *g_path_list_table[];

/* The actor's per-frame world transform: the record's own position goes through the
   model's matrix, is scaled, and is folded into the model; when the actor names a part,
   the part's table entry replaces it, and the model's own length ends up in the radius. */
/* Works out the spot the creature aims at, bent around its leader when close, and shifts it by the path points. */
void creature_compute_aim_point(char *moby) {
    f32 offset[4];
    f32 ownOffset[4];
    f32 sideways[4];
    f32 bend[4];
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    s32 idx;

    idx = *(s32 *)(vars + 0x1E8);
    if (idx == -1) {
        FastVecSub(offset, self + 0x10, vars + 0x120);
        vec_scale_to_length(offset, offset, 15.0f);
        offset[2] = 0.0f;
        FastVecAdd(vars + 0x180, offset, vars + 0x120);
    } else {
        s32 base = g_moby_array + (idx << 8);

        FastVecSub(offset, (char *)base + 0x10, vars + 0x120);
        offset[2] = 0.0f;
        if (FastVecLength(offset) < 9.0f) {
            FastVecSub(ownOffset, self + 0x10, vars + 0x120);
            ownOffset[2] = 0.0f;
            vec_scale_to_length(ownOffset, ownOffset, 15.0f);
            FastVecAdd(vars + 0x180, ownOffset, vars + 0x120);
            FastVecCross(sideways, offset, ownOffset);
            FastVecCross(bend, offset, sideways);
            vec_scale_to_length(bend, bend, 1.0f);
            FastVecAdd(vars + 0x180, vars + 0x180, bend);
        } else {
            vec_scale_to_length(offset, offset, 15.0f);
            FastVecAdd(vars + 0x180, offset, vars + 0x120);
        }
    }
    idx = *(s32 *)(vars + 0x1E4);
    if (idx != -1) {
        int *list = g_path_list_table[idx];

        math_closest_point_on_polygon_edge(vars + 0x180, vars + 0x180, (char *)list + 0x10, *list);
    }
    *(f32 *)(vars + 0x188) = *(f32 *)(vars + 0x1C8);
}

/* func_L08_00425AA8 is isolated in L08_00425AA8.c. */

/* Halves the size of the linked effect when it belongs to one of four certain kinds of moby. */
void moby_halve_linked_scale(char *moby) {
    char *link;
    char *target;
    s16 classId;
    link = func_32A170((s32)moby, -1, 1);
    if (link == 0) {
        return;
    }
    target = *(char **)(link + 0x20);
    if (target == 0) {
        return;
    }
    classId = *(s16 *)(target + 0xAA);
    if (classId == 0xA66 /* moby class 2662 */ || classId == 0xA82 /* moby class 2690 */ ||
        classId == 0xCBB /* moby class 3259 */ || classId == 0xCF3 /* moby class 3315 */) {
        *(f32 *)(link + 0x2C) = *(f32 *)(link + 0x2C) * 0.5f;
    }
}

extern void moby_update_ground_probe(char *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];

/* The record's whole per-frame pass: the sibling step, the aim vector copied out of the
   sub-object, the shared sprite pass, then the dispatch the shared tag call returns. */
/* Runs the creature's body each frame and reacts to hits: pushes it back, and cleans up on death. */
void creature_update_hit_reaction(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int hitResult;

    moby_update_ground_probe(moby);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(char **)(moby + 0x24) + 0x24);
    moby_halve_linked_scale(moby);
    hitResult = moby_apply_damage_to_object(moby, vars + 0x50, 0);
    if (hitResult == 0) {
        return;
    }
    if (hitResult == 1) {
        float push[4];

        FastVecSub(push, moby + 0x10, g_hero_position);
        vec_scale_to_length(vars + 0x1A0, push, 0.16666667f);
    } else {
        if (hitResult == 4) {
            *(unsigned char *)(vars + 0xC6) = 0;
            *(s32 *)(vars + 0xCC) = -1;
        }
        group_advance_turn(moby);
    }
    creature_release_sounds(moby);
}

/* func_L08_00425FE8 is isolated in L08_00425FE8.c. */

/* Collision sweep and movement update are in L08_00423970-motion.c. */

/* func_L08_00426730 is isolated in L08_00423970-state.c. */

/* func_L08_00429238 is isolated in L08_00429238.c. */


extern s32 g_beam_slot_state[];
extern s32 g_beam_start_light_ids[];
extern s32 g_beam_end_light_ids[];
extern s32 g_beam_slot_key[];
extern void gfx_free_point_light(s32 a0);

/* func_L08_004290E8 is isolated in L08_004290E8.c. */

/* func_L08_004294A0 is isolated in L08_004294A0.c. */

/* func_L08_00429560 is isolated in L08_00429560-g8.c. */

/* func_L08_00429EE8 is isolated in L08_00429EE8.c. */


/* func_L08_0042A980 is isolated in L08_0042A980-g64.c. */
