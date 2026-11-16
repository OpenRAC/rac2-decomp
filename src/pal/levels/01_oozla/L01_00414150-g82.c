#include "include_asm.h"

#include "common.h"
extern s32 g_oozla_intro_timer SDATA(D_L01_001AEC38);
extern s32 D_L01_001AEC38_1 __asm__("D_L01_001AEC38");
extern s32 g_breakable_count SDATA(D_L01_001B3468);
extern s32 D_L01_001B3468_1 __asm__("D_L01_001B3468");
extern float g_breakable_alpha_check_a __attribute__((sda));
extern float g_breakable_alpha_check_b __attribute__((sda));
extern s32 g_breakable_active_limit __attribute__((sda));
extern char g_zero_l01_vector[] NOT_SDA;
extern s32 math_fast_float_d(char *);
extern void moby_mark_spawned(char *);
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern void part_spawn_masked_debris_pal(char *, s32, char *, float, float, float, float, s32);
extern s32 flag_set_first_pending(char *);
extern int PlayMobySound(s32, s32, char *);
extern void part_spawn_scaled_bolts_pal(char *, s32, float);
typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;

/* Basic breakable object: waits for a hit, scatters debris and bolts, then hides and deletes itself after a short count (PAL copy). */
void breakable_object_update_basic_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        D_L01_001B3468_1 = 0;
        g_oozla_intro_timer = g_oozla_intro_timer + 1;
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) != 0 && *(s32 *)vars == 0) {
            g_oozla_intro_timer = D_L01_001AEC38_1 - 1;
            moby_set_state(moby, 2, -1);
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        if (*(u8 *)(moby + 0x31) != 0 && g_breakable_alpha_check_a < 0.9f && g_breakable_alpha_check_b < 0.9f && g_breakable_count < g_breakable_active_limit)
            part_spawn_masked_debris_pal(moby, 0x7F, g_zero_l01_vector, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        else
            part_spawn_masked_debris_pal(moby, 0xD, g_zero_l01_vector, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        part_spawn_scaled_bolts_pal(moby, 4, 0.0f);
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
            count = D_L01_001B3468_1;
            retiring->flags = flags | 1;
            *(int *)(vars + 4) = 0x64;
            D_L01_001B3468_1 = count + 1;
        }
        if (math_fast_float_d(vars + 4) != 0) {
            g_breakable_count = g_breakable_count - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}
