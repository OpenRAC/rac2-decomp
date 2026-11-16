#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(Quad128 *, Quad128 *, char *);
typedef int TI128 __attribute__((mode(TI)));
extern void SetDeathBits_pal(char *, int, int);
extern void matrix_mul_vec3(TI128 *, TI128 *, char *);
extern void FastVecAdd(TI128 *, TI128 *, char *);
extern char *SpawnExplosion_pal(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(TI128 *, TI128 *, float);
extern void part_spawn_masked_debris_pal(char *, int, TI128 *, float, float, float, float, int);

/* func_L07_003EB838 is in L07_003EB838.c. */

/* Blows up the entity when it dies: sets its death bits, spawns an explosion and throws debris pieces. */
void entity_spawn_death_effects_b_pal(char *moby)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xefff;
    SetDeathBits_pal(moby, 0, 3);
    *(TI128 *)position = 0;
    position[2] = 0.75f;
    matrix_mul_vec3((TI128 *)position, (TI128 *)position, moby + 0xc0);
    FastVecAdd((TI128 *)position, (TI128 *)position, moby + 0x10);
    SpawnExplosion_pal((TI128 *)position, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f,
                 1, 0, 0, *(int *)(vars + 0x314));
    PlayMobySound(9, 0, moby);
    vec_scale_to_length((TI128 *)direction, (TI128 *)(vars + 0x1c0), 0.060000002f);
    part_spawn_masked_debris_pal(moby, 0x7f8, (TI128 *)direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xff);
}


extern void moby_set_state(int, int, int);
extern int math_random_int_range(int, int);
extern void *part_spawn_between_points_depth_push(char *, int, int, char *, int, int, int);
extern void moby_set_state(int, int, int);

/* Arm the object's mode ten and hand it to the shared launcher. */
void entity_launch_member_b_pal(char *moby, int from_pos, int to_pos, int owner, int flag)
{
    int life;

    moby_set_state(moby, 8, -1);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    life = ((s32)(math_random_int_range(0x2D, 0x4B)) * 5 + 2) / 6;
    part_spawn_between_points_depth_push(moby, from_pos, to_pos, moby + 0xF0, life, owner, flag);
}



