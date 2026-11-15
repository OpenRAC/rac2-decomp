#include "include_asm.h"
#include "names.h"

/* func_L02_003D6570 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B0318 __attribute__((sda));
extern float D_L02_001B031C __attribute__((sda));
extern int D_L02_001B0320 __attribute__((sda));
extern unsigned int D_L02_001B0330 __attribute__((sda));
extern float D_L02_001B0334 __attribute__((sda));
extern float D_L02_001BA500[4];

extern void *func_0029FCC0(char *, int, void *);
extern void func_0029FC20(char *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L00_00325AE8(void *, int, float, float);

/* Draws one glow flare at a joint, fading it out when the joint faces away from the camera. */
void func_L02_003D6570(char *self, int joint) {
    float origin[4];
    float originCopy[4];
    float matrix[16];
    float offset[4];
    float toCamera[4];
    float facing[4];
    float facingDot;
    unsigned int color;

    TransformMobyJointToWorld(self, joint, origin);
    *(TI128 *)originCopy = *(TI128 *)origin;
    TransformMobyJointPoint(self, joint, matrix);
    transform_vector(offset, &D_L02_001B0320, matrix);
    FastVecAdd(origin, origin, offset);
    FastVecSub(toCamera, gCameraPosition_L02, origin);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    *(TI128 *)facing = *(TI128 *)matrix;
    facingDot = FastVecDot(toCamera, facing);
    if (D_L02_001B0334 < facingDot) {
        color = D_L02_001B0330;
        facingDot = facingDot * facingDot;
        DrawBillboardQuad_L00(origin, (color & 0xFFFFFF) | ((int)(facingDot * (float)(int)(color >> 24)) << 24),
                          D_L02_001B031C, D_L02_001B0318);
    }
}
