#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern int func_002761F8(void *, void *, int, void *, int);
extern char *func_002AD0B0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_002AD5F8(void *, void *, void *, void *, void *, void *);
extern void func_002AD470(void *, void *, void *, void *, void *, void *);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002B0408(void *, void *, int);
extern void func_002AB6D8(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A8F70(void *, int, int, void *, void *, float);

/* The last collision probe's result; +0x18 is the object it hit. */
typedef struct { char pad[24]; char *object; } Collision;
extern Collision D_L07_001BF640;
extern int D_0018C0B0;
/* `sda` on an incomplete array: the one-instruction address the assembler expands absolute. */
extern char D_L07_001A8F20[] __attribute__((sda));

/* With no platform recorded at +0x314, probe from 2 above to 3 below the object and record a hit
   object whose flags have bit 1; otherwise carry the object along with its platform (states 7 and
   11 use func_002AD470) and, in mode 3, recompute its height on it. In that branch the position
   and +0xF0 vector are written `arg + 0x10` / `arg + 0xF0` at each use, without a variable:
   gcse then shares them through the copies retail has. */
void func_L07_003EB838(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float probeStart[4] __attribute__((aligned(16)));
    float probeEnd[4] __attribute__((aligned(16)));
    float localOffset[4] __attribute__((aligned(16)));
    char *platform = *(char **)(vars + 0x314);
    char *pos;

    if (platform == 0) {
        pos = moby + 0x10;
        *(Quad *)probeStart = *(Quad *)pos;
        *(Quad *)probeEnd = *(Quad *)pos;
        probeStart[2] += 2.0f;
        probeEnd[2] -= 3.0f;
        if (CollLine(probeStart, probeEnd, 0, moby, 0) && D_L07_001BF640.object != 0) {
            if (*(int *)(GetMobyPrivateValue2(D_L07_001BF640.object) + 0x3C) & 2) {
                *(char **)(vars + 0x314) = D_L07_001BF640.object;
                FastVecSub(localOffset, pos, *(char **)(vars + 0x314) + 0x10);
                TransformVectorByObjectOrGiven(*(char **)(vars + 0x314), localOffset, localOffset, 0);
                *(float *)(vars + 0x318) = localOffset[2] - 1.0f;
                GetAttachmentRotationAngles(moby, *(char **)(vars + 0x314), pos, moby + 0xF0, vars + 0x2F0, vars + 0x300);
            }
            *(int *)(vars + 0x88) |= 0x100;
        }
    } else {
        *(Quad *)(vars + 0x2E0) = *(Quad *)(moby + 0x10);
        if (*(unsigned char *)(moby + 0x20) == 7 || *(unsigned char *)(moby + 0x20) == 11)
            ApplyCollisionPushToObject(moby, platform, vars + 0x2F0, vars + 0x300, moby + 0x10, moby + 0xF0);
        else
            TransformPointAndRotationByParent(moby, platform, moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        AlignRotationToDirection(moby + 0xC0, *(char **)(vars + 0x314) + 0xE0, 0);
        GetEulerAnglesFromMatrix(moby + 0xC0, moby + 0xF0);
        if (*(unsigned char *)(moby + 0x95) == 3) {
            FastVecSub(probeStart, moby + 0x10, *(char **)(vars + 0x314) + 0x10);
            TransformVectorByObjectOrGiven(*(char **)(vars + 0x314), probeStart, probeStart, 0);
            probeStart[2] = *(float *)(vars + 0x318);
            matrix_mul_vec3(probeStart, probeStart, *(char **)(vars + 0x314) + 0xC0);
            *(float *)(vars + 0x180) = probeStart[2] + *(float *)(*(char **)(vars + 0x314) + 0x18);
            if (*(float *)(moby + 0x18) < *(float *)(vars + 0x180))
                QueueImpactEffect(moby, gHeroMoby_0018C0B0, 0x10000, moby + 0x10, D_L07_001A8F20, 7.0f);
        }
    }
}
