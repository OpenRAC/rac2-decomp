#include "include_asm.h"
#include "common.h"

extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void moby_set_state(char *, int, int);
extern s32 part_spawn_damage_debris(char *, char *, char *);
extern void set_moby_color(void *, u8, u8, u8);

/* The func_L02_003F17B0 reset for the level-11 mover: the same turn rates, its own state
   layout, and the path follower (func_002B3380) restarted in place of the two child
   slots. */
void path_mover_reset(char *moby, int mode) {
    char *state = *(char **)(moby + 0x68);

    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(u16 *)(state + 0x256) = 0;
    *(u16 *)(state + 0x88) = 0;
    moby_set_controller_speed_limits((u8 *)moby, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    moby_set_state(moby, 3, 0);
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(moby + 0x31) = 1;
    *(u8 *)(moby + 0x7F) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x1000) & 0xFFB8;
    *(u16 *)(state + 0x258) = mode;
    *(int *)(state + 0x200) = 0;
    part_spawn_damage_debris(moby, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(moby, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}
