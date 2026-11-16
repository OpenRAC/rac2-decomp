#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(Quad128 *, Quad128 *, char *);
typedef int TI128 __attribute__((mode(TI)));
extern void group_destroy_attached_parts(char *, char *);
extern void SetDeathBits_pal(char *, int, int);
extern void matrix_mul_vec3(TI128 *, TI128 *, char *);
extern void FastVecAdd(TI128 *, TI128 *, char *);
extern char *SpawnExplosion_pal(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(TI128 *, TI128 *, float);
extern void part_spawn_masked_debris_pal(char *, int, TI128 *, float, float, float, float, int);

/* Arm the object's mode, then set up its position and hand it to the launcher.
   func_PAL_002B15D8's integer mask is its last parameter, and this compiler sets the
   arguments up in parameter order: the mask's store then comes after the four
   float copies, in the call's delay slot, as the retail has it. */
void entity_spawn_death_effects_pal(char *moby)
{
    char *vars;
    TI128 local_pos[1];
    TI128 push_vel;

    vars = *(char **)(moby + 0x68);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    *(int *)(moby + 0x98) = 0;
    group_destroy_attached_parts(moby, vars + 0x330);
    SetDeathBits_pal(moby, 0, 3);
    local_pos[0] = 0;
    ((float *)local_pos)[2] = 0.75f;
    matrix_mul_vec3(local_pos, local_pos, moby + 0xC0);
    FastVecAdd(local_pos, local_pos, moby + 0x10);
    SpawnExplosion_pal(local_pos, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, *(int *)(vars + 0x338));
    PlayMobySound(6, 0, moby);
    vec_scale_to_length(&push_vel, vars + 0x1C0, 0.060000002f);
    part_spawn_masked_debris_pal(moby, 1016, &push_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}


extern void moby_set_state(int, int, int);
extern int math_random_int_range(int, int);
extern void *part_spawn_between_points_depth_push(char *, int, int, char *, int, int, int);
extern void moby_set_state(int, int, int);

/* Arm the object's mode ten and hand it to the shared launcher. */
void entity_launch_member_a_pal(char *moby, int from_pos, int to_pos, int owner, int flag)
{
    int life;

    moby_set_state(moby, 10, -1);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    life = ((s32)(math_random_int_range(0x2D, 0x4B)) * 5 + 2) / 6;
    part_spawn_between_points_depth_push(moby, from_pos, to_pos, moby + 0xF0, life, owner, flag);
}
