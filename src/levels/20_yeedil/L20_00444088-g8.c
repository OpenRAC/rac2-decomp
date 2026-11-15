#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2090 __attribute__((sda));

extern int D_L20_001B2094 __attribute__((sda));

extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);

extern char *homing_l20_shot_spawn(char *, char *, char *, char *, int, float, int);

extern void vec_scale_to_length(char *, char *, float);

extern char *turret_spawn_from_group(char *, int, TI128 *, TI128 *);

/* Launches the group shot from the enemy muzzle toward the hero. */
char *yeedil_boss_launch_group_shot(char *moby) {
    TI128 launchPos;
    TI128 launchVelocity;
    TI128 *pa = &launchPos;
    TI128 *pb = &launchVelocity;
    char *state;
    float aimAngle;

    aimAngle = 0.78539824f;
    state = *(char **)(moby + 0x68);
    yeedil_boss_compute_shot_launch(moby, (char *)pa, (char *)pb, &aimAngle);
    return turret_spawn_from_group(moby, *(int *)(state + 0x240), pa, pb);
}

/* Launches a damaging shot from the enemy muzzle, scaled by its speed and damage settings. */
void yeedil_boss_launch_damage_shot(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 launchPos;
    TI128 launchVelocity;
    float aimAngle;

    aimAngle = 0.78539824f;
    yeedil_boss_compute_shot_launch(moby, (char *)&launchPos, (char *)&launchVelocity, (float *)&aimAngle);
    vec_scale_to_length((char *)&launchVelocity, (char *)&launchVelocity, D_L20_001B2090 * 0.0166666675f);
    homing_l20_shot_spawn(moby, (char *)&launchPos, (char *)&launchVelocity, state + 0x1F0, D_L20_001B2094,
                      (float)*(unsigned char *)(state + 0x35), *(int *)(state + 0x210));
}
