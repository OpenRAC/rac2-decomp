/* func_0030CCD0: beam chain update, the small cousin of the F4 family's chain loop. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector start, end;
    void *target;
    float length;
    int unknown28, timer, light, fade;
    short segment;
} BeamState;
typedef struct { char pad[0x10]; Vector pos; } Thing;
typedef struct { char pad[0x10]; float height; } ThingInfo;
typedef struct { char pad[0x68]; BeamState *vars; } Actor;

extern int D_001A79F0;
extern int D_L00_001A8F00;
extern BeamState D_L00_001C5890[], D_L00_001C58E0[];
typedef union { u8 b[0x2600]; s32 i[0x980]; void *ptr[0x980]; } Hero;
extern char D_00189E20[];
extern float D_L00_001AF2E4 __attribute__((sda));
extern float D_L00_001AF2F0 __attribute__((sda)), D_L00_001AF2F4 __attribute__((sda)), D_L00_001AF2F8 __attribute__((sda));
extern float D_L00_001AF2FC __attribute__((sda)), D_L00_001AF300 __attribute__((sda)), D_L00_001AF304 __attribute__((sda));
extern float D_L00_001AF308 __attribute__((sda)), D_L00_001AF30C __attribute__((sda)), D_L00_001AF310 __attribute__((sda));
extern float D_L00_001AF314 __attribute__((sda)), D_L00_001AF318 __attribute__((sda)), D_L00_001AF31C __attribute__((sda));
extern float D_L00_001AF320 __attribute__((sda)), D_L00_001AF334 __attribute__((sda)), D_L00_001AF338 __attribute__((sda));
extern float D_L00_001AF384 __attribute__((sda));
extern Vector D_L00_0023A210[2][20], D_L00_0023A340[], D_L00_0023A4E0[];
extern float D_L00_0023A490[], D_L00_0023A620[];
extern char D_L00_001A8F20[] MACRO_ADDR;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern ThingInfo *func_002AB1F0(void *);
extern float func_002ABB18(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern float func_00282DF0(void *);
extern float func_00283180(float);
extern unsigned int func_0030CAA0(void);

/* Moves the twenty points of the beam chain so they trail from the start toward the locked target. The chain waves about and sheds spark particles. */
void func_0030CCD0(Actor *actor)
{
    Vector goal, dir, side, step, last, delta, tip;
    float angle;
    float len;
    float *waveOffset;
    int byteOffset;
    float dist;
    void *target;
    float previousWave;
    int spin;
    float stepLength;
    float weight;
    float wave;
    int i;
    float sway;
    void *heroTarget;
    BeamState *beam = actor->vars;
    float zero;
    Vector *lastPtr;
    ThingInfo *info;
    float segmentsLeft;

    if (gCurrentMapIndex == 1 && D_L00_001A8F00 == 2)
        beam = D_L00_001C5890;
    if (gCurrentMapIndex == 0x14 && D_L00_001A8F00 == 2)
        beam = D_L00_001C58E0;
    len = D_L00_001AF2E4 * 0.05f;
    D_L00_001AF2FC = FastAddRotations(D_L00_001AF2FC, D_L00_001AF300);
    D_L00_001AF304 = fast_subtract_rotations(D_L00_001AF304, D_L00_001AF308);
    D_L00_001AF318 = FastAddRotations(D_L00_001AF318, D_L00_001AF31C);
    heroTarget = 0;
    if (beam->target == 0)
        heroTarget = ((Hero *)gHeroState)->ptr[0x5C0 / 4];
    if (heroTarget != 0) {
        if (beam->target == 0)
            beam->target = heroTarget;
    }
    target = beam->target;
    if (target != 0) {
        info = 0;
        if (D_L00_001A8F00 != 2)
            info = GetMobyPrivateValue0(target);
        qcopy(&goal, &((Thing *)beam->target)->pos);
        if (info != 0)
            goal.f[2] += info->height;
        else
            goal.f[2] += 0.2f;
        len = fast_vec_dist(beam, &goal) * 0.05f;
    }
    beam->segment = 0x14;
    FastVecSub(&dir, &beam->end, beam);
    vec_scale_to_length(&dir, &dir, 1.0f);
    if (beam->target != 0) {
        FastVecCross(&side, &dir, gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(&dir, &dir, &side, 0.17453295f);
    }
    FastVecScale(&last, &dir, len);
    qcopy(D_L00_0023A210[0], beam);
    qcopy(D_L00_0023A210[1], beam);
    i = 1;
    do {
        float fi = i;
        byteOffset = i * 4;
        weight = IntToFloat(i) * 0.05f;
        wave = D_L00_001AF2F4 + (D_L00_001AF2F8 - D_L00_001AF2F4) * weight;
        wave = wave * FastSinOrCosB(WrapAngleToPi(D_L00_001AF2FC + fi * D_L00_001AF2F0));
        wave = wave + RandomSignedFloatRange(D_L00_001AF334, D_L00_001AF338);
        waveOffset = (float *)(byteOffset + (char *)D_L00_0023A490);
        previousWave = *waveOffset;
        *waveOffset = wave;
        D_L00_0023A210[0][i].f[2] -= previousWave;
        FastVecSub(&side, &D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        lerp_vector(&step, &side, &last, 0.85f);
        zero = 0.0f;
        stepLength = FastVecLength(&step);
        if (stepLength == zero) {
            qcopy(&D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        } else {
            FastVecScale(&step, &step, len / stepLength);
            FastVecAdd(&D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1], &step);
            qcopy(&last, &step);
        }
        D_L00_0023A210[0][i].f[2] += wave;
        FastVecSub(&side, &D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        if (beam->target != 0) {
            FastVecSub(&tip, &goal, &D_L00_0023A210[0][i]);
            dist = FastVecLength(&tip);
            if (dist != zero) {
                if (i == 0x13) {
                    sway = 0.5f;
                    len = dist;
                } else if (i >= 0x10) {
                    sway = 0.5f;
                    segmentsLeft = IntToFloat(0x13 - i);
                    len = dist / segmentsLeft;
                } else {
                    sway = 0.1f;
                }
                /* Live across the next call: loop.c hoists this copy, which retail's preheader order shows. */
                lastPtr = &last;
                FastVecScale(&tip, &tip, len / dist);
                lerp_vector(lastPtr, lastPtr, &tip, sway);
            }
        }
        angle = WrapAngleToPi(D_L00_001AF304 + (float)i * D_L00_001AF30C);
        wave = D_L00_001AF310 * FastSinOrCosB(WrapAngleToPi(D_L00_001AF318 + (float)i * D_L00_001AF320));
        qcopy(&D_L00_0023A210[1][i], &D_L00_0023A210[0][i]);
        wave = wave * FastSinOrCosB(angle);
        D_L00_0023A620[i] = wave;
        D_L00_0023A210[1][i].f[2] += wave;
        wave = FastAddRotations(FastMatrixHelperA(side.f[0], side.f[1]), 1.5707965f);
        {
            float r2 = D_L00_001AF314 * FastSinOrCosA(angle);
            delta.f[0] = FastSinOrCosA(wave) * r2;
            delta.f[1] = FastSinOrCosB(wave) * r2;
        }
        delta.f[2] = 0.0f;
        qcopy(&D_L00_0023A4E0[i], &delta);
        FastVecAdd(&D_L00_0023A210[1][i], &D_L00_0023A210[1][i], &delta);
        i++;
    } while (i < 0x14);
    qcopy(&beam->end, D_L00_0023A340);
    {
        float pitch = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        float yaw = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(&tip, &dir, D_L00_001AF384);
        ApplyAxisRotationToQuaternion(&tip, &tip, gHeroState + 0x740, yaw);
        ApplyAxisRotationToQuaternion(&tip, &tip, gHeroState + 0x750, pitch);
    }
    spin = RandomIntRange(1, 8);
    if (RandomIntBelow(2))
        spin = -spin;
    wave = RandomFloatRange(0.2f, 0.6f);
    SpawnGroundEffectParticle(beam, 0xF, wave * 0.3f, wave, GetBeamGlowColor() | 0x7F000000, 0, spin, &tip, 0, 0.0f);
    SpawnGroundEffectParticle(beam, 0xF, wave * 0.15f, wave * 0.5f, 0x307F7F7F, 0, -spin, &tip, 0, 0.0f);
    spin = RandomIntRange(1, 8);
    if (RandomIntBelow(2))
        spin = -spin;
    wave = RandomFloatRange(0.15f, 3.0f);
    SpawnGroundEffectParticle(&beam->end, 0xC, wave * 0.1f, wave, GetBeamGlowColor() | 0x7F000000, 0, spin, D_L00_001A8F20, 0, 0.0f);
}
