#include "common.h"
typedef int TQ __attribute__((mode(TI)));

extern void func_L00_002D7958(float *dst, void *src, float x);
extern void func_L00_002D7940(char *p);
extern void func_L00_002EE0C0(char *p);
extern void func_L00_00427B40(char *p);

/* Copies the full aligned target vector into both state slots, records the
 * weight and refreshes the two five-float blend records and owner transform. */
/* Sets the camera's target position and blend weight, then refreshes the camera state. */
void func_L00_00427BE8(char *camera, void *blendSource, TQ *targetVec, f32 weightIn)
{
    char *state = *(char **)(camera + 0x70);
    char *target = state + 0xB0;
    f32 weight = weightIn;

    qcopy(target, targetVec);
    qcopy(state + 0x80, targetVec);
    *(f32 *)(target + 0x18) = weight;
    CopyVec5WithFirstBlended((float *)(state + 0x14), blendSource, weight);
    CopyVec5WithFirstBlended((float *)(camera + 0x50), blendSource, 0.0f);
    ZeroFiveWords(state);
    func_L00_002EE0C0(state + 0x90);
    UpdateCameraAnglesToTarget(camera);
}
