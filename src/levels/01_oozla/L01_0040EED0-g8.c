#include "common.h"


extern int g_oozla_intro_timer SDATA(D_L01_001AEC38);
extern int counter_abs __asm__("D_L01_001AEC38");
extern int active_abs __asm__("D_L01_001B3468");
extern float g_breakable_alpha_check_b __attribute__((sda));
extern float g_breakable_alpha_check_a __attribute__((sda));
extern int g_breakable_active_limit __attribute__((nosda));
extern int g_breakable_count SDATA(D_L01_001B3468);
extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(char *, int, int);
extern void FastVecScale(char *, char *, float);
extern void part_spawn_masked_debris(char *, int, void *, float, float, float, float, int);
extern void part_spawn_scaled_bolts(char *, float, int);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern void moby_mark_spawned(char *);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
/* Update for a breakable object: counts itself, waits to be hit, bursts with a sound and retires after a timer. */
void breakable_object_update_timed(char *moby_arg)
{
    char *moby = moby_arg;
    char *vars = *(char **)(moby_arg + 0x68);
    float offset[4];
    int active_count;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        g_oozla_intro_timer = g_oozla_intro_timer + 1;
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *(int *)vars == 0) {
            g_oozla_intro_timer = counter_abs - 1;
            moby_set_state(moby, 2, -1);
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        FastVecScale((char *)offset, moby + 0xD0, -0.10000001f);
        if (*(u8 *)(moby + 0x31) != 0 && g_breakable_alpha_check_a < 0.9f &&
            g_breakable_alpha_check_b < 0.9f && (active_count = g_breakable_count, active_count < g_breakable_active_limit)) {
            part_spawn_masked_debris(moby, 0x3FF, offset, 1.0f, 3.0f, 2.0f, 4.0f, 0xFF);
        } else {
            part_spawn_masked_debris(moby, 0xF, offset, 1.0f, 3.0f, 2.0f, 4.0f, 0xFF);
        }
        part_spawn_scaled_bolts(moby, 0.0f, 4);
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
            g_breakable_count = g_breakable_count - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}

