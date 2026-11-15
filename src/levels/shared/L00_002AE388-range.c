#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
typedef struct { char pad0[0x40]; float matrix[16]; float position[4]; char pad1[0x318-0x90]; float height; char pad2[0x2294-0x31c]; int mode; } ScorerState;
extern ScorerState D_00189E20_26;
typedef struct { char pad[0x140]; float position[4]; float pad1; float pitch; float heading; } ScorerCamera;
extern ScorerCamera D_L00_001B8C80;
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_002ABB78(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282E20(void *);

float func_L00_002AE388(char *object, float heading, float range, int *blocked, float hlimit, float vlimit)
{
    float position[4] __attribute__((aligned(16)));
    float distance, horizontal, vertical, sum, score;
    *blocked = 0;
    qcopy_nc(position, D_00189E20_26.position);
    if (D_00189E20_26.mode == 20)
        position[2] = D_00189E20_26.height;
    distance = fast_vec_dist(position, object + 0x10);
    if (range < distance) *blocked = 1;
    sum = FastDiffRots(func_00283248(F(object,0x10)-position[0], F(object,0x14)-position[1]),heading);
    horizontal = sum;
    vertical = FastDiffRots(func_00283248(vec_distance_xy(position,object+0x10),F(object,0x18)-position[2]),0.0f);
    if (D_00189E20_26.mode==1 || D_00189E20_26.mode==29) {
        horizontal = FastDiffRots(func_00283248(F(object,0x10)-D_L00_001B8C80.position[0],F(object,0x14)-D_L00_001B8C80.position[1]),D_L00_001B8C80.heading);
        vertical = FastDiffRots(func_00283248(vec_distance_xy(D_L00_001B8C80.position,object+0x10),F(object,0x18)-D_L00_001B8C80.position[2]),-D_L00_001B8C80.pitch);
        sum = horizontal + vertical;
        horizontal = (horizontal > vertical ? horizontal : vertical);
    }
    if (hlimit > 0.0f) { if (hlimit < horizontal) *blocked=1; }
    if (vlimit > 0.0f) { if (vlimit < vertical) *blocked=1; }
    score = distance + sum * distance;
    if (func_002ABB78(object)) score += range * 0.8f;
    else if (object && *(char **)(object+0x24) && *(short *)(*(char **)(object+0x24)+0x46)==22) score += range * 0.8f;
    return score;
}



