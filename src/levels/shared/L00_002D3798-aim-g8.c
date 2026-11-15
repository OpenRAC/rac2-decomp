#include "common.h"

typedef int HeroVector __attribute__((mode(TI)));
typedef struct {
    char matrix[0x100];
    char pad100[0x5C];
    float heading;
    char pad160[0x30];
    HeroVector motion;
    float motionHeight;
    float motionTarget;
    char pad1A8[0x10];
    int timer;
    char pad1BC[0x10C];
    float groundNormalZ;
    char pad2CC[0xF54];
    char *targetObject;
    char pad1224[0x230];
    short mode;
    char pad1456[0x6];
    float targetHeight;
    char pad1460[0x80];
    float direction[4];
    float pitchRate;
    float yawRate;
    union { float value; int bits; } blend;
    int blendTime;
    int active;
    char pad1504[0x8];
    int activeTime;
    char pad1510[0xD80];
    int probeFlags;
    int state;
} AimHero;
extern AimHero D_00189E20;
typedef struct { char pad[0x100]; float pitch, yaw; } AimInput;
typedef struct { char pad[0x18]; char *object; char unused[4]; float position[4]; } AimProbe;
extern AimInput D_00138180;
extern AimProbe D_L00_001BF200;
typedef struct { char pad[0x158]; float height; char pad15C[0x214]; HeroVector motion; } AimCamera;
extern AimCamera D_L00_001B8C80;
extern char D_L00_001B8FF0[];
extern int D_001A7BA4, D_L00_001A8FF0;
extern int D_L00_001A7CE8 __attribute__((sda));
extern float D_L00_001A7F9C __attribute__((sda)), D_L00_001A7FA0 __attribute__((sda));
extern float D_L00_001A7FA4 __attribute__((sda)), D_L00_001A7FA8 __attribute__((sda));
extern float D_L00_001A7FAC __attribute__((sda)), D_L00_001A7FB0 __attribute__((sda));
extern float D_L00_001A7FB4 __attribute__((sda)), D_L00_001A7FBC __attribute__((sda));
extern int func_L00_002D6418(void);
extern int func_L00_002D64B8(float *, float *, float *);
extern void func_L00_002D6588(void), func_L00_002D5940(void);
extern float func_00282DF0(void *), func_00282E20(void *), func_00283248(float,float);
extern void func_00282F20(void *,void *,float), func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,int,int);
extern float func_00282E48(void *,void *), func_00282C48(float), func_00282DB0(void *,void *);
extern void func_L00_002D3B58(void *,void *,float);
extern float func_00283BE0(float,float),func_00283B98(float,float);
/* EE argument banks are independent: target is $f12, output is $a0,
 * followed by the three $f13-$f15 rates/limit arguments. */
