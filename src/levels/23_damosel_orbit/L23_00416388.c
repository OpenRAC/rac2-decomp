#include "include_asm.h"
#include "names.h"

typedef signed short s16;

typedef unsigned short u16;

typedef signed int s32;

typedef unsigned long long u64;

/* func_L23_00416388 is matched in L23_00416388-boss-g8.c. */

/* func_L23_004177F8 is matched in L23_004177F8-g8.c. */

extern int math_fast_float_d(char *);

extern int FastDecTimer(char *);

/* Refreshes two measured state pairs and advances the two counters under their limits. */
void mothership_tick_timers(char *moby) {
    char *state = *(char **)(moby + 0x68);

    math_fast_float_d(state + 0x348);
    FastDecTimer(state + 0x34C);
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    if (*(s32 *)(state + 0x5AC) <= 0xFFFE)
        *(s32 *)(state + 0x5AC) = *(s32 *)(state + 0x5AC) + 1;
}

/* func_L23_00418160 is matched in L23_00418160-g8.c. */

/* func_L23_004183F0 is matched in L23_004183F0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00418650 is matched in L23_00418650.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_004186D0 is matched in L23_004186D0-g8.c. */

/* func_L23_00418BC8 is matched in L23_00418BC8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00418DC0 is matched in L23_00418DC0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern s32 mothership_is_value_not_in_slots(s32 arg0);

/* Collects the set bits of the mask whose index the shared predicate accepts. */
s32 mothership_collect_masked_path_indices(char *moby, u64 mask, s32 *outIndices, s32 checkPredicate) {
    s32 count = 0;
    s32 *out = outIndices;
    s32 i;

    for (i = 0; i < 0x40; i++) {
        if ((mask & 1) != 0 && (checkPredicate == 0 || mothership_is_value_not_in_slots(i) != 0)) {
            *out = i;
            count++;
            out++;
        }
        mask >>= 1;
    }
    return count;
}

extern s32 math_get_mask_bit(u64, s32);

extern int *g_path_lists[];

extern char g_path_end_masks[];

/* Returns 0 when bit arg of the slot's first mask is set; otherwise tests the second mask and
   returns the slot's count minus one. */
s32 mothership_test_path_end_mask(char *moby, s32 index, s32 arg) {
    s32 *slots = (s32 *)(*(char **)(moby + 0x68) + 0x230);
    s32 *slot = &slots[index];
    s32 slotId;
    s32 lastIndex;

    if (math_get_mask_bit(*(u64 *)(g_path_end_masks + (*slot << 4)), arg) != 0)
        return 0;
    slotId = *slot;
    lastIndex = *g_path_lists[slotId] - 1;
    math_get_mask_bit(*(u64 *)(g_path_end_masks + (slotId << 4) + 8), arg);
    return lastIndex;
}

/* Shifts a 64-bit value right by a variable count and keeps its lowest bit. */
s32 math_get_mask_bit(u64 value, s32 shift) { return (s32)((value >> shift) & 1); }

/* Advances the three-slot ring at +0x398, storing the previous value of +0x394. */
void mothership_push_path_history(char *moby, s16 newValue) {
    char *state = *(char **)(moby + 0x68);
    s16 ringPos = *(s16 *)(state + 0x39E);
    u16 oldValue = *(u16 *)(state + 0x394);
    int byteOffset;
    int nextPos;

    nextPos = (ringPos + 1) % 3;
    byteOffset = nextPos * 2;
    *(s16 *)(state + 0x39E) = nextPos;
    *(s16 *)(state + byteOffset + 0x398) = oldValue;
    *(s16 *)(state + 0x394) = newValue;
}

/* func_L23_004190C8 is defined in L23_004190C8-g8.c. */

/* func_L23_004196B8 is matched in L23_004196B8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00419970 is matched in L23_00416388-scan.c. */

/* One when exactly one bit of the mask is set and the shared predicate rejects its index. */
s32 mothership_is_single_rejected_bit(u64 mask) {
    s32 count = 0;
    s32 found = 0;
    s32 i = 0;

    do {
        if (mask & 1) {
            count++;
            if (count >= 2)
                return 0;
            found = i;
        }
        i++;
        mask >>= 1;
    } while (i < 0x40);

    if (count == 0)
        return 0;
    if (count == 1) {
        if (mothership_is_value_not_in_slots(found) == 0)
            return 1;
    }
    return 0;
}

