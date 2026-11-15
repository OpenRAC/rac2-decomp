#include "include_asm.h"
#include "names.h"

/* func_L02_003DB200 is a unit of its own: retail clears its first vector as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B04B0 __attribute__((sda));
extern float D_L02_001B04C8 __attribute__((sda));
extern float D_L02_001B04CC __attribute__((sda));
extern float D_L02_001B04D0 __attribute__((sda));
extern float D_L02_001B04D4 __attribute__((sda));
extern float D_L02_001B04D8 __attribute__((sda));
extern int D_L02_001B359C;
extern float D_L02_001BA500[4];

extern void *func_0029FCC0(char *, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_L02_003449D8(void *, void *, void *, int, int);

/* Spawns a spray of sparks at joint 4 of the boss's part, pushed away from the hero. */
void func_L02_003DB200(char *moby) {
    float launchVelocity[4];
    float jointPos[4];
    float awayDir[4];

    *(TI128 *)launchVelocity = 0;
    TransformMobyJointToWorld((char *)(gMobyPool_L02 + (*(int *)(*(char **)(moby + 0x68) + 0x244) << 8)), 4, jointPos);
    jointPos[2] = jointPos[2] + D_L02_001B04D4;
    FastVecSub(awayDir, gCameraPosition_L02, jointPos);
    awayDir[2] = 0.0f;
    vec_scale_to_length(awayDir, awayDir, D_L02_001B04D8);
    FastVecAdd(jointPos, jointPos, awayDir);
    AddRandomOffsetToVector(jointPos, D_L02_001B04C8);
    launchVelocity[2] = RandomFloatRange(D_L02_001B04CC, D_L02_001B04D0) * 0.016666668f;
    SpawnEnemyRecord(jointPos, launchVelocity, &D_L02_001B04B0, RandomIntBelow(2), 1);
}
