/* Creates the child, copies both full vectors and initializes its motion.
 * Returns the created object or null; the fifth integer slot and float input are preserved. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2470 __attribute__((sda));
extern int D_L20_001B246C __attribute__((sda));

extern void *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern float func_002A7940(void);
extern float func_002A7878(float a, float b);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L11_00460258(char *, int);
extern int func_002E5DA0(int, int, char *, int);

/* Creates a homing shot (moby class 4855) at a position, aimed at a target, and returns it. */
char *func_L20_0044B100(char *template, char *position, char *direction, char *targetPos, int travelFrames,
                        float power) {
    char *shot;
    char *state;
    char *pos;
    TI128 predicted;
    float value;

    shot = CreateMoby(0x12F7 /* moby class 4855 */);
    if (shot != 0) {
        InitChildObjectFromParent((u8 *)shot, (u8 *)template);
        pos = shot + 0x10;
        qcopy(pos, position);
        *(float *)(shot + 0x2C) =
            *(float *)(*(u32 *)(shot + 0x24) + 0x24) * D_L20_001B2470;
        state = *(char **)(shot + 0x68);
        qcopy(state, direction);
        *(float *)(state + 0x20) = power;
        *(float *)(state + 0x24) = RandomAngle();
        *(float *)(state + 0x28) = RandomFloatRange(0.052359886f, 0.10471977f);
        *(int *)(state + 0x30) = 0;
        value = IntToFloat(travelFrames);
        *(float *)(state + 0x34) = 1.0f / value;
        FastVecScale(&predicted, direction, (float)(travelFrames >> 1));
        FastVecAdd(&predicted, &predicted, position);
        FastVecSub(state + 0x10, targetPos, &predicted);
        value = FastVecLength(state);
        vec_scale_to_length(state + 0x10, state + 0x10, value);
        SpawnSparkRing_L11(pos, D_L20_001B246C);
        PlaySoundFromClassBank(0, 0, shot, 0x12F7);
    }
    return shot;
}
