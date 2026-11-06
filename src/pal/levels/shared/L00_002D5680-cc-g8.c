/* func_PAL_L00_002D5680, the PAL copy of func_L00_002D5158: the same C, where rename func_L00_002D64B8 becomes func_PAL_L00_002D6A08; rename func_L00_002D6588 becomes func_PAL_L00_002D6AD8; rename func_L00_002D5940 becomes func_PAL_L00_002D5E90; scale D_L00_001A7CE8. */
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
extern int func_PAL_L00_002D6A08(float *, float *, float *);
extern void func_PAL_L00_002D6AD8(void), func_PAL_L00_002D5E90(void);
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
void func_PAL_L00_002D5680(void)
{
    char *hero;
    char *aim;
    float direction[4], local[4];
    float target, probeRate, probeLimit, rate, limit, yaw, pitch, yawScale, pitchScale, distance;
    float value, pitchBound;
    int hit;
    char *object;
    if (func_L00_002D6418()) {
        aim = (char *)&D_00189E20 + 0x14E0;
        if (func_00282DF0(aim) == 0.0f)
            func_00282F20(aim, aim - 0x14E0, 1.0f);
        hero = aim - 0x14E0;
        if (HF(0x2C8) > -0.99f)
            func_00283098(aim, aim, aim - 0x14A0);
        yaw = func_00283248(HF(0x14E0), HF(0x14E4));
        pitch = func_00283248(func_00282E20(aim), HF(0x14E8));
        if (func_PAL_L00_002D6A08(&target, &probeRate, &probeLimit)) {
            func_002AAC80(-pitch, (float *)(aim + 0x10), probeRate, probeRate, probeLimit);
            value = func_00283BE0(target, yaw);
            func_002AAC80(value, (float *)(aim + 0x14), probeRate, probeRate, probeLimit);
        } else {
            distance = 0.0f;
            func_00282F20(direction, D_L00_001B8FF0, 30.0f);
            hit = 0;
            func_00282CC0(direction, direction, D_L00_001B8FF0 - 0x230);
            if (func_002761F8(D_L00_001B8FF0 - 0x230, direction, 1, HI(0x2290), 0)) {
                char *probeObject = D_L00_001BF200.object;
                if (probeObject && *(short *)(*(char **)(probeObject + 0x24) + 0x46) == 5) {
                    distance = func_00282E48(D_L00_001B8FF0 - 0x230, D_L00_001BF200.position);
                    hit = 1;
                }
            }
            yawScale = func_00282C48(D_00138180.yaw) < 1.0f ? 0.3f : 1.0f;
            pitchScale = func_00282C48(D_00138180.pitch) < 1.0f ? 0.3f : 1.0f;
            if (hit) {
                if (yawScale > 0.6f) yawScale = 0.6f;
                if (pitchScale > 0.6f) pitchScale = 0.6f;
            }
            limit = -D_00138180.pitch * 0.0003490659f * D_L00_001A7F9C * pitchScale;
            rate = D_00138180.yaw * 0.0003490659f * D_L00_001A7FA0 * yawScale;
            if (D_001A7BA4) rate = -rate;
            if (hit) {
                float cap = D_L00_001A7FA0 * 0.0003490659f;
                func_L00_002D3B58(local, (char *)&D_00189E20 + 0x120, 0.0f);
                if (func_00282C48(D_00138180.pitch) < 1.0f) {
                    float correction = func_00282DB0(local, D_L00_001B8FF0 + 0x10);
                    correction = -(correction / distance) * D_L00_001A7FB4;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (D_00138180.pitch == 0.0f) limit = correction;
                    else { limit -= correction; limit *= D_L00_001A7FBC; limit += correction; }
                }
                if (func_00282C48(D_00138180.yaw) < 1.0f) {
                    float correction = func_00282DB0(local, D_L00_001B8FF0 + 0x20);
                    correction = (correction / distance) * D_L00_001A7FB4;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (D_00138180.yaw == 0.0f) rate = correction;
                    else { rate -= correction; rate *= D_L00_001A7FBC; rate += correction; }
                }
            }
            value = func_00282C48(D_00189E20.pitchRate);
            if (func_00282C48(rate) < value || D_00189E20.pitchRate * rate < 0.0f)
                func_002AA2E8(&D_00189E20.pitchRate, rate, D_L00_001A7FB0 * 6.981318e-06f);
            else
                func_002AA2E8(&D_00189E20.pitchRate, rate, D_L00_001A7FA8 * (yawScale * 6.981318e-06f));
            value = func_00282C48(D_00189E20.yawRate);
            if (func_00282C48(limit) < value || D_00189E20.yawRate * limit < 0.0f)
                func_002AA2E8(&D_00189E20.yawRate, limit, D_L00_001A7FAC * 6.981318e-06f);
            else
                func_002AA2E8(&D_00189E20.yawRate, limit, D_L00_001A7FA4 * (pitchScale * 6.981318e-06f));
        }
        yaw = func_00283B98(yaw, D_00189E20.yawRate);
        pitch = func_00283B98(pitch, D_00189E20.pitchRate);
        if (!D_L00_001A8FF0) yaw = func_00283B98(yaw, D_00189E20.heading);
        pitchBound = 1.483529999f;
        if (pitch > pitchBound) { pitch = pitchBound; D_00189E20.pitchRate = 0; }
        else if (pitch < -pitchBound) { D_00189E20.pitchRate = 0; pitch = -pitchBound; }
        aim = (char *)&D_00189E20 + 0x14E0;
        func_002AF000(aim, 1.0f, yaw, pitch);
        hero = aim - 0x14E0;
        if (D_00189E20.groundNormalZ > -0.99f) func_00283098(aim, aim, hero);
        func_PAL_L00_002D6AD8();
        if (!func_PAL_L00_002D6A08(0, 0, 0)) {
            AimCamera *camera = &D_L00_001B8C80;
            *(short *)(hero + 0x1454) = 2;
            *(float *)(hero + 0x1A0) = camera->height;
            camera = (AimCamera *)((char *)camera + 0x370);
            qcopy(aim - 0x1350, camera);
            *(float *)(hero + 0x1A4) = *(float *)(hero + 0x145C);
            func_L00_002B3EF8(0, 0.053280003f, 0.36f, 0.24434614f);
        }
    }
    if (func_L00_002D6418() || ((D_00189E20.state == 1 || D_00189E20.state == 0x1D) && D_00189E20.timer >= (((int)(D_L00_001A7CE8) * 5 + 2) / 6))) {
        if (!D_00189E20.active) {
            object = D_00189E20.targetObject;
            if (object && *(short *)(object + 0xAA) != 0x47) {
                func_00282CF0((char *)&D_00189E20 + 0x14A0, object + 0x10, (char *)&D_00189E20 + 0x80);
                func_00283098((char *)&D_00189E20 + 0x14A0, (char *)&D_00189E20 + 0x14A0, (char *)&D_00189E20 + 0x40);
                func_002A91F0((char *)&D_00189E20 + 0x14B0, object + 0xF0);
            }
            D_00189E20.active = 1;
            D_00189E20.blend.bits = 0;
            D_00189E20.blendTime = 0;
            D_00189E20.activeTime = 0;
        }
    } else if (D_00189E20.state != 1 && D_00189E20.state != 0x1D) {
        char *oldObject;
        if (!D_00189E20.active) return;
        func_PAL_L00_002D5E90();
        oldObject = D_00189E20.targetObject;
        if (oldObject && *(short *)(oldObject + 0xAA) != 0x47) {
            func_00282CF0((char *)&D_00189E20 + 0x14A0, oldObject + 0x10, (char *)&D_00189E20 + 0x80);
            func_00283098((char *)&D_00189E20 + 0x14A0, (char *)&D_00189E20 + 0x14A0, (char *)&D_00189E20 + 0x40);
            D_00189E20.blendTime = 0;
            D_00189E20.blend.value = 1.0f;
        }
        D_00189E20.active = 0;
    }
    if (D_00189E20.active) func_PAL_L00_002D5E90();
}
