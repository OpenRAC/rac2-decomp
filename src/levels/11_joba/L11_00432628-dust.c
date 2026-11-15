#include "names.h"
/* A unit of its own for -frac2-keep-block-order (config/cflags.txt): retail keeps the
   frame-15 joint call behind the frame-5 one, reached by a jump. */

extern int func_L01_00321178(char *, float *);
extern float func_0029F530(char *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float D_L11_002B6B60[];
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283248(float, float);
extern int func_002B5278(char *, float);
extern void func_0029FCC0(char *, int, float *);
extern void func_002A7A00(float *, float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern char *func_002BDCE8(float *, float, float, float, int, float *, float, int, int);

/* Steps along the vector at +0xC0, weighted by the walk table at the animation frame, and
   turns toward the target; on frames 5 and 15 it scatters ten dust particles at a joint
   (3, then 2). A state change hands over to the shared handler instead. */
void func_L11_00432628(char *obj, float *target)
{
    float offset[4], origin[4], half[4], velocity[4], pos[4];
    float frame, frameStart, scale;
    int index, i, type, next;
    short lifetime;
    char *particle, *data;

    if (*(unsigned char *)(obj + 0x42) != *(unsigned char *)(obj + 0x43)) {
        TurnMobyTowardTarget(obj, target);
        return;
    }
    frame = GetMobyAnimationValue(obj);
    index = FloatToInt(frame);
    next = index + 1;
    frameStart = IntToFloat(index);
    FastVecScale((char *)offset, obj + 0xC0, D_L11_002B6B60[index] + (D_L11_002B6B60[next] - D_L11_002B6B60[index]) * (frame - frameStart));
    FastVecAdd(obj + 0x10, (char *)offset, obj + 0x10);
    StepMovementAtOwnPositionWithFactor(obj, FastMatrixHelperA(target[0] - *(float *)(obj + 0x10), target[1] - *(float *)(obj + 0x14)));
    if (index == 5 || index == 15) {
        if (index == 5) {
            TransformMobyJointToWorld(obj, 3, origin);
        } else {
            TransformMobyJointToWorld(obj, 2, origin);
        }
        FastVecScale((char *)half, obj + 0xC0, 0.5f);
        FastVecAdd((char *)origin, (char *)origin, (char *)half);
        origin[2] -= 0.2f;
        lifetime = 60;
        for (i = 9; i >= 0; i--) {
            RandomDirectionVector(velocity, 0.005000000353902578f, 0.050000004f);
            type = FloatToInt(RandomSignedFloatRange(1.0f, 3.0f));
            scale = RandomFloatRange(0.3f, 1.0f) * 210000.0f;
            pos[0] = origin[0] + RandomSignedFloatRange(0, 0.3f);
            pos[1] = origin[1] + RandomSignedFloatRange(0, 0.3f);
            pos[2] = origin[2] + RandomSignedFloatRange(0, 0.3f);
            particle = SpawnSpinningSparkParticle(pos, 0, 1.0f, 1.01f, type, velocity, scale, 0x406080, 0);
            if (particle != 0) {
                *(short *)(particle + 0xA) = lifetime;
                particle[3] = 0x44;
                data = particle + 0x20;
                particle[9] = FloatToInt(4.0f) + 0x40;
                *(float *)(data + 0x1C) = IntToFloat(5);
                *(int *)(data + 4) = 3;
                data[0xA] = 0x20;
                data[0xB] = particle[0xA];
            }
        }
    }
}
