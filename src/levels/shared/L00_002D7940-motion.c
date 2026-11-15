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
void func_L00_002DA1E0(char *pos, float step)
{
    float delta[4];
    float previous[4];
    char *obj;
    float *src;
    int n;
    int i;
    int j;

    obj = D_L00_001B8C80.active;
    src = (float *)(obj + 0x64);
    previous[0] = src[0];
    previous[1] = src[1];
    previous[2] = src[2];
    previous[3] = 0.0f;
    if (*(short *)(obj + 0x8A) != 0) {
        qcopy(D_L00_001B8C80.position, pos);
        *(short *)(obj + 0x8A) = 0;
        return;
    }
    FastVecSub(delta, pos, previous);
    n = FloatToInt(FastVecLength(delta) / (step * 0.9f)) + 1;
    divide_vector_xyz(delta, delta, IntToFloat(n));
    qcopy(pos, previous);
    for (j = 0; j < n; j++) {
        FastVecAdd(pos, pos, delta);
        i = 0;
        while (i < 6 && func_00277258(pos, D_L00_001B1850, D_00189E20.collision, step) != 0) {
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
