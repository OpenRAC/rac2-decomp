#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;

extern short D_L00_001B28B0[] MACRO_ADDR;
extern short D_L00_001B28B8[] MACRO_ADDR;
extern Vector D_L00_0023D9E0[][5];    /* trail points: [trail][point] */
extern Vector D_L00_0023D9E0_1[][5];  /* the same table: the name each point's predecessor is read through */
extern Vector D_L00_001B8DC0;
extern float D_L00_001AFA14 __attribute__((sda));
extern void func_002A7988(void *, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);

/* Four five-point trails: one whose timer runs out is re-aimed from the object's position with
   random bends, a live one jitters each segment. */
void func_L00_003B4EF8(unsigned char *object)
{
    Vector position, direction, axis, displacements[5];
    int i, j;
    float sign, angle;

    qcopy(&position, object + 0x10);
    for (i = 0; i < 4; i++) {
        short *timer = &D_L00_001B28B0[i];

        if (*timer == 0)
            continue;
        --*timer;
        if (*timer < 0)
            *timer = 0;
        if (*timer == 0) {
            *timer = 4;
            D_L00_001B28B8[i] = 64;
            SpawnRandomDirectionEffect(&direction, D_L00_001AFA14, D_L00_001AFA14);
            qcopy(&D_L00_0023D9E0[i][0], &position);
            sign = 1.0f;
            for (j = 1; j < 5; j++) {
                FastVecSub(&axis, &D_L00_0023D9E0_1[i][j - 1], &gCameraPosition_L00);
                angle = RandomFloatRange(0.17453295f, 0.78539824f) * sign;
                sign = -sign;
                ApplyAxisRotationToQuaternion(&direction, &direction, &axis, angle);
                FastVecAdd(&D_L00_0023D9E0[i][j], &D_L00_0023D9E0_1[i][j - 1], &direction);
            }
        } else {
            for (j = 1; j < 5; j++) {
                FastVecSub(&displacements[j], &D_L00_0023D9E0[i][j], &D_L00_0023D9E0_1[i][j - 1]);
                displacements[j].v[0] += RandomSignedFloatRange(0.0f, 0.1f);
                displacements[j].v[1] += RandomSignedFloatRange(0.0f, 0.1f);
                displacements[j].v[2] += RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L00_0023D9E0[i][0], &position);
            for (j = 1; j < 5; j++)
                FastVecAdd(&D_L00_0023D9E0[i][j], &D_L00_0023D9E0_1[i][j - 1], &displacements[j]);
            if (D_L00_001B28B0[i] > 0)
                D_L00_001B28B8[i] = 32;
            else
                D_L00_001B28B8[i] = 0;
        }
    }
}