/* func_L23_00419D60 is defined in L23_00419D60-g8.c. */

/* func_L23_0041A038 is matched in L23_0041A038-g8.c. */

/* func_L23_0041A3B8 is defined in L23_0041A3B8-g8.c. */

/* func_L23_0041A7A0 is matched in L23_0041A7A0-g8.c. */

/* func_L23_0041AFE8 is matched in L23_0041AFE8-g8.c (built with -fno-sched-interblock). */

/* func_L23_0041B188 is matched in L23_0041B188-g8.c. */

extern void module_l00_call_handler(void);

/* Calls the measured shared helper and reports success. */
/* Does nothing but call a shared helper and report that it worked. */
s32 mothership_call_helper_return_true(void) {
    module_l00_call_handler();
    return 1;
}

extern float math_fabs(float);

/* Relatches the first measure when the incoming one has moved at least a tenth away. */
void mothership_relatch_first_measure(char *moby, float *newMeasure) {
    char *state = *(char **)(moby + 0x68);

    if (!(math_fabs(*(float *)(state + 0x5D0) - *newMeasure) < 0.1f)) {
        *(float *)(state + 0x5D0) = *newMeasure;
        *(s32 *)(state + 0x5CC) = 0;
        *(s32 *)(state + 0x5DC) = 0;
    }
}

/* Clears three words of the state at +0x68. */
void mothership_clear_measure_flags(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(s32 *)(state + 0x5CC) = 0;
    *(s32 *)(state + 0x5C8) = 0;
    *(s32 *)(state + 0x5DC) = 0;
}

/* Returns the new value in $f0. Declared void, the call leaves $f0 free and the measure
 * reloaded right after it takes $f0 where retail has $f1. */
extern float math_step_value_toward_target(float *, float *, float, float, float, float);

/* Springs the second measure toward its target, doubles the word at +0x74, and latches the
 * measure once it is within a tenth of the target. */
void mothership_spring_second_measure(char *moby) {
    char *state = *(char **)(moby + 0x68);

    if (*(s32 *)(state + 0x5D8) != 0)
        return;
    math_step_value_toward_target((float *)(state + 0x588), (float *)(state + 0x58C), *(float *)(state + 0x5D4),
                  0.016666668f, 0.016666668f, 0.40833336f);
    *(float *)(state + 0x74) *= 2.0f;
    if (math_fabs(*(float *)(state + 0x588) - *(float *)(state + 0x5D4)) < 0.1f) {
        *(s32 *)(state + 0x5D8) = 1;
        *(s32 *)(state + 0x58C) = 0;
    }
}

/* The same relatch as the first measure, for the second one and its own flags. */
void mothership_relatch_second_measure(char *moby, float *newMeasure) {
    char *state = *(char **)(moby + 0x68);

    if (!(math_fabs(*(float *)(state + 0x5D4) - *newMeasure) < 0.1f)) {
        *(float *)(state + 0x5D4) = *newMeasure;
        *(s32 *)(state + 0x58C) = 0;
        *(s32 *)(state + 0x5D8) = 0;
    }
}

/* func_L23_0041B6D8 is matched in L23_0041B6D8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */


/* func_L23_0041B9F0 is defined in L23_0041B9F0-g8.c. */


/* func_L23_0041C0E8 is defined in L23_00416388-g8.c (it reads $gp data). */

/* func_L23_0041C578 is defined in L23_00416388-g8.c (it reads $gp data). */

/* func_L23_0041C6B0 is matched in L23_0041C6B0-g8.c (built with -frac2-qcopy). */

/* func_L23_0041C7D8 is matched in L23_00416388-g8.c */

/* The same table and counters func_L23_0041CCC0 clears below, declared the same way. */
extern s32 D_L23_001B3744 __attribute__((sda));

extern s32 D_L23_001B3738[3] __attribute__((sda));

extern s32 g_effect_pools[3][60];

typedef int TI128 __attribute__((mode(TI)));

extern char *SpawnLinkedScaledObject(char *, TI128 *, s32, float);

extern char *linked_scaled_object_spawn_spin_shrink(char *, TI128 *, s32, float);

extern char *linked_scaled_object_spawn_spinning_effect(char *, TI128 *, s32, float);

