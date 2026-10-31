/* Own unit, default game profile (-O2 -G0 -ffunction-sections).  It cannot share
 * L20_0043ECB0.c: that unit declares D_L20_001B2F9C as an unsigned int and
 * func_002A7750 with an int first argument, and the unsigned-int spelling of the
 * slot walk compiles to a different loop (488 bytes).  The group walk's last two
 * predicates are in retail's order: the previous entry's high bit first, then the
 * list head.
 */
#include "common.h"

extern u16 *D_L20_001FBB20[];
extern int D_L20_001B2FB8 __attribute__((sda));
typedef u8 ActorSlot[0x100];
extern ActorSlot *D_L20_001B2F9C __attribute__((sda));
typedef struct { u8 prefix[0x80]; float position[4]; } ResidentPoseView;
extern ResidentPoseView D_00189E20;
extern float func_00283248(float, float);
extern void func_002A7398(s8 *, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A0F48(void *);
extern void func_00282C98(void *);
extern void func_00282DD8(void *, const void *, const void *);
extern void func_002ACE78(float *, float *, float);
extern void func_00273978(void *, int, int, const void *, const void *, unsigned char, float);

u8 *func_L20_00440198(int group, const float position[4], const float velocity[4], float lifetime)
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
            *(float *)(actor + 0xF8) = func_00283248(
                D_00189E20.position[0] - *(float *)(actor + 0x10),
                D_00189E20.position[1] - *(float *)(actor + 0x14));
            flags = *(u16 *)(actor + 0x34);
            flags = (flags & 0xFFBE) | 0x1000;
            *(u16 *)(actor + 0x34) = flags;
            *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
            *(u16 *)(actor + 0x34) = flags & 0xEFFF;
            func_002A7398((s8 *)actor, 7, 0);
            func_002A7750(actor, 7, 3);
            func_002A0F48(actor);
            func_00282C98(origin);
            func_00282DD8(delta, origin, velocity);
            func_002ACE78(delta, delta, 0.10471977293491364f);
            state = *(u8 **)(actor + 0x68);
            *(u8 **)(actor + 0x68) = state + 0x210;
            func_00273978(actor, 3, 0, velocity, delta, 0xFF, 15.0f);
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
