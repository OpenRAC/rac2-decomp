#include "include_asm.h"
#include "names.h"

extern unsigned int D_L02_001A8F00;

/* Report whether the resident flag word is still clear. */
int func_L02_002F1658(void) {
    return D_L02_001A8F00 == 0;
}

typedef int TI128 __attribute__((mode(TI)));

typedef union {
    TI128 q;
    float f[4];
} Vec4;

typedef struct Ent {
    unsigned char pad00[0x31];
    unsigned char f31;
    unsigned char pad32[2];
    unsigned short f34;
    unsigned char pad36[0x98 - 0x36];
    int f98;
} Ent;

extern unsigned int D_L02_001FC060[];
extern char *D_L02_001B359C;
extern int D_L02_001B35B8 __attribute__((sda));
extern int D_L02_001A9048;
extern float D_L02_001AEF50 __attribute__((sda));
extern float D_L02_001AEE50[2] __attribute__((sda));
extern float D_L02_001AEE48[2] __attribute__((sda));
extern float D_L02_001AEE40[2] __attribute__((sda));
extern int D_L02_001AEE70 __attribute__((sda));
extern float func_00283198(float x);
extern float func_00283B98(float a, float b);
extern float func_00283BE0(float a, float b);
extern void func_002C9828(int *path, int seg, void *pos, void *rot, int flags, float t);
extern int func_002A9640(void *e, int a1, int a2);
extern void func_L00_0032A258(void *a0, void *a1, void *a2, void *a3, int t0, int t1, int t2, int t3,
                              int s0, int s1, int s2);
extern void func_L01_0031A278(char *a0, float *a1, float f12, float f13, float f14);
extern void func_002E5CF8(int a0, int a1, void *a2);
extern void func_002ABBB8(void *a0, float f12, void *a1, float f13, void *a2, float f14, int a3,
                          float f15, int t0, int t1, float f16, float f17, int t2, float f18,
                          int t3, int s0, int s1, int s2, int s3);
extern void func_002AA2E8(float *p, float a, float b);
extern void func_L02_0038CDE8(void *e);
extern void func_L02_0038D978(void *e);
extern void func_002A0F48(void *e);

/* Walks the group's entity list: each one moves along the path object (func_002C9828), turns its
   angle and advances its phase; a hit by the player while it is active switches it off and spawns
   the debris (func_L00_0032A258, func_002ABBB8); a live one tilts toward its turning speed
   (func_002AA2E8) and runs the level's two update calls. */
void func_L02_0038C998(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int *path = *(int **)(vars + 0x60);
    float range = (float)*path;
    float step = *(float *)(vars + 0x14);
    int seg = *(short *)(vars + 0x70);
    float rate = D_L02_001AEF50 * 0.00029088825f;
    unsigned short *q;
    unsigned char *target;
    unsigned char *targetVars;
    float prev;
    float h;

    q = (unsigned short *)gEntityGroupLists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)gEntityGroupLists[moby[0x21]])) {
        target = (unsigned char *)(gMobyPool_L02 + ((*q & 0x7FFF) << 8));
        if (target == 0)
            break;
        targetVars = *(unsigned char **)(target + 0x68);
        prev = *(float *)(target + 0xF8);
        h = *(float *)(targetVars + 0x10) + *(float *)(targetVars + 0x7C) * FastSinOrCosB(*(float *)(targetVars + 0x80));
        if (range <= h)
            h -= range;
        else if (h < 0.0f)
            h += range;
        SamplePathPosition(path, seg, target + 0x10, target + 0xF0, 0, h);
        *(float *)(targetVars + 0x68) = FastAddRotations(*(float *)(targetVars + 0x68), *(float *)(targetVars + 0x6C));
        *(float *)(target + 0x18) += FastSinOrCosB(*(float *)(targetVars + 0x68));
        *(float *)(targetVars + 0x10) += step;
        if (range <= *(float *)(targetVars + 0x10))
            *(float *)(targetVars + 0x10) -= range;
        *(float *)(targetVars + 0x80) = FastAddRotations(*(float *)(targetVars + 0x80), *(float *)(targetVars + 0x84));
        if (FindOwnedEffectSlot(target, 0x4010000, 0) != 0) {
            if (target[0x31] != 0) {
                Vec4 dir;
                float pos[4] __attribute__((aligned(16)));

                ((Ent *)target)->f31 = 0;
                ((Ent *)target)->f34 |= 1;
                ((Ent *)target)->f98 = 0;
                D_L02_001A9048++;
                ExplodeObjectIntoPieces(target, D_L02_001AEE50, D_L02_001AEE48, D_L02_001AEE40, 0x3F, 2,
                                  D_L02_001AEE70, 0, 0xFFFF, 0xFF, 0);
                dir.q = 0;
                dir.f[2] = 0.05000000447f;
                ComputeMobyLocalPoint((char *)target, pos, 0.0f, 0.0f, 0.0f);
                if (*(short *)(target + 0xAA) == 0x1290 /* moby class 4752 */)
                    PlayMobySound(0, 0, target);
                if (*(short *)(target + 0xAA) == 0x134B /* moby class 4939 */)
                    PlayMobySound(0, 0, target);
                if (*(short *)(target + 0xAA) == 0xB15 /* moby class 2837 */)
                    PlayMobySound(1, 0, target);
                if (*(short *)(target + 0xAA) == 0xB13 /* moby class 2835 */)
                    PlayMobySound(1, 0, target);
                SpawnExplosionEffects(target, 0.0f, &dir, 0.0f, pos, 5.0f, 0x23, 2.5f, 8, 0x10, 0.0f, 3.0f, -1,
                              15.0f, 1, 10, -1, 0, 0x810001);
            }
        }
        target[0xA8] = 0xFF;
        if (target[0x31] != 0) {
            if ((*(unsigned short *)(target + 0x34) ^ 1) & 1) {
                h = -fast_subtract_rotations(*(float *)(target + 0xF8), prev) * 50.0f;
                if (0.78539824f < h)
                    h = 0.78539824f;
                if (h < -0.78539824f)
                    h = -0.78539824f;
                ApproachValue((float *)(target + 0xF0), h, rate);
                if (*(short *)(targetVars + 0x72) != 0)
                    UpdateLampGlowEffects(target);
                UpdateBlinkingLampMoby(target);
            }
        }
        func_002A0F48(target);
        q++;
    }
}
