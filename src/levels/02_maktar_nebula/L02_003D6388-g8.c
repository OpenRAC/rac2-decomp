#include "include_asm.h"
#include "names.h"

/* func_L02_003D6388 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029FCC0(char *, int, void *);

extern void func_0029FC20(char *, int, void *);

extern void func_002830C0(void *, void *, void *);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282DB0(void *, void *);

extern void func_L00_00325AE8(void *, int, float, float);

extern float D_L02_001BA500[4];

extern char D_L02_001B02E0[8] __attribute__((sda));

extern char D_L02_001B0300[8] __attribute__((sda));

extern unsigned int D_L02_001B0310 __attribute__((sda));

extern float D_L02_001B0314 __attribute__((sda));

extern float D_L02_001B02DC __attribute__((sda));

extern float D_L02_001B02D8 __attribute__((sda));

extern float D_L02_001B02F0 __attribute__((sda));

/* Draws the glow flares at one joint, two offset spots, and fades them out when the joint faces away from the camera. */
void func_L02_003D6388(char *self, int joint, int mirror) {
    float origin[4];
    float origin2[4];
    float matrix[16];
    float offsetA[4];
    float offsetB[4];
    float toCamera[4];
    float facing[4];
    float facingDot;
    float alpha;
    unsigned int color;

    TransformMobyJointToWorld(self, joint, origin);
    *(TI128 *)origin2 = *(TI128 *)origin;
    TransformMobyJointPoint(self, joint, matrix);
    *(TI128 *)offsetA = *(TI128 *)D_L02_001B02E0;
    *(TI128 *)offsetB = *(TI128 *)D_L02_001B0300;
    if (mirror != 0) {
        offsetA[1] = -offsetA[1];
        offsetB[1] = -offsetB[1];
    }
    transform_vector(offsetA, offsetA, matrix);
    FastVecAdd(origin, origin, offsetA);
    transform_vector(offsetB, offsetB, matrix);
    FastVecAdd(origin2, origin2, offsetB);
    FastVecSub(toCamera, gCameraPosition_L02, origin);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    vec_scale_to_length(facing, matrix + 8, -1.0f);
    facingDot = FastVecDot(toCamera, facing);
    if (D_L02_001B0314 < facingDot) {
        color = D_L02_001B0310;
        alpha = (float)(int)(color >> 24);
        color &= 0xFFFFFF;
        facingDot = facingDot * facingDot;
        color |= (int)(facingDot * alpha) << 24;
        DrawBillboardQuad_L00(origin, color, D_L02_001B02DC, D_L02_001B02D8);
        DrawBillboardQuad_L00(origin2, color, D_L02_001B02F0, D_L02_001B02D8);
    }
}
