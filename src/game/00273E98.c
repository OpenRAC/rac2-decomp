#include "common.h"

extern void func_00274208(void *);
extern int func_002746C8(void *);
extern void func_00282F20(float, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00274A88(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_002AA2E8(float *, float, float);
extern void func_002ACE78(void *, void *, float);
extern void func_00283810(void *, void *, void *, float);
extern int func_002E5CF8(int, int, void *);
extern int func_002E5E58(int, int, void *);
extern int func_002E5F00(int, char *);
extern void func_00283028(void *, void *, void *);
extern float D_001BAFC0[];

/* Moves a physical camera object that bumps into walls, slows down and plays a bump sound. */
int func_00273E98(char *object)
{
    float delta[4];
    float direction[4];
    float scaled[4];
    float correction[4];
    float length;
    char *state = *(char **)(object + 0x68);
    char *orientation;
    float distance, step, factor;
    int sound;

    ApplyPathMoveStepCopy(object);
    if (PushMobyAwayFromHit(object)) {
        orientation = state + 0x10;
        vec_scale_to_length(1.0f, D_001BAFC0, D_001BAFC0);
        FastVecCross(delta, D_001BAFC0, state);
        ClampMovementVector(object, orientation, delta);
        ComputeViewDirection(object + 0x10, direction, 1);
        if (FastVecDot(direction, D_001BAFC0) > 0.7f) {
            distance = FastVecDot(state, D_001BAFC0);
            step = distance * 0.5f;
            if (FloatAbs(step) < 0.033333335f)
                step = 0.0f;
            vec_scale_to_length(distance + step, scaled, D_001BAFC0);
            FastVecSub(state, state, scaled);
            if (step == 0.0f) {
                length = FastVecLength(state);
                ApproachValue(&length, 0.033333335f, 0.0019444445f);
                vec_scale_to_length(length, state, state);
                FastVecCross(correction, state, D_001BAFC0);
                factor = FastVecLength(correction) * -0.5f;
                factor /= *(float *)(state + 0x2C);
                SetDirectionWithComplement(correction, correction, factor);
                FastVectorNormalize3(orientation, orientation, correction, 0.1f);
            }
            if (FloatAbs(distance) >= 0.033333335f) {
                if (*(u8 *)(state + 0x5E) != 0xFF)
                    sound = PlayMobySound(*(u8 *)(state + 0x5E), 0, object);
                else
                    sound = PlaySoundFromGlobalBank(8, 0, object);
                if (sound != -1)
                    SetVoicePositionOffset(sound, state + 0x20);
            }
        } else {
            FastVectorNormalize(state, state, D_001BAFC0);
        }
    }
    return 0;
}
