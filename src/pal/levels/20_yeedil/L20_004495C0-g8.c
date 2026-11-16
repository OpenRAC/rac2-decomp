#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void yeedil_boss_compute_shot_launch_pal(char *, char *, char *, float *);
extern char *turret_spawn_from_group_pal(char *, int, TI128 *, TI128 *);

/* Launches the group shot from the enemy muzzle toward the hero. (PAL) */
char *yeedil_boss_launch_group_shot_pal(char *moby) {
    TI128 launch_pos;
    TI128 launch_velocity;
    TI128 *pa = &launch_pos;
    TI128 *pb = &launch_velocity;
    char *state;
    float aim_angle;

    aim_angle = 0.78539824f;
    state = *(char **)(moby + 0x68);
    yeedil_boss_compute_shot_launch_pal(moby, (char *)pa, (char *)pb, &aim_angle);
    return turret_spawn_from_group_pal(moby, *(int *)(state + 0x240), pa, pb);
}
