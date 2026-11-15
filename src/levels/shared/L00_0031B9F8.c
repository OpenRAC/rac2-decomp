#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef int s32;

extern int FloatToInt(float);
extern float IntToFloat(int);

/* Works out how far a falling object ends up after a whole number of steps, and optionally reports the step count. */
f32 math_compute_falling_step_offset(const f32 *start, const f32 *velocity, s32 *outIndex, f32 gravity) {
    s32 stepCount = FloatToInt(velocity[2] / gravity);
    f32 velocityTerm = IntToFloat(stepCount);
    f32 gravityTerm = IntToFloat((stepCount * stepCount + stepCount) >> 1);
    f32 result = start[2] + velocity[2] * velocityTerm - gravityTerm * gravity;

    if (outIndex != 0)
        *outIndex = stepCount;
    return result;
}
