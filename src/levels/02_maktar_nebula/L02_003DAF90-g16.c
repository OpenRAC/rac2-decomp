#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { float position[4]; float original[4]; } EmitterOrigin;
extern float D_L02_001B0440[4] __attribute__((sda));
extern float D_L02_001B0438 __attribute__((sda));
extern float D_L02_001B0434 __attribute__((sda));
extern void func_0029FCC0(char *, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00325AE8(void *, int, float, float);

/* Emit at joint four after transforming the local offset into world space. */
/* Draws a glow at joint 4, moved by a fixed offset in the joint's own direction. */
void func_L02_003DAF90(char *moby)
{
    EmitterOrigin emitter;
    float jointMatrix[16];
    float localOffset[4];
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);

    TransformMobyJointToWorld(moby, 4, (char *)emitter.position);
    *(Quadword *)emitter.original = *(Quadword *)emitter.position;
    TransformMobyJointPoint(moby, 4, (char *)jointMatrix);
    transform_vector(localOffset, D_L02_001B0440, jointMatrix);
    FastVecAdd(emitter.position, emitter.position, localOffset);
    DrawBillboardQuad_L00(emitter.position, *(int *)(vars + 0x250),
            D_L02_001B0438, D_L02_001B0434);
}
