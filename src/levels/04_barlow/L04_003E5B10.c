#include "names.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00283248(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002A7A00(void *, float, float);
extern float func_002A89A8(void *, int, float);
extern int func_002B5278(void *, float);
extern char *func_002BDCE8(void *, int, float, float, void *, float, int, int, float);
extern void func_L01_00321178(void *, void *);
extern float D_L04_002AF630[];

/* Moves the object along its animation toward a target point and turns it to face that point. On two key frames it also sprays a burst of sparks. */
void func_L04_003E5B10(char *moby, float *targetPos)
{
    float step[4], pos[4], vel[4], random[4], spawn[4];
    float frame, frameStart, brightness;
    int frameIndex, i, sparkKind;
    unsigned short lifetime;
    char *particle, *particleData;

    if ((unsigned char)moby[0x42] != (unsigned char)moby[0x43]) {
        TurnMobyTowardTarget(moby, targetPos);
        return;
    }
    frame = GetMobyAnimationValue(moby);
    frameIndex = FloatToInt(frame);
    {
        int nextIndex = frameIndex + 1;
        frameStart = IntToFloat(frameIndex);
        frame -= frameStart;
        FastVecScale(step, moby + 0xc0,
                      D_L04_002AF630[frameIndex] + (D_L04_002AF630[nextIndex] - D_L04_002AF630[frameIndex]) * frame);
    }
    FastVecAdd(moby + 0x10, step, moby + 0x10);
    StepMovementAtOwnPositionWithFactor(moby, FastMatrixHelperA(targetPos[0] - *(float *)(moby + 0x10), targetPos[1] - *(float *)(moby + 0x14)));
    *(float *)(moby + 0x18) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
    if (frameIndex != 5 && frameIndex != 15) {
        return;
    }
    if (frameIndex == 5) {
        TransformMobyJointToWorld(moby, 3, pos);
    } else {
        TransformMobyJointToWorld(moby, 2, pos);
    }
    FastVecScale(vel, moby + 0xc0, 0.5f);
    FastVecAdd(pos, pos, vel);
    pos[2] -= 0.2f;
    lifetime = 60;
    for (i = 9; i >= 0; i--) {
        RandomDirectionVector(random, 0.005000000353902578f, 0.050000004f);
        sparkKind = FloatToInt(RandomSignedFloatRange(1.0f, 3.0f));
        brightness = RandomFloatRange(0.3f, 1.0f) * 210000.0f;
        spawn[0] = pos[0] + RandomSignedFloatRange(0.0f, 0.3f);
        spawn[1] = pos[1] + RandomSignedFloatRange(0.0f, 0.3f);
        spawn[2] = pos[2] + RandomSignedFloatRange(0.0f, 0.3f);
        particle = SpawnSpinningSparkParticle(spawn, sparkKind, 0.0f, 1.0f, random, 1.01f, 0x406080, 0, brightness);
        if (particle) {
            *(unsigned short *)(particle + 0xa) = lifetime;
            particleData = particle + 0x20;
            particle[3] = 0x44;
            particle[9] = FloatToInt(4.0f) + 0x40;
            *(float *)(particleData + 0x1c) = IntToFloat(5);
            *(int *)(particleData + 4) = 3;
            particleData[0xa] = 0x20;
            particleData[0xb] = particle[0xa];
        }
    }
}
