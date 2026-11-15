#include "common.h"
extern char *D_L20_001B2F9C_1 __attribute__((sda));

extern float D_L20_001B2ACC __attribute__((sda));

/* Retail materializes this vector address independently for the two effect
 * constructors. The two symbol views preserve those separate lifetimes. */
extern char D_L20_001A8F20[];
extern char D_L20_001A8F20_1[];

extern void *part_find_owned_effect_slot(char *, int, int);

extern void func_0032F5B0(char *, int, int);

extern void vec_local_offset_to_world(char *, char *, f32, f32, f32);

extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);

extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, unsigned char);

extern void part_spawn_scaled_bolts(char *, int, f32);

extern int PlayMobySound(int, int, char *);

extern int flag_set_first_pending(char *);

extern int math_fast_float_d(char *);

extern void moby_mark_spawned(char *);

/* Updates moby class 4890: waits for its trigger, puts out a burst of effects and a sound, then removes itself after a short timer. */
void triggered_l20_burst_update(char *moby_arg) {
    char *moby = moby_arg;
    char *vars;
    f32 effect_pos[4];
    f32 zero;
    f32 size;
    int value;

    vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        func_0032F5B0(moby, 1, -1);
        break;
    case 1:
        value = part_find_owned_effect_slot(moby, 0x04010000, 0);
        if (value == 0) {
            value = 0xFF;
        } else if (*(int *)vars != 0) {
            value = 0xFF;
        } else {
            func_0032F5B0(moby, 2, -1);
            break;
        }
        *(u8 *)(moby + 0xA8) = value;
        value = *(int *)(vars + 4);
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
            func_0032F5B0(moby, 2, -1);
        }
        break;
    case 2:
        zero = 0.0f;
        size = 3.0f;
        vec_local_offset_to_world(moby, (char *)effect_pos, zero, zero, size);
        if (*(u8 *)(moby + 0x31) != 0 && D_L20_001B2ACC < 0.9f) {
            SpawnExplosionEffects(moby, D_L20_001A8F20, effect_pos, zero, zero, 10, 3, 16,
                          1.0f, 0.5f, 9.0f, *(f32 *)(moby + 0x2C) * 1.3f, -1, 15.0f,
                          0, 1, -1, 0, 0);
            part_spawn_masked_debris(moby, 1, (float *)D_L20_001A8F20_1, size, 6.0f, size, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris(moby, 1, (float *)D_L20_001A8F20_1, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        func_0032F5B0(moby, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            *(u16 *)(moby + 0x34) |= 1;
            *(u32 *)(moby + 0x98) = 0;
            *(u8 *)(moby + 0x31) = 0;
            *(u32 *)(vars + 8) = 0x78;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            moby_mark_spawned(moby);
        }
        break;
    }
}
