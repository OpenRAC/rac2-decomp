#include "include_asm.h"
#include "names.h"

/* func_L12_00413CE0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

extern u16 *D_L12_001FB960[];

/* The path-follower state of an entity: the record fields the nearest-entity hand-over touches. */
typedef struct {
    u8 pad00[0x2B0];
    s32 f2B0;
    s32 f2B4;
    s32 f2B8;
    s32 f2BC;
    s32 f2C0;
    u8 pad2C4[0x2D0 - 0x2C4];
    s32 f2D0;
    s32 f2D4;
    u8 pad2D8[0x2DC - 0x2D8];
    s32 f2DC;
    u16 f2E0;
    u8 pad2E2[0x2EA - 0x2E2];
    u8 f2EA;
    u8 pad2EB[0x302 - 0x2EB];
    u8 f302;
    u8 f303;
} PathState;

extern u8 *D_L12_001B2E9C_base[3] __asm__("D_L12_001B2E9C") __attribute__((sda));

extern s32 D_L12_001B2EB8;

extern u16 D_L12_001B1840_h __asm__("D_L12_001B1840") __attribute__((sda));

extern u8 *D_L12_001FEAC0[];

extern f32 func_00282E80(void *a, void *b);

/* Hands the object's path state to the nearest eligible entity of its group. */
void func_L12_00413CE0(u8 *moby)
{
    PathState *state = *(PathState **)(moby + 0x68);
    u8 *bestEntity;
    f32 bestDistance;
    f32 origin[4];
    u16 *entry;
    u8 *entity;
    PathState *entityState;
    f32 distance;

    if (state->f2C0 != -1) {
        *(TI128 *)origin = *(TI128 *)(D_L12_001FEAC0[state->f2C0] + 0x10);
        bestEntity = 0;
        bestDistance = 100000.0f;
        for (entry = D_L12_001FB960[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= D_L12_001B2EB8 && entry != 0 &&
             ((entry != 0 && (s16)entry[-1] >= 0) || entry == D_L12_001FB960[moby[0x21]]);
             entry++) {
            entity = D_L12_001B2E9C_base[0] + ((*entry & 0x7FFF) << 8);
            if (entity == 0)
                break;
            entityState = *(PathState **)(entity + 0x68);
            distance = vec_distance_xy(entity + 0x10, origin);
            if (entityState != 0 && (entityState->f302 & 1)) {
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestEntity = entity;
                }
            }
        }
        if (bestEntity != 0) {
            PathState *target = *(PathState **)(bestEntity + 0x68);

            target->f2B0 = state->f2B0;
            target->f2B4 = state->f2B4;
            target->f2B8 = state->f2B8;
            target->f2BC = state->f2BC;
            target->f2C0 = state->f2C0;
            target->f2D0 = state->f2D0;
            target->f2D4 = state->f2D4;
            target->f2E0 = D_L12_001B1840_h;
            target->f2DC = state->f2C0;
            target->f2EA = 1;
            target->f302 = 2;
            target->f303 = state->f303;
        }
    }
}
