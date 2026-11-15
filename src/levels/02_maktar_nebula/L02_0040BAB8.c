/* Choose a randomized point around the supplied full vector and store it in the private state.
 * The shared helper transfers the complete aligned 16-byte input vector.
 */
#include "common.h"

extern float func_00283248(float,float),func_002A7878(float,float);
extern float func_00283180(float),func_00283198(float);

/* Picks a random spot near the target, a few steps away from the object, and stores it as the place the robot should walk to. */
void func_L02_0040BAB8(u8 *moby, float *target) {
    float angle, distance, offsetX, cosAngle;
    u8 *vars;

    angle = FastMatrixHelperA(*(float *)(moby + 0x10) - target[0], *(float *)(moby + 0x14) - target[1]);
    angle = angle + RandomFloatRange(-0.7853982448577881f, 0.7853982448577881f);
    distance = RandomFloatRange(-2.0f, 2.0f) + 8.0f;
    vars = *(u8 **)(moby + 0x68);
    qcopy(vars + 0x2C0, target);
    offsetX = distance * FastSinOrCosA(angle);
    *(float *)(vars + 0x2C0) = *(float *)(vars + 0x2C0) + offsetX;
    cosAngle = FastSinOrCosB(angle);
    *(float *)(vars + 0x2C4) = *(float *)(vars + 0x2C4) + distance * cosAngle;
}
