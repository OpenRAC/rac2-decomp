#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(char *, char *, char *);
extern void make_hit_descriptor(char *, int, int, void *, float);
extern int CollLine(void *, void *, int, int, void *);
extern int math_fast_float_d(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void gfx_add_draw_callback_third(void *, int);
extern void EmitJitteredParticleTrail_pal(char *);
extern void part_l20_spawn_spark_burst_pal(char *, int, int);
extern void gfx_draw_projectile_trail(void);
extern void moby_mark_spawned(int);
extern char g_spark_position[];

/* Flies a shot forward each frame, checks what it hits, and on a hit makes sparks and removes the shot. (PAL version) */
void projectile_l20_update_pal(char *moby) {
    char *position = moby + 0x10;
    char *vars = *(char **)(moby + 0x68);
    char *velocity;
    char buf[0x30];

    *(TI128 *)vars = *(TI128 *)position;
    velocity = vars + 0x10;
    FastVecAdd(position, position, velocity);
    make_hit_descriptor(buf, (int)moby, 0x10001, velocity, *(float *)(vars + 0x2C));
    if (CollLine(vars, position, 0, *(int *)(moby + 0xB8), buf) != 0
        || math_fast_float_d(vars + 0x20) != 0) {
        part_l20_spawn_spark_burst_pal(g_spark_position, 0x14, 1);
        snd_play_from_class_bank(2, 0, moby, 0x12EF);
        moby_mark_spawned((int)moby);
    } else {
        EmitJitteredParticleTrail_pal(moby);
        gfx_add_draw_callback_third(gfx_draw_projectile_trail, (int)moby);
    }
}

extern char *CreateMoby(int);

/* Spawns an object of type 0x12F2 and fills its position and its sub-record vector. */
/* Creates a Yeedil shot at a position with a direction and a size, owned by another object. (PAL version) */
char *projectile_l20_spawn_pal(char *moby, char *position, char *direction, float radius) {
    char *vars;
    char *shot = CreateMoby(0x12F2);

    if (shot != 0) {
        *(int *)(shot + 0xB8) = (int)moby;
        *(TI128 *)(shot + 0x10) = *(TI128 *)position;
        vars = *(char **)(shot + 0x68);
        *(unsigned char *)(shot + 0x30) = 0xFF;
        *(TI128 *)(vars + 0x10) = *(TI128 *)direction;
        *(float *)(vars + 0x2C) = radius;
        *(int *)(vars + 0x20) = 0xFA;
    }
    return shot;
}
