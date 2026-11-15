#include "include_asm.h"
#include "common.h"

/* func_L23_003C0A60 is a unit of its own: it reads $gp data. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA70 __attribute__((sda));
extern float D_L23_001AFAB0 __attribute__((sda));

extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern void mothership_project_point_onto_surface(void *, float);

typedef struct { u8 pad[0x18]; char *hit; } VisibilityCollision;
extern VisibilityCollision g_last_ray_hit;
typedef struct { u8 pad[0x2290]; char *hero; } VisibilityHero;
extern VisibilityHero g_hero_state;

/* Checks that nothing solid blocks the straight route from the enemy to its target, stepping along it. */
int IsPathClear(char *moby, TI128 *start_pos, TI128 *target_pos) {
    char *vars = *(char **)(moby + 0x68);
    TI128 loc[6];
    int found;
    char *hit;

    if (D_L23_001AFA70 < fast_vec_dist(start_pos, target_pos))
        return 0;
    qcopy(&loc[0], target_pos);
    mothership_project_point_onto_surface(&loc[0], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    FastVecSub(&loc[1], &loc[0], start_pos);
    vec_scale_to_length(&loc[1], &loc[1], D_L23_001AFAB0);
    qcopy(&loc[4], start_pos);
    qcopy(&loc[2], start_pos);
    mothership_project_point_onto_surface(&loc[2], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    found = 0;
    do {
        float distance = fast_vec_dist(&loc[4], &loc[0]);

        if (distance < D_L23_001AFAB0) {
            if (distance < 0.0f)
                return 1;
            vec_scale_to_length(&loc[5], &loc[1], distance);
            found = 1;
            FastVecAdd(&loc[3], &loc[4], &loc[5]);
            mothership_project_point_onto_surface(&loc[3], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
        } else {
            FastVecAdd(&loc[3], &loc[4], &loc[1]);
            mothership_project_point_onto_surface(&loc[3], *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
        }
        if (CollLine(&loc[2], &loc[3], 0x10, 0, 0)) {
            hit = g_last_ray_hit.hit;
            if (hit != moby && hit != g_hero_state.hero)
                return 0;
        }
        qcopy(&loc[2], &loc[3]);
        FastVecAdd(&loc[4], &loc[4], &loc[1]);
    } while (found == 0);
    return 1;
}
