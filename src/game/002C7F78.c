#include "common.h"
extern void func_00300190(char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern float func_002A7878(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00282978(char *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002B9180(char *);
extern int D_001B1688 __attribute__((sda));
extern char D_001B5200[];
extern char D_00189EA0[];
extern float func_00282E48(char *, char *);
extern void func_00282CF0(char *, char *, char *);
/* Updates a floating particle: it slows down, sinks, gets pushed away by the hero and fades out. It is removed when its life runs out. */
void func_002C7F78(char *particle)
{
    char *motion, *position = particle + 16, *hero, *heroBase;
    float push[4], heroPos[4];
    float a, b;
    motion = particle + 32;
    TransformVectorOrCopy(position, position);
    FastVecScale(motion, motion, 0.9f);
    *(float *)(motion + 8) -= *(float *)(motion + 12);
    FastVecAdd(position, position, motion);
    hero = gHeroPosition;
    if (fast_vec_dist(position, hero) < 1.05f) {
      heroBase = hero - 128;
      if (*(float *)(heroBase + 0x170) != 0) {
        qcopy(heroPos, hero);
        FastVecSub((char *)push, position, (char *)heroPos);
        a = RandomFloatRange(0.1f, 2.0f);
        vec_scale_to_length((char *)push, (char *)push, *(float *)(heroBase + 0x170) * 0.2f + a * 0.016666667f * 0.15f);
        *(unsigned char *)(particle + 8) += (int)(*(short *)(motion + 22) * *(float *)(heroBase + 0x170) * 0.5f);
        FastVecAdd(position, position, (char *)push);
    }
    }
    if (gGameTime % 10 == 0) {
        *(float *)(motion + 28) = FastAddRotations(*(float *)(motion + 28), 1.0f);
        a = FastSinOrCosB(*(float *)(motion + 28));
        vec_scale_to_length((char *)push, gActiveCamera, a * 0.0075f);
        FastVecAdd(motion, motion, (char *)push);
    }
    if (*(short *)(motion + 20) >= 160) {
        if (*(short *)(particle + 10) < *(short *)(motion + 20)) {
            a = IntToFloat(*(short *)(particle + 10)); b = IntToFloat(*(short *)(motion + 20));
            *(int *)(particle + 4) = (FloatToInt((a /= b) * 128.0f) << 24) | 0x353535;
        } else *(int *)(particle + 4) = 0x9F353535;
    } else {
        if (*(short *)(particle + 10) < *(short *)(motion + 20)) {
            a = IntToFloat(*(short *)(particle + 10)); b = IntToFloat(*(short *)(motion + 20));
            *(int *)(particle + 4) = (FloatToInt((a /= b) * 64.0f) << 24) | 0x909090;
        } else *(int *)(particle + 4) = 0x40909090;
    }
    *(unsigned char *)(particle + 8) += *(unsigned char *)(motion + 22);
    if (FastDecTimer(particle + 10)) KillParticle(particle);
}
