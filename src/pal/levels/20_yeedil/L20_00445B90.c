#include "include_asm.h"

#include "common.h"
extern u16 *D_L20_001FBB20[];
extern int D_L20_001B2FB8 __attribute__((sda));
typedef u8 ActorSlot[0x100];
extern ActorSlot *D_L20_001B2F9C __attribute__((sda));
typedef struct { u8 prefix[0x80]; float position[4]; } ResidentPoseView;
extern ResidentPoseView g_hero_state;
extern float mat_fast_helper_a(float, float);
extern void anim_start_immediate(s8 *, int, int);
extern void moby_set_state(void *, int, int);
extern void func_002A0F48(void *);
extern void vec_copy_helper_a(void *);
extern void FastVecCross(void *, const void *, const void *);
extern void vec_set_direction_with_complement(float *, float *, float);
extern void func_PAL_00273818(void *, int, int, const void *, const void *, unsigned char, float);

u8 *func_PAL_L20_00445B90(int group, const float position[4], const float velocity[4], float lifetime)
{
    float delta[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    u16 *entry;
    u8 *actor;
    u8 *state;
    u16 flags;

    for (entry = D_L20_001FBB20[group];
         (u8)group != 0xFF && group <= D_L20_001B2FB8 && entry != 0 &&
         ((s16)entry[-1] >= 0 || entry == D_L20_001FBB20[group]);
         ++entry) {
        actor = D_L20_001B2F9C[*entry & 0x7FFF];
        if (actor == 0)
            break;
        if (actor[0x20] == 6) {
            qcopy(actor + 0x10, position);
            *(float *)(actor + 0xF8) = mat_fast_helper_a(
                g_hero_state.position[0] - *(float *)(actor + 0x10),
                g_hero_state.position[1] - *(float *)(actor + 0x14));
            flags = *(u16 *)(actor + 0x34);
            flags = (flags & 0xFFBE) | 0x1000;
            *(u16 *)(actor + 0x34) = flags;
            *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
            *(u16 *)(actor + 0x34) = flags & 0xEFFF;
            anim_start_immediate((s8 *)actor, 7, 0);
            moby_set_state(actor, 7, 3);
            func_002A0F48(actor);
            vec_copy_helper_a(origin);
            FastVecCross(delta, origin, velocity);
            vec_set_direction_with_complement(delta, delta, 0.12566373f);
            state = *(u8 **)(actor + 0x68);
            *(u8 **)(actor + 0x68) = state + 0x210;
            func_PAL_00273818(actor, 3, 0, velocity, delta, 0xFF, 15.0f);
            *(u8 **)(actor + 0x68) = state;
            *(float *)(state + 0x288) = lifetime;
            {
                int cycle = *(int *)(*(u8 **)(actor + 0x24) + 0x10);
                u16 control = *(u16 *)(actor + 0x34) | 0x1000;
                *(int *)(actor + 0x9C) = 1;
                *(int *)(actor + 0x98) = cycle;
                *(u16 *)(actor + 0x34) = control;
            }
            return actor;
        }
    }
    return 0;
}

