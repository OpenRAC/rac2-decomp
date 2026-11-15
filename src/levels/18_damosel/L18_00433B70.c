#include "common.h"

extern void func_L11_003F4198(void *, int, void *, float);
extern void func_L18_00434510(void *, int, int, int, int, float, float);
extern void func_002ACB48(void *, float);
extern void func_002A7A00(void *, float, float);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_0029FCC0(void *, int, void *);
/* EE register-bank argument order is unchanged by the FP interleaving. */
extern void func_L02_003FFC48(void *, int, float, int, float, int, int);

/* The two records at state + 0x610/+0x6B0 share this layout. The updater
* at 0x434128 reads angles, angular steps and radii at +0x40/+0x60/+0x80;
* its initializer at 0x433460 writes both vectors of the last two fields. */
typedef struct {
    float endpoints[2][4];
    float tangents[2][4];
    float angles[2][4];
    float angularSteps[2][4];
    float radii[2][4];
} L18ArcControl;

/* Draws the crackling lightning on both sides of the Extermibot beam, with extra branches when the beam is strong, plus glows at both ends. */
void func_L18_00433B70(u8 *obj) {
    L18ArcControl control __attribute__((aligned(16)));
    float branch[6][4] __attribute__((aligned(16)));
    u8 *state  =  *(u8 **)(obj + 0x68);
    float width  =  0.02f;
    int active  =  (u16)(*(u16 *)(state + 0x806) - 2) < 3;
    int strong  =  (u16)(*(u16 *)(state + 0x806) - 2) < 2;
    int count;
    float (*path)[4];
    int life;
    float size, speed, scale, half;
    if (active) width  =  0.08f;
    count  =  active ? 12 : 8;
    path  =  __builtin_alloca(count * 16);
    life  =  strong ? RandomIntRange(48, 128) : RandomIntRange(48, 80);
    size  =  strong ? RandomFloatRange(0.02f, 0.12f) : RandomFloatRange(0.02f, 0.07f);
    speed  =  strong ? RandomFloatRange(2.0f, 6.0f) : RandomFloatRange(2.0f, 3.0f);
    BuildJitteredCurvePointsAlt(path, count, state + 0x610, width);
    DrawLightningRibbon_L18(path, count, life, 0x60FFFFFF, 0x30FF0000, size, speed);
    if ((unsigned)(*(u16 *)(state + 0x806) - 2) < 2) {
        qcopy(control.endpoints[0], path[RandomIntRange(count - 6, count - 3)]);
        qcopy(control.endpoints[1], path[count - 2]);
        AddRandomOffsetToVector(control.endpoints[1], 1.0f);
        RandomDirectionVector(control.tangents[0], 1.0f, 2.0f);
        RandomDirectionVector(control.tangents[1], 1.0f, 2.0f);
        life = RandomIntRange(48, 96);
        size = RandomFloatRange(0.02f, 0.08f);
        speed = RandomFloatRange(2.0f, 3.0f);
        BuildJitteredCurvePointsAlt(branch, 6, &control, 0.05f);
        DrawLightningRibbon_L18(branch, 6, life, 0x60FF3030, 0x30FF0000, size, speed);
    }
    life  =  strong ? RandomIntRange(48, 128) : RandomIntRange(48, 80);
    size  =  strong ? RandomFloatRange(0.02f, 0.12f) : RandomFloatRange(0.02f, 0.07f);
    speed  =  strong ? RandomFloatRange(2.0f, 6.0f) : RandomFloatRange(2.0f, 3.0f);
    BuildJitteredCurvePointsAlt(path, count, state + 0x6B0, width);
    DrawLightningRibbon_L18(path, count, life, 0x60FFFFFF, 0x30FF0000, size, speed);
    if ((unsigned)(*(u16 *)(state + 0x806) - 2) < 2) {
        qcopy(control.endpoints[0], path[RandomIntRange(count - 6, count - 3)]);
        qcopy(control.endpoints[1], path[count - 2]);
        AddRandomOffsetToVector(control.endpoints[1], 1.0f);
        RandomDirectionVector(control.tangents[0], 1.0f, 2.0f);
        RandomDirectionVector(control.tangents[1], 1.0f, 2.0f);
        life = RandomIntRange(48, 96);
        size = RandomFloatRange(0.02f, 0.08f);
        speed = RandomFloatRange(2.0f, 3.0f);
        BuildJitteredCurvePointsAlt(branch, 6, &control, 0.05f);
        DrawLightningRibbon_L18(branch, 6, life, 0x60FF3030, 0x30FF0000, size, speed);
    }
    scale  =  *(float *)(state + 0x7E0) * 2.0f + 1.0f;
    TransformMobyJointToWorld(*(void **)(state + 0x7C8), 0, control.endpoints[0]);
    TransformMobyJointToWorld(*(void **)(state + 0x7C8), 1, control.endpoints[1]);
    half = scale * 0.5f;
    {
        int glowLife = RandomIntRange(80, 96);
        float angle = RandomAngle();
        DrawAimedEffectPacket(control.endpoints[0], 0x807070, half, glowLife, angle, 49, 2);
    }
    scale = scale * 0.7f;
    {
        int glowLife = RandomIntRange(8, 22);
        float angle = RandomAngle();
        DrawAimedEffectPacket(control.endpoints[0], 0x802020, scale, glowLife, angle, 11, 2);
    }
    {
        int glowLife = RandomIntRange(80, 96);
        float angle = RandomAngle();
        DrawAimedEffectPacket(control.endpoints[1], 0x807070, half, glowLife, angle, 49, 2);
    }
    {
        int glowLife = RandomIntRange(8, 22);
        float angle = RandomAngle();
        DrawAimedEffectPacket(control.endpoints[1], 0x802020, scale, glowLife, angle, 11, 2);
    }
}
