/* Updates motion and clamps the independent yaw and pitch components.
 * Full position transfers use the approved helper; the measured speed local is scalar. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2444 __attribute__((sda));

extern float D_L20_001B2448 __attribute__((sda));

extern float D_L20_001B244C __attribute__((sda));

extern float func_00282DF0(void *);

extern void func_002AAC80(void *, float, float, float, float);

extern void func_002AFDD8(char *, char *, char *, char *);

extern int func_L07_00321D68(char *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

float func_L20_0044A8F0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *v = state + 0x180;
    char *src = arg0 + 0x10;
    float b0[4] __attribute__((aligned(16)));
    float b1[4] __attribute__((aligned(16)));
    float speed;
    float f;
    float a;
    float gain;
    float pitch;

    FastVecSub(b0, state + 0x190, state + 0x180);
    speed = FastVecLength(state + 0xF0);
    f = FastVecLength(b0);
    func_002AAC80(&speed, f, D_L20_001B2444 * 0.00027777778f,
                  D_L20_001B2444 * 0.00027777778f,
                  D_L20_001B2448 * 0.016666668f);
    vec_scale_to_length(state + 0xF0, b0, speed);
    qcopy(src, v);
    func_L07_00321D68(arg0, state + 0xF0);
    qcopy(v, src);
    func_002AFDD8(arg0, b1, state + 0xF0, 0);
    gain = D_L20_001B244C;
    a = b1[1] * -gain;
    *(float *)(state + 0x1A8) = a;
    *(float *)(state + 0x1AC) = b1[0] * gain;
    if (a > 0.78539824f) {
        *(float *)(state + 0x1A8) = 0.78539824f;
    } else if (a < -0.78539824f) {
        *(float *)(state + 0x1A8) = -0.78539824f;
    }
    pitch = *(float *)(state + 0x1AC);
    if (pitch > 0.78539824f) {
        *(float *)(state + 0x1AC) = 0.78539824f;
    } else if (pitch < 0.0f) {
        *(float *)(state + 0x1AC) = 0.0f;
    }
    return f;
}
