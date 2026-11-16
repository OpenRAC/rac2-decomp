#include "include_asm.h"

#include "common.h"
extern char *D_L20_001B2F9C_1 __attribute__((sda));
extern float g_burst_trigger_progress __attribute__((sda));
extern char g_effect_color_table[];
extern char D_L20_001A8F20_1[];
extern void *part_find_owned_effect_slot(char *, int, int);
extern void moby_set_state(char *, int, int);
extern void vec_local_offset_to_world(char *, char *, f32, f32, f32);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void part_spawn_masked_debris_pal(char *, int, float *, float, float, float, float, unsigned char);
extern void part_spawn_scaled_bolts_pal(char *, int, f32);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern int math_fast_float_d(char *);
extern void moby_mark_spawned(char *);

/* Updates moby class 4890: waits for its trigger, puts out a burst of effects and a sound, then removes itself after a short timer (PAL). */
void triggered_l20_burst_update_pal(char *moby_arg) {
    char *moby = moby_arg;
    char *state;
    f32 offset[4];
    f32 zero;
    f32 three;
    int value;

    state = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        value = part_find_owned_effect_slot(moby, 0x04010000, 0);
        if (value == 0) {
            value = 0xFF;
        } else if (*(int *)state != 0) {
            value = 0xFF;
        } else {
            moby_set_state(moby, 2, -1);
            break;
        }
        *(u8 *)(moby + 0xA8) = value;
        value = *(int *)(state + 4);
        if (value <= 0) {
            break;
        }
        value = (int)((char *)D_L20_001B2F9C_1 + (value << 8));
        if (value == 0) {
            break;
        }
        {
            s32 mode = *(u8 *)(value + 0x20);
            if (mode == 0xFE) goto changeState;
            if (mode == 0xFD) goto changeState;
            if (mode != 3) break;
        changeState:
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        zero = 0.0f;
        three = 3.0f;
        vec_local_offset_to_world(moby, (char *)offset, zero, zero, three);
        if (*(u8 *)(moby + 0x31) != 0 && g_burst_trigger_progress < 0.9f) {
            SpawnExplosionEffects_pal(moby, g_effect_color_table, offset, zero, zero, 10, 3, 16,
                          1.0f, 0.5f, 9.0f, *(f32 *)(moby + 0x2C) * 1.3f, -1, 15.0f,
                          0, 1, -1, 0, 0);
            part_spawn_masked_debris_pal(moby, 1, (float *)D_L20_001A8F20_1, three, 6.0f, three, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris_pal(moby, 1, (float *)D_L20_001A8F20_1, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            *(u16 *)(moby + 0x34) |= 1;
            *(u32 *)(moby + 0x98) = 0;
            *(u8 *)(moby + 0x31) = 0;
            *(u32 *)(state + 8) = 0x64;
        }
        if (math_fast_float_d(state + 8) != 0) {
            moby_mark_spawned(moby);
        }
        break;
    }
}
