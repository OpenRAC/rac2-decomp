#include "common.h"

typedef struct {
    char pad000[0x140];
    float position[4];
    char pad150[0x40];
    char *active;
} CameraMotionState;
extern CameraMotionState D_L00_001B8C80;
extern char D_L00_001BF230[];
typedef struct {
    char pad000[0x2290];
    void *collision;
} CameraCollisionContext;
extern CameraCollisionContext D_00189E20;
extern int D_L00_001B1850 __attribute__((sda));

extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_00282DF0(void *v);
extern void func_00282D90(void *out, void *a, float f);
extern int func_00283CF0(float f);
extern float func_00283CE0(int v);
extern int func_00277258(void *pos, int a, void *b, float step);

/* Moves the camera in radius-scaled steps and resolves up to six contacts per step.
 * Counterpart: RAC1 resolve_camera_movement_collisions. */
/* Moves the camera toward a target point in small steps and pushes it out of walls. */
void func_L00_002DA1E0(char *pos, float step)
{
    float delta[4];
    float previous[4];
    char *camObj;
    float *src;
    int steps;
    int i;
    int j;

    camObj = D_L00_001B8C80.active;
    src = (float *)(camObj + 0x64);
    previous[0] = src[0];
    previous[1] = src[1];
    previous[2] = src[2];
    previous[3] = 0.0f;
    if (*(short *)(camObj + 0x8A) != 0) {
        qcopy(D_L00_001B8C80.position, pos);
        *(short *)(camObj + 0x8A) = 0;
        return;
    }
    FastVecSub(delta, pos, previous);
    steps = FloatToInt(FastVecLength(delta) / (step * 0.9f)) + 1;
    divide_vector_xyz(delta, delta, IntToFloat(steps));
    qcopy(pos, previous);
    for (j = 0; j < steps; j++) {
        FastVecAdd(pos, pos, delta);
        i = 0;
        while (i < 6 && TestPointAgainstCollision(pos, D_L00_001B1850, gHeroState.collision, step) != 0) {
            qcopy(pos, D_L00_001BF230);
            {
                char *hit = D_L00_001B8C80.active;
                if (*(unsigned char *)(hit + 0x89) == 0)
                    *(unsigned char *)(hit + 0x89) = 1;
            }
            i++;
        }
    }
    qcopy(D_L00_001B8C80.position, pos);
}
