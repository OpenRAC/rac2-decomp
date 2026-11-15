#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers,
   and the copy as the scheduling barrier the retail's inline-asm macro was. */
typedef int TI128 __attribute__((mode(TI)));

extern void FastVecAdd(char *, char *, char *);

extern void make_hit_descriptor(char *, int, int, void *, float);

extern int CollLine(void *, void *, int, int, void *);

extern int math_fast_float_d(void *);

extern void snd_play_from_class_bank(int, int, void *, int);

extern void gfx_add_draw_callback_third(void *, int);

extern void EmitJitteredParticleTrail(char *);

extern void part_l20_spawn_spark_burst(char *, int, int);

extern void gfx_draw_projectile_trail(void);

extern void moby_mark_spawned(int);

extern char D_L20_001C0420[];

/* Flies a shot forward each frame, checks what it hits, and on a hit makes sparks and removes the shot. */
void projectile_l20_update(char *moby) {
    char *position = moby + 0x10;
    char *vars = *(char **)(moby + 0x68);
    char *velocity;
    char hit_info[0x30];

    *(TI128 *)vars = *(TI128 *)position;
    velocity = vars + 0x10;
    FastVecAdd(position, position, velocity);
    make_hit_descriptor(hit_info, (int)moby, 0x10001, velocity, *(float *)(vars + 0x2C));
    if (CollLine(vars, position, 0, *(int *)(moby + 0xB8), hit_info) != 0
        || math_fast_float_d(vars + 0x20) != 0) {
        part_l20_spawn_spark_burst(D_L20_001C0420, 0x14, 1);
        snd_play_from_class_bank(2, 0, moby, 0x12EF);
        moby_mark_spawned((int)moby);
    } else {
        EmitJitteredParticleTrail(moby);
        gfx_add_draw_callback_third(gfx_draw_projectile_trail, (int)moby);
    }
}

/* Fills in the settings block of this object and copies one position vector into it. */
void object_fill_settings_block(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(f32 *)(*(char **)(state + 0x84) + 0x0) = 8.0f;
    *(f32 *)(*(char **)(state + 0x84) + 0x4) = 2.5f;
    *(u8 *)(*(char **)(state + 0x84) + 0x18) = 1;
    *(u16 *)(*(char **)(state + 0x84) + 0x1A) = 0;
    *(u8 *)(*(char **)(state + 0x84) + 0x1E) = 1;
    *(u8 *)(*(char **)(state + 0x84) + 0x1F) = 0;
    *(TI128 *)(*(char **)(state + 0x84) + 0x20) = *(TI128 *)(state + 0x60);
}
