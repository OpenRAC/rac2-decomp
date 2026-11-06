/* func_PAL_L02_003ED620, the PAL copy of func_L02_003E91F0: the same C, where wrap D_L02_001B0CAC (({e}) * 1.2f). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L02_001B0BA8 __attribute__((sda));
extern float D_L02_001B0C1C __attribute__((sda)), D_L02_001B0C20 __attribute__((sda)), D_L02_001B0C24 __attribute__((sda));
extern float D_L02_001B0C28 __attribute__((sda)), D_L02_001B0C2C __attribute__((sda));
extern float D_L02_001B0C30 __attribute__((sda)), D_L02_001B0C34 __attribute__((sda));
extern float D_L02_001B0C38 __attribute__((sda)), D_L02_001B0C3C __attribute__((sda)), D_L02_001B0C40 __attribute__((sda));
extern float D_L02_001B0C44 __attribute__((sda)), D_L02_001B0C48 __attribute__((sda)), D_L02_001B0C4C __attribute__((sda));
extern float D_L02_001B0C60 __attribute__((sda)), D_L02_001B0C64 __attribute__((sda));
extern float D_L02_001B0CAC __attribute__((sda));
extern int D_L02_001B0C7C __attribute__((sda));
extern float D_L02_00249090[2][20][4];
extern float D_L02_00249310[20], D_L02_00249360[20][4], D_L02_002494A0[20];
typedef union { char b[0x2600]; float f[0x980]; Quad q[0x260]; } Hero;
extern char D_00189E20[];
extern char D_L02_001A8F20[] __attribute__((sda));
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern int func_002AB1F0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int), func_002ABB18(float), func_00283198(float), func_00283180(float), func_002A78D8(float, float);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float), func_002A7878(float, float);
extern int func_002A7820(int, int), func_002A77E0(int);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
typedef struct {
    char pad[0x20];
    float start[4];
    float end[4];
    char gap[0x0C];
    char *target;
    int count;
} TetherState;
/* Relaxes and animates a pair of twenty-point tether strands, then emits sparks. */
void func_PAL_L02_003ED620(char *actor) {
    TetherState *state = *(TetherState **)(actor + 0x68);
    float endpoint[4], direction[4], delta[4], blended[4], tangent[4], sideways[4], toward[4];
    float length = D_L02_001B0BA8 * 0.05f;
    float phase, span, distance, oscillation, lateral, radius;
    int spin;
    D_L02_001B0C28 = func_00283B98(D_L02_001B0C28, D_L02_001B0C2C);
    D_L02_001B0C30 = func_00283BE0(D_L02_001B0C30, D_L02_001B0C34);
    D_L02_001B0C44 = func_00283B98(D_L02_001B0C44, D_L02_001B0C48);
    if (state->target) {
        char *settings = (char *)func_002AB1F0(state->target);
        qcopy(endpoint, state->target + 0x10);
        endpoint[2] += *(float *)(settings + 0x10);
        length = func_00282E48(state->start, endpoint) * 0.05f;
    }
    state->count = 20;
    func_00282CF0(direction, state->end, state->start);
    func_00282F20(direction, direction, 1.0f);
    if (state->target) {
        func_00282DD8(delta, direction, &((Hero *)D_00189E20)->q[0x2C0 / 16]);
        func_002ACEC0(direction, direction, delta, 0.17453295f);
    }
    func_00282D30(tangent, direction, length);
    qcopy(D_L02_00249090[0][0], state->start);
    qcopy(D_L02_00249090[1][0], state->start);
    {
    /* i is declared here, after the setup code: its later pseudo number sets the gcse order of the spilled state->start/state->end/i*4 copies. */
    int i;
    for (i = 1; i < 20; i++) {
        float value, height, zero;
        float *point;
        height = func_00283CE0(i);
        height = D_L02_001B0C20 + (D_L02_001B0C24 - D_L02_001B0C20) * (height * 0.05f);
        height *= func_00283198(func_002ABB18(D_L02_001B0C28 + (float)i * D_L02_001B0C1C));
        height += func_002A78D8(D_L02_001B0C60, D_L02_001B0C64);
        D_L02_00249090[0][i][2] -= D_L02_00249310[i];
        D_L02_00249310[i] = height;
        func_00282CF0(delta, D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        func_00282D08(blended, delta, tangent, 0.85f);
        span = func_00282DF0(blended);
        zero = 0.0f;
        if (span == zero) qcopy(D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        else {
            func_00282D30(blended, blended, length / span);
            func_00282CC0(D_L02_00249090[0][i], D_L02_00249090[0][i - 1], blended);
            qcopy(tangent, blended);
        }
        D_L02_00249090[0][i][2] += height;
        func_00282CF0(delta, D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        if (state->target) {
            func_00282CF0(toward, endpoint, D_L02_00249090[0][i]);
            distance = func_00282DF0(toward);
            if (distance != zero) {
                if (i == 19) { length = distance; height = 0.5f; }
                else if (i >= 16) {
                    float remaining = func_00283CE0(19 - i);
                    height = 0.5f;
                    length = distance / remaining;
                }
                else height = 0.1f;
                func_00282D30(toward, toward, length / distance);
                func_00282D08(tangent, tangent, toward, height);
            }
        }
        value = func_002ABB18(D_L02_001B0C30 + (float)i * D_L02_001B0C38);
        oscillation = func_002ABB18(D_L02_001B0C44 + (float)i * D_L02_001B0C4C);
        height = D_L02_001B0C3C * func_00283198(oscillation);
        qcopy(D_L02_00249090[1][i], D_L02_00249090[0][i]);
        height *= func_00283198(value);
        D_L02_002494A0[i] = height;
        point = D_L02_00249090[0][i];
        point[82] += height;
        height = func_00283B98(func_00283248(delta[0], delta[1]), 1.5707965f);
        lateral = D_L02_001B0C40 * func_00283180(value);
        sideways[0] = func_00283180(height) * lateral;
        sideways[1] = func_00283198(height) * lateral;
        sideways[2] = 0;
        qcopy(D_L02_00249360[i], sideways);
        func_00282CC0(D_L02_00249090[1][i], D_L02_00249090[1][i], sideways);
    }
    }
    qcopy(state->end, D_L02_00249090[0][19]);
    oscillation = func_002A78D8(0.52359885f, 1.0471977f);
    phase = func_002A7878(-0.52359885f, 1.0471977f);
    func_00282D30(toward, direction, ((D_L02_001B0CAC) * 1.2f));
    func_002ACEC0(toward, toward, &((Hero *)D_00189E20)->q[0x740 / 16], phase);
    func_002ACEC0(toward, toward, &((Hero *)D_00189E20)->q[0x750 / 16], oscillation);
    spin = func_002A7820(1, 8);
    if (func_002A77E0(2)) spin = -spin;
    radius = func_002A7878(0.2f, 0.6f);
    func_002C2210(state->start, 12, radius * 0.3f, radius, D_L02_001B0C7C | 0x7F000000, 0, spin, toward, 0, 0.0f);
    func_002C2210(state->start, 12, radius * 0.15f, radius * 0.5f, 0x307F7F7F, 0, -spin, toward, 0, 0.0f);
    spin = func_002A7820(1, 8);
    if (func_002A77E0(2)) spin = -spin;
    radius = func_002A7878(0.15f, 3.0f);
    func_002C2210(state->end, 10, radius * 0.1f, radius, D_L02_001B0C7C | 0x7F000000, 0, spin, D_L02_001A8F20, 0, 0.0f);
}
