#include "include_asm.h"
#include "names.h"

/* func_L02_003DB158 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int s32;
typedef float f32;
typedef int TQ __attribute__((mode(TI)));

extern f32 D_L02_001B0474 __attribute__((sda));
extern f32 D_L02_001B0478 __attribute__((sda));
extern s32 D_L02_001B0480 __attribute__((sda));

extern void *func_0029FCC0(char *, int, void *);
extern void func_0029FC20(char *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00325AE8(void *, int, float, float);

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 v[16]; } M4;

/* Draws a glow at a joint of the boss, moved by a fixed offset in the joint's own direction. */
void func_L02_003DB158(char *moby, s32 jointIndex) {
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);
    V4 jointPos, jointPosCopy;
    M4 jointMatrix;
    V4 localOffset;

    TransformMobyJointToWorld(moby, jointIndex, &jointPos);
    *(TQ *)&jointPosCopy = *(TQ *)&jointPos;
    TransformMobyJointPoint(moby, jointIndex, &jointMatrix);
    transform_vector(&localOffset, &D_L02_001B0480, &jointMatrix);
    FastVecAdd(&jointPos, &jointPos, &localOffset);
    DrawBillboardQuad_L00(&jointPos, *(s32 *)(vars + 0x250), D_L02_001B0478, D_L02_001B0474);
}
