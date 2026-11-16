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
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
extern void part_spawn_scaled_bolts_pal(char *, int, f32);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern int math_fast_float_d(char *);
extern void moby_mark_spawned(char *);

void func_PAL_L20_003A328C(char *arg0) {
    char *s0 = arg0;
    char *s1;
    f32 buf[4];
    f32 f20;
    f32 f21;
    int v0;

    s1 = *(char **)(s0 + 0x68);

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        moby_set_state(s0, 1, -1);
        break;
    case 1:
        v0 = part_find_owned_effect_slot(s0, 0x04010000, 0);
        if (v0 == 0) {
            v0 = 0xFF;
        } else if (*(int *)s1 != 0) {
            v0 = 0xFF;
        } else {
            moby_set_state(s0, 2, -1);
            break;
        }
        *(u8 *)(s0 + 0xA8) = v0;
        v0 = *(int *)(s1 + 4);
        if (v0 <= 0) {
            break;
        }
        v0 = (int)((char *)D_L20_001B2F9C_1 + (v0 << 8));
        if (v0 == 0) {
            break;
        }
        {
            s32 mode = *(u8 *)(v0 + 0x20);
            if (mode == 0xFE) goto changeState;
            if (mode == 0xFD) goto changeState;
            if (mode != 3) break;
        changeState:
            moby_set_state(s0, 2, -1);
        }
        break;
    case 2:
        f20 = 0.0f;
        f21 = 3.0f;
        vec_local_offset_to_world(s0, (char *)buf, f20, f20, f21);
        if (*(u8 *)(s0 + 0x31) != 0 && g_burst_trigger_progress < 0.9f) {
            SpawnExplosionEffects_pal(s0, g_effect_color_table, buf, f20, f20, 10, 3, 16,
                          1.0f, 0.5f, 9.0f, *(f32 *)(s0 + 0x2C) * 1.3f, -1, 15.0f,
                          0, 1, -1, 0, 0);
            func_PAL_002B15D8(s0, 1, (float *)D_L20_001A8F20_1, f21, 6.0f, f21, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(s0, 1, (float *)D_L20_001A8F20_1, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(s0, 1, 0.0f);
        PlayMobySound(0, 0, s0);
        moby_set_state(s0, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(s0) != 0) {
            *(u16 *)(s0 + 0x34) |= 1;
            *(u32 *)(s0 + 0x98) = 0;
            *(u8 *)(s0 + 0x31) = 0;
            *(u32 *)(s1 + 8) = 0x64;
        }
        if (math_fast_float_d(s1 + 8) != 0) {
            moby_mark_spawned(s0);
        }
        break;
    }
}