/* Spawns an object of kind TYPE at POS in the first free slot of its row, counts it, and gives
 * it the position as it was on entry. Returns the slot index, or -1 when the row is full.
 * The do-while (0) around the first copy leaves loop notes after it, which the schedulers treat
 * as a barrier (the lever of func_00124818): the argument copies and the 16-byte copy stay
 * ahead of the search, so $a0 is free for the 0xF0 factor and the object goes to $t0. Wrapping
 * the search instead doubles its reference weights, and local-alloc then gives the first word
 * $v0 ahead of the table address. The vector is kept in memory (a TI128 local is kept in a
 * register pair across the calls), and the table pointer is read back by D[type][i]. */
s32 part_spawn_effect_in_free_slot(char *obj, TI128 *pos, s32 type, s32 effectArg) {
    float saved[4] __attribute__((aligned(16)));
    char *slot;
    s32 i;

    do {
        *(TI128 *)saved = *pos;
    } while (0);
    for (i = 0; i < 50; i++) {
        if (g_effect_pools[type][i] == 0)
            break;
        if (i == 49) {
            i = -1;
            break;
        }
    }
    if (i != -1) {
        switch (type) {
        case 0:
            g_effect_pools[type][i] = (s32)SpawnLinkedScaledObject(obj, pos, effectArg, 4.0f);
            break;
        case 1:
            g_effect_pools[type][i] = (s32)linked_scaled_object_spawn_spin_shrink(obj, pos, effectArg, 3.65f);
            break;
        case 2:
            g_effect_pools[type][i] = (s32)linked_scaled_object_spawn_spinning_effect(obj, pos, effectArg, 3.65f);
            break;
        }
        slot = (char *)g_effect_pools[type][i];
        if (slot != 0) {
            D_L23_001B3744++;
            D_L23_001B3738[type]++;
            *(TI128 *)(slot + 0x10) = *(TI128 *)saved;
        }
    }
    return i;
}

/* func_L23_0041CA58 is defined in L23_0041CA58.c. */

/* The two sda declarations give retail's bare-symbol forms in this -G0 unit: the store through
 * $at and the unsplit address pair of the small array. */
extern s32 D_L23_001B3744 __attribute__((sda));

extern s32 D_L23_001B3738[3] __attribute__((sda));

extern s32 D_L23_001B1FA0[4];

extern s32 g_effect_pools[3][60];

/* Clears the three collected rows and their counts, then latches the two state counters.
 * The row pointer is taken after the count store: taken first, it trades the registers of
 * the 0xF0 factor and the count array; and an explicit row (rather than D[i][j] in the inner
 * loop) keeps the multiply ahead of the counter increment, so the counter stays in place. */
void part_reset_effect_pools(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 i, j;

    D_L23_001B3744 = 0;
    for (i = 0; i < 3; i++) {
        s32 *row;

        D_L23_001B3738[i] = 0;
        row = g_effect_pools[i];
        for (j = 0x31; j >= 0; j--)
            row[j] = 0;
    }
    D_L23_001B1FA0[3] = *(s16 *)(state + 0x2FE);
    D_L23_001B1FA0[2] = *(s16 *)(state + 0x2FA);
    D_L23_001B1FA0[0] = 0;
    D_L23_001B1FA0[1] = 0;
}

/* func_L23_0041CD58 is matched in L23_0041CD58-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_0041D0A0 is matched in L23_0041D0A0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_0041D1F0 is matched in L23_0041D1F0-g8.c (built with -fno-gcse). */

/* func_L23_0041D398 is matched in L23_0041D398-g8.c. */

/* func_L23_0041DA48 is matched in L23_00416388-hud-g16.c (built with -G16 -g). */

/* A three-label switch, the third one sharing the default's body (the recipe of
 * func_L22_003A65E0): with only two cases cc1 emits a comparison chain, and the third label is
 * what makes it build the decision tree rooted on 0xE3B. */
/* Returns a size value from the moby private data, picked by its object class. */
float moby_get_scale_by_class(char *moby) {
    switch (*(s16 *)(moby + 0xAA)) {
    case 0xE3A: /* moby class 3642 */
        return *(float *)(*(char **)(moby + 0x68) + 0x2C);
    case 0xE3B: /* moby class 3643 */
        return *(float *)(*(char **)(moby + 0x68) + 0x44);
    case 0xE3C: /* moby class 3644 */
    default:
        return *(float *)(*(char **)(moby + 0x68) + 0x44);
    }
}
