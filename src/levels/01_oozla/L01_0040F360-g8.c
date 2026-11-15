#include "common.h"


extern int D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern int counter_abs __asm__("D_L01_001AEC38");
extern int active_abs __asm__("D_L01_001B3468");
extern float D_L01_001B208C __attribute__((sda));
extern float D_L01_001B2090 __attribute__((sda));
extern int D_L01_001B15E0 __attribute__((nosda));
extern int D_L01_001B3468 SDATA(D_L01_001B3468);
extern void moby_set_state(char *, int, int);
extern int part_find_owned_effect_slot(char *, int, int);
extern void FastVecScale(char *, char *, float);
extern void part_spawn_masked_debris(char *, int, void *, float, float, float, float, int);
extern void part_spawn_scaled_bolts(char *, float, int);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern int moby_mark_spawned(char *);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
/* Update for a breakable object: counts itself, waits to be hit, bursts with a sound and retires after a timer. */
void breakable_object_update_burst(char *mobyArg)
{
    char *moby = mobyArg;
    char *vars = *(char **)(mobyArg + 0x68);
    float offset[4];
    int activeCount;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38 + 1;
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *(int *)vars == 0) {
            D_L01_001AEC38 = counter_abs - 1;
            moby_set_state(moby, 2, -1);
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        FastVecScale((char *)offset, moby + 0xD0, -0.06666667f);
        if (*(u8 *)(moby + 0x31) != 0 && D_L01_001B2090 < 0.9f &&
            D_L01_001B208C < 0.9f && (activeCount = D_L01_001B3468, activeCount < D_L01_001B15E0)) {
            part_spawn_masked_debris(moby, 0x1F, offset, 1.0f, 3.0f, 2.0f, 5.0f, 0xFF);
        } else {
            part_spawn_masked_debris(moby, 5, offset, 1.0f, 3.0f, 2.0f, 5.0f, 0xFF);
        }
        part_spawn_scaled_bolts(moby, 0.0f, 1);
        PlayMobySound(0, 0, moby);
        moby_set_state(moby, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            RetiringObject *retiring = (RetiringObject *)moby;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = active_abs;
            retiring->flags = flags | 1;
            *(int *)(vars + 4) = 0x78;
            active_abs = count + 1;
        }
        if (math_fast_float_d(vars + 4) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}

