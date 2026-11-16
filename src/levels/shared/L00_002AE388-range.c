#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
typedef struct { char pad0[0x40]; float matrix[16]; float position[4]; char pad1[0x318-0x90]; float height; char pad2[0x2294-0x31c]; int mode; } ScorerState;
extern ScorerState D_00189E20_26;
typedef struct { char pad[0x140]; float position[4]; float pad1; float pitch; float heading; } ScorerCamera;
extern ScorerCamera g_scalar_transition_state;
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int moby_is_in_special_class_range(void *);
extern void FastVecSub(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern float vec_length_xy(void *);

/* Gives a target a score (lower is better) from its distance and angle, and flags it if it is out of range. */
float hero_score_target_by_heading(char *object, float heading, float range, int *blocked, float hlimit, float vlimit)
{
    float position[4] __attribute__((aligned(16)));
    float distance, horizontal, vertical, sum, score;
    *blocked = 0;
    qcopy_nc(position, D_00189E20_26.position);
    if (D_00189E20_26.mode == 20)
        position[2] = D_00189E20_26.height;
    distance = fast_vec_dist(position, object + 0x10);
    if (range < distance) *blocked = 1;
    sum = FastDiffRots(mat_fast_helper_a(F(object,0x10)-position[0], F(object,0x14)-position[1]),heading);
    horizontal = sum;
    vertical = FastDiffRots(mat_fast_helper_a(vec_distance_xy(position,object+0x10),F(object,0x18)-position[2]),0.0f);
    if (D_00189E20_26.mode==1 || D_00189E20_26.mode==29) {
        horizontal = FastDiffRots(mat_fast_helper_a(F(object,0x10)-g_scalar_transition_state.position[0],F(object,0x14)-g_scalar_transition_state.position[1]),g_scalar_transition_state.heading);
        vertical = FastDiffRots(mat_fast_helper_a(vec_distance_xy(g_scalar_transition_state.position,object+0x10),F(object,0x18)-g_scalar_transition_state.position[2]),-g_scalar_transition_state.pitch);
        sum = horizontal + vertical;
        horizontal = (horizontal > vertical ? horizontal : vertical);
    }
    if (hlimit > 0.0f) { if (hlimit < horizontal) *blocked=1; }
    if (vlimit > 0.0f) { if (vlimit < vertical) *blocked=1; }
    score = distance + sum * distance;
    if (moby_is_in_special_class_range(object)) score += range * 0.8f;
    else if (object && *(char **)(object+0x24) && *(short *)(*(char **)(object+0x24)+0x46)==22) score += range * 0.8f;
    return score;
}



