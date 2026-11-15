#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

extern float func_002AA140(float, float, float);

/* Blends each of the four parts of one vector toward another by the given amount. */
void func_L00_0031D670(f32 *out, const f32 *from, const f32 *to, f32 amount) {
    u128 fromVec, toVec;
    f32 *fromF = (f32 *)&fromVec;
    f32 *toF = (f32 *)&toVec;
    fromVec = *(const u128 *)from;
    toVec = *(const u128 *)to;

    out[0] = LerpFloat_002AA140(fromF[0], toF[0], amount);
    out[1] = LerpFloat_002AA140(fromF[1], toF[1], amount);
    out[2] = LerpFloat_002AA140(fromF[2], toF[2], amount);
    out[3] = LerpFloat_002AA140(fromF[3], toF[3], amount);
}
