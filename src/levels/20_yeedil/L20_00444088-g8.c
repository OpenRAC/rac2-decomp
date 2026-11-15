#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2090 __attribute__((sda));

extern int D_L20_001B2094 __attribute__((sda));

extern void func_L20_00443B60(char *, char *, char *, float *);

extern void func_L20_0044B100(char *, char *, char *, char *, int, float, int);

extern void func_00282F20(char *, char *, float);

extern void func_L20_0044AC38(char *, int, TI128 *, TI128 *);

/* Launches the group shot from the enemy muzzle toward the hero. */
void func_L20_00444018(char *moby) {
    TI128 launchPos;
    TI128 launchVelocity;
    TI128 *pa = &launchPos;
    TI128 *pb = &launchVelocity;
    char *state;
    float aimAngle;

    aimAngle = 0.78539824f;
    state = *(char **)(moby + 0x68);
    ComputeShotLaunch(moby, (char *)pa, (char *)pb, &aimAngle);
    SpawnTurretFromGroup(moby, *(int *)(state + 0x240), pa, pb);
}

/* Launches a damaging shot from the enemy muzzle, scaled by its speed and damage settings. */
void func_L20_00444088(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 launchPos;
    TI128 launchVelocity;
    float aimAngle;

    aimAngle = 0.78539824f;
    ComputeShotLaunch(moby, (char *)&launchPos, (char *)&launchVelocity, (float *)&aimAngle);
    vec_scale_to_length((char *)&launchVelocity, (char *)&launchVelocity, D_L20_001B2090 * 0.0166666675f);
    SpawnHomingShot_L20(moby, (char *)&launchPos, (char *)&launchVelocity, state + 0x1F0, D_L20_001B2094,
                      (float)*(unsigned char *)(state + 0x35), *(int *)(state + 0x210));
}