extern void func_002AAC80(float target, float *output, float rate, float acceleration, float limit);
extern void func_002AA2E8(float *,float,float);
extern void func_002AF000(void *,float,float,float), func_002A91F0(void *,void *);
extern void func_L00_002B3EF8(int,float,float,float);
#define HF(o) (*(float *)(hero + (o)))
#define HI(o) (*(int *)(hero + (o)))
/* Update the hero aim direction, collision-sensitive turn rates, and aim transitions. */
void func_L00_002D5158(void)
{
    char *hero;
    char *aim;
    float direction[4], local[4];
    float target, probeRate, probeLimit, rate, limit, yaw, pitch, yawScale, pitchScale, distance;
    float value, pitchBound;
    int hit;
    char *object;
    if (IsHeroActionAllowed()) {
        aim = (char *)&gHeroState + 0x14E0;
        if (FastVecLength(aim) == 0.0f)
            vec_scale_to_length(aim, aim - 0x14E0, 1.0f);
        hero = aim - 0x14E0;
        if (HF(0x2C8) > -0.99f)
            matrix_mul_vec3(aim, aim, aim - 0x14A0);
        yaw = FastMatrixHelperA(HF(0x14E0), HF(0x14E4));
        pitch = FastMatrixHelperA(vec_length_xy(aim), HF(0x14E8));
        if (GetHeroCameraParams(&target, &probeRate, &probeLimit)) {
            ApproachTargetWithBraking(-pitch, (float *)(aim + 0x10), probeRate, probeRate, probeLimit);
            value = fast_subtract_rotations(target, yaw);
            ApproachTargetWithBraking(value, (float *)(aim + 0x14), probeRate, probeRate, probeLimit);
        } else {
            distance = 0.0f;
            vec_scale_to_length(direction, D_L00_001B8FF0, 30.0f);
            hit = 0;
            FastVecAdd(direction, direction, D_L00_001B8FF0 - 0x230);
            if (CollLine(D_L00_001B8FF0 - 0x230, direction, 1, HI(0x2290), 0)) {
                char *probeObject = gCollisionResult.object;
                if (probeObject && *(short *)(*(char **)(probeObject + 0x24) + 0x46) == 5) {
                    distance = fast_vec_dist(D_L00_001B8FF0 - 0x230, gCollisionResult.position);
                    hit = 1;
                }
            }
            yawScale = FloatAbs(gPadState.yaw) < 1.0f ? 0.3f : 1.0f;
            pitchScale = FloatAbs(gPadState.pitch) < 1.0f ? 0.3f : 1.0f;
            if (hit) {
                if (yawScale > 0.6f) yawScale = 0.6f;
                if (pitchScale > 0.6f) pitchScale = 0.6f;
            }
            limit = -gPadState.pitch * 0.0002908882452175021f * D_L00_001A7F9C * pitchScale;
            rate = gPadState.yaw * 0.0002908882452175021f * D_L00_001A7FA0 * yawScale;
            if (D_001A7BA4) rate = -rate;
            if (hit) {
                float cap = D_L00_001A7FA0 * 0.0002908882452175021f;
                SetViewSpaceHeight(local, (char *)&gHeroState + 0x120, 0.0f);
                if (FloatAbs(gPadState.pitch) < 1.0f) {
                    float correction = FastVecDot(local, D_L00_001B8FF0 + 0x10);
                    correction = -(correction / distance) * D_L00_001A7FB4;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (gPadState.pitch == 0.0f) limit = correction;
                    else { limit -= correction; limit *= D_L00_001A7FBC; limit += correction; }
                }
                if (FloatAbs(gPadState.yaw) < 1.0f) {
                    float correction = FastVecDot(local, D_L00_001B8FF0 + 0x20);
                    correction = (correction / distance) * D_L00_001A7FB4;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (gPadState.yaw == 0.0f) rate = correction;
                    else { rate -= correction; rate *= D_L00_001A7FBC; rate += correction; }
                }
            }
            value = FloatAbs(gHeroState.pitchRate);
            if (FloatAbs(rate) < value || gHeroState.pitchRate * rate < 0.0f)
                ApproachValue(&gHeroState.pitchRate, rate, D_L00_001A7FB0 * 4.848137450608192e-06f);
            else
                ApproachValue(&gHeroState.pitchRate, rate, D_L00_001A7FA8 * (yawScale * 4.848137450608192e-06f));
            value = FloatAbs(gHeroState.yawRate);
            if (FloatAbs(limit) < value || gHeroState.yawRate * limit < 0.0f)
                ApproachValue(&gHeroState.yawRate, limit, D_L00_001A7FAC * 4.848137450608192e-06f);
            else
                ApproachValue(&gHeroState.yawRate, limit, D_L00_001A7FA4 * (pitchScale * 4.848137450608192e-06f));
        }
        yaw = FastAddRotations(yaw, gHeroState.yawRate);
        pitch = FastAddRotations(pitch, gHeroState.pitchRate);
        if (!D_L00_001A8FF0) yaw = FastAddRotations(yaw, gHeroState.heading);
        pitchBound = 1.483529999f;
        if (pitch > pitchBound) { pitch = pitchBound; gHeroState.pitchRate = 0; }
        else if (pitch < -pitchBound) { gHeroState.pitchRate = 0; pitch = -pitchBound; }
        aim = (char *)&gHeroState + 0x14E0;
        BuildSphericalOffset(aim, 1.0f, yaw, pitch);
        hero = aim - 0x14E0;
        if (gHeroState.groundNormalZ > -0.99f) matrix_mul_vec3(aim, aim, hero);
        UpdateHeroCameraBlock();
        if (!GetHeroCameraParams(0, 0, 0)) {
            AimCamera *camera = &D_L00_001B8C80;
            *(short *)(hero + 0x1454) = 2;
            *(float *)(hero + 0x1A0) = camera->height;
            camera = (AimCamera *)((char *)camera + 0x370);
            qcopy(aim - 0x1350, camera);
            *(float *)(hero + 0x1A4) = *(float *)(hero + 0x145C);
            SteerHeroHeading(0, 0.037f, 0.25f, 0.2036217749f);
        }
    }
    if (IsHeroActionAllowed() || ((gHeroState.state == 1 || gHeroState.state == 0x1D) && gHeroState.timer >= D_L00_001A7CE8)) {
        if (!gHeroState.active) {
            object = gHeroState.targetObject;
            if (object && *(short *)(object + 0xAA) != 0x47 /* moby class 71 */) {
                FastVecSub((char *)&gHeroState + 0x14A0, object + 0x10, (char *)&gHeroState + 0x80);
                matrix_mul_vec3((char *)&gHeroState + 0x14A0, (char *)&gHeroState + 0x14A0, (char *)&gHeroState + 0x40);
                BuildRotationFromAngles((char *)&gHeroState + 0x14B0, object + 0xF0);
            }
            gHeroState.active = 1;
            gHeroState.blend.bits = 0;
            gHeroState.blendTime = 0;
            gHeroState.activeTime = 0;
        }
    } else if (gHeroState.state != 1 && gHeroState.state != 0x1D) {
        char *oldObject;
        if (!gHeroState.active) return;
        UpdateHeroHeldObject();
        oldObject = gHeroState.targetObject;
        if (oldObject && *(short *)(oldObject + 0xAA) != 0x47 /* moby class 71 */) {
            FastVecSub((char *)&gHeroState + 0x14A0, oldObject + 0x10, (char *)&gHeroState + 0x80);
            matrix_mul_vec3((char *)&gHeroState + 0x14A0, (char *)&gHeroState + 0x14A0, (char *)&gHeroState + 0x40);
            gHeroState.blendTime = 0;
            gHeroState.blend.value = 1.0f;
        }
        gHeroState.active = 0;
    }
    if (gHeroState.active) UpdateHeroHeldObject();
}
