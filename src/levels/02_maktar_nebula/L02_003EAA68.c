#include "include_asm.h"
#include "names.h"

/* func_L02_003EAA68 is a unit of its own: it needs the opt-in quadword-copy profile with its
   scheduling barrier and the clear's barrier (-frac2-qcopy -frac2-qcopy-barrier
   -frac2-zero-ti-barrier, config/cflags.txt). The zero clear at the top is retail's
   `sq $zero,0($sp)` followed at once by a reload of the group byte, and the entity's +0x10
   quadword reaches the +0x30 of its private data through register addresses; with the copy a
   barrier, retail's own statement order (copy, +0x3C, +0x28) keeps `state + 0x24` after the copy.
   D_L02_001B359C and D_L02_001B35B8 are `sda` arrays of unknown size read as [0]: bare-symbol
   loads, and the `$gp` form in the delay slot of the first walk's `beq`. */

typedef int TI128 __attribute__((mode(TI)));

extern unsigned short *D_L02_001FC060[];
extern char *D_L02_001B359C[] __attribute__((sda));
extern int D_L02_001B35B8[] __attribute__((sda));

extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);

/* Sets up the group of swing platforms that share the actor's group number,
   giving each a start position and state. */
void func_L02_003EAA68(unsigned char *actor) {
    char *state;
    float center[4];
    float off[4];
    int first;
    unsigned short *listEntry;
    char *entity;

    if (actor[0x21] == 0xFF)
        return;
    first = 0;
    state = *(char **)(actor + 0x68);
    *(TI128 *)center = 0;
    for (listEntry = gEntityGroupLists[actor[0x21]];
         actor[0x21] != 0xFF && actor[0x21] <= D_L02_001B35B8[0] && listEntry != 0 &&
         ((listEntry != 0 && (short)listEntry[-1] >= 0) || listEntry == gEntityGroupLists[actor[0x21]]);
         listEntry++) {
        entity = gMobyPool_L02[0] + ((*listEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (*(short *)(entity + 0xAA) == 0xAB0 /* moby class 2736 */) {
            char *entityVars = *(char **)(entity + 0x68);

            *(TI128 *)(entityVars + 0x30) = *(TI128 *)(entity + 0x10);
            *(float *)(entityVars + 0x3C) = *(float *)(actor + 0xF8);
            *(char **)(entityVars + 0x28) = state + 0x24;
            if (*(int *)entityVars != 0) {
                if (first == 0) {
                    *(int *)entityVars = 2;
                    first = 1;
                }
                FastVecAdd(center, center, entity + 0x10);
                entity[0x20] = 2;
            } else {
                entity[0x20] = 1;
            }
        }
    }
    FastVecScale(center, center, 0.5f);
    vec_scale_to_length(off, actor + 0xD0, 0.5f);
    off[2] -= 0.5f;
    for (listEntry = gEntityGroupLists[actor[0x21]];
         actor[0x21] != 0xFF && actor[0x21] <= D_L02_001B35B8[0] && listEntry != 0 &&
         ((listEntry != 0 && (short)listEntry[-1] >= 0) || listEntry == gEntityGroupLists[actor[0x21]]);
         listEntry++) {
        entity = gMobyPool_L02[0] + ((*listEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (*(short *)(entity + 0xAA) == 0xAB0 /* moby class 2736 */ && **(int **)(entity + 0x68) == 0) {
            ((unsigned char *)entity)[0x30] = 0xFF;
            *(float *)(entity + 0xF8) = FastAddRotations(*(float *)(entity + 0xF8), 1.5707965f);
            *(float *)(entity + 0xF0) = 3.1415927f;
            FastVecAdd(entity + 0x10, center, off);
            *(int *)(entity + 0x98) = 0;
            *(unsigned short *)(entity + 0x34) = (*(unsigned short *)(entity + 0x34) | 0x41) & 0xEFFF;
        }
    }
}
