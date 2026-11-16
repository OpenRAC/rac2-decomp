#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void group_destroy_attached_parts(char *, char *);
extern void SetDeathBits_pal(char *, int, int);
extern void matrix_mul_vec3(TI128 *, TI128 *, char *);
extern void FastVecAdd(TI128 *, TI128 *, char *);
extern unsigned char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int,
                                    int, int, void *);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(TI128 *, TI128 *, float);
extern void part_spawn_masked_debris_pal(char *, int, TI128 *, float, float, float, float, int);

/* Kills a climbing enemy: detaches its parts, spawns an explosion and a sound, and throws debris. */
void climbing_enemy_die_pal(char *moby)
{
    char *vars;
    TI128 spawn_pos[1];
    TI128 velocity;

    vars = *(char **)(moby + 0x68);
    group_destroy_attached_parts(moby, vars + 0x300);
    SetDeathBits_pal(moby, 0, 3);
    spawn_pos[0] = 0;
    ((float *)spawn_pos)[2] = 0.75f;
    matrix_mul_vec3(spawn_pos, spawn_pos, moby + 0xC0);
    FastVecAdd(spawn_pos, spawn_pos, moby + 0x10);
    SpawnExplosion_pal(spawn_pos, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, 0);
    PlayMobySound(6, 0, moby);
    vec_scale_to_length(&velocity, vars + 0x1C0, 0.060000002f);
    part_spawn_masked_debris_pal(moby, 1016, &velocity, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}
