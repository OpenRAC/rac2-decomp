#include "include_asm.h"
#include "common.h"

/* func_L23_003C0A60 is a unit of its own: it reads $gp data. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA70 __attribute__((sda));
extern float D_L23_001AFAB0 __attribute__((sda));

extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L23_00418650(void *, float);

typedef struct { u8 pad[0x18]; char *hit; } VisibilityCollision;
extern VisibilityCollision D_L23_001C0A80;
typedef struct { u8 pad[0x2290]; char *hero; } VisibilityHero;
extern VisibilityHero D_00189E20;

/* Checks that nothing solid blocks the straight route from the enemy to its target, stepping along it. */
int func_L23_003C0A60(char *moby, TI128 *startPos, TI128 *targetPos) {
    char *vars = *(char **)(moby + 0x68);
    TI128 loc[6];
    int found;
    char *hit;

    if (D_L23_001AFA70 < fast_vec_dist(startPos, targetPos))
        return 0;
    qcopy(&loc[0], targetPos);
    ProjectPointOntoPlanetSurface(&loc[0], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    FastVecSub(&loc[1], &loc[0], startPos);
    vec_scale_to_length(&loc[1], &loc[1], D_L23_001AFAB0);
    qcopy(&loc[4], startPos);
    qcopy(&loc[2], startPos);
    ProjectPointOntoPlanetSurface(&loc[2], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    found = 0;
    do {
        float distance = fast_vec_dist(&loc[4], &loc[0]);

        if (distance < D_L23_001AFAB0) {
            if (distance < 0.0f)
                return 1;
            vec_scale_to_length(&loc[5], &loc[1], distance);
            found = 1;
            FastVecAdd(&loc[3], &loc[4], &loc[5]);
            ProjectPointOntoPlanetSurface(&loc[3], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
        } else {
            FastVecAdd(&loc[3], &loc[4], &loc[1]);
            ProjectPointOntoPlanetSurface(&loc[3], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
        }
        if (CollLine(&loc[2], &loc[3], 0x10, 0, 0)) {
            hit = gLastRayHit.hit;
            if (hit != moby && hit != gHeroState.hero)
                return 0;
        }
        qcopy(&loc[2], &loc[3]);
        FastVecAdd(&loc[4], &loc[4], &loc[1]);
    } while (found == 0);
    return 1;
}
