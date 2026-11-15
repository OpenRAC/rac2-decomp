#include "include_asm.h"
#include "names.h"

/* func_L02_003DAE60 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B0410 __attribute__((sda));
extern float D_L02_001B0414 __attribute__((sda));
extern int D_L02_001B0420 __attribute__((sda));
extern float D_L02_001B0430 __attribute__((sda));
extern float D_L02_001BA500[4];

extern void *func_0029FCC0(char *, int, void *);
extern void func_0029FC20(char *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L00_00325AE8(void *, int, float, float);

/* Draws a glow at a joint of the boss, brighter when it faces the camera. */
void func_L02_003DAE60(char *moby, int jointIndex) {
    float jointPos[4];
    float jointPosCopy[4];
    float jointMatrix[16];
    float localOffset[4];
    float toCamera[4];
    float axisCopy[4];
    float alignment;
    unsigned int color;
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);

    TransformMobyJointToWorld(moby, jointIndex, jointPos);
    *(TI128 *)jointPosCopy = *(TI128 *)jointPos;
    TransformMobyJointPoint(moby, jointIndex, jointMatrix);
    transform_vector(localOffset, &D_L02_001B0420, jointMatrix);
    FastVecAdd(jointPos, jointPos, localOffset);
    FastVecSub(toCamera, gCameraPosition_L02, jointPos);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    *(TI128 *)axisCopy = *(TI128 *)jointMatrix;
    alignment = FastVecDot(toCamera, axisCopy);
    if (D_L02_001B0430 < alignment) {
        color = *(unsigned int *)(vars + 0x250);
        alignment = alignment * alignment;
        DrawBillboardQuad_L00(jointPos, (color & 0xFFFFFF) | ((int)(alignment * (float)(int)(color >> 24)) << 24),
                          D_L02_001B0414, D_L02_001B0410);
    }
}
