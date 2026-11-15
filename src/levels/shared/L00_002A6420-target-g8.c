#include "common.h"

typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x8];
    float heading;
    char pad9c[0x140];
    short count;
    char pad1de[0xa1a];
    char *special;
    char padbfc[0x854];
    int flag;
    char pad1454[0xe3c];
    char *object;
    char pad2294[0x8];
    int mode;
    char pad22a0[0x1f0];
    char *target;
} TargetState;

typedef struct {
    char pad[0x114];
    float pitch114;
    char gap[0x1c8 - 0x118];
    float yaw1c8;
    char gap2[0x274 - 0x1cc];
    float pitch274, yaw278;
} CameraAngles;

extern TargetState D_00189E20;
extern int D_001B19C8;
extern char *D_L00_001FACE0[];
extern CameraAngles D_L00_0025BE10;

extern char *func_002AB1F0(void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern void func_L00_002D36E0(float, float, float, void *, int);
extern void func_L00_002D3778(void *, void *, float);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L00_002AB0D8(float, float);
extern void func_L00_002AB0C0(float, float);
extern void func_L00_002AB0F0(float, float);

/* Select an unobstructed target and update the clamped pitch/yaw aim angles. */
void func_L00_002ABBA0(void)
{
    float a[4], b[4];
    int special = 0;
    int mode;
    char *obj, *info, *best;
    int i;
    float distance, angle, score, priority, bestScore, bestPriority;
    float yaw, pitch;

    if (gHeroState.special)
        special = gHeroState.flag == 0;
    mode = gHeroState.mode;
    if (mode != 1 && mode != 4 && mode != 2 && mode != 7 && mode != 0) {
        gHeroState.special = 0;
        gHeroState.target = 0;
        return;
    }
    if (!special) {
        if ((unsigned char)(gHeroState.object)[0x43] == 81)
            return;
        if (D_001B19C8 % 7 == 0) {
            bestScore = 100000000.0f;
            bestPriority = 0.0f;
            obj = D_L00_001FACE0[0];
            best = 0;
            for (i = 0; obj != 0; obj = D_L00_001FACE0[++i]) {
                info = GetMobyPrivateValue0(obj);
                if (!info)
                    continue;
                distance = vec_distance_xy(gHeroState.pos, obj + 0x10);
                if ((unsigned char)info[0x28] < distance)
                    continue;
                angle = FastMatrixHelperA(*(float *)(obj + 0x10) - gHeroState.pos[0],
                                     *(float *)(obj + 0x14) - gHeroState.pos[1]);
                angle = FastDiffRots(angle, gHeroState.heading);
                if (angle > 1.9198623895645142f)
                    continue;
                pitch = vec_distance_xy(obj + 0x10, gHeroState.pos);
                pitch = FastMatrixHelperA(pitch, gHeroState.pos[2] - *(float *)(obj + 0x18));
                pitch = FloatAbs(pitch);
                if (pitch > 1.047197699546814f)
                    continue;
                score = angle * distance + distance;
                if (obj == gHeroState.target) {
                    score -= 1.5f;
                    if (score < 0.0f)
                        score = 0.0f;
                }
                priority = (unsigned char)info[0x29];
                if (priority > bestPriority || score < bestScore) {
                    if (bestPriority < priority)
                        bestPriority = priority;
                    bestScore = score;
                    best = obj;
                }
            }
            gHeroState.target = best;
        }
        if (gHeroState.target) {
            BuildHeroRelativePoint(0, 0, 1.2f, a, 1);
            qcopy(b, gHeroState.target + 0x10);
            ApplyHeroModeTransformReversed(b, b, 0.5f);
            if (CollLine(a, b, 2, 0, 0))
                gHeroState.target = 0;
        }
    }
    if (gHeroState.target || special) {
        char *target, *targetInfo;

        target = gHeroState.target;
        if (special)
            target = gHeroState.special;
        qcopy(a, target + 0x10);
        targetInfo = GetMobyPrivateValue0(target);
        if (targetInfo) {
            if (special)
                a[2] += *(float *)(targetInfo + 0x10);
            else
                a[2] += (unsigned char)targetInfo[0x2a] * 0.125f;
        }
        if (special)
            BuildHeroRelativePoint(0.5f, 0, 0.55f, b, 1);
        else
            BuildHeroRelativePoint(0.3f, 0, 0.85f, b, 1);
        yaw = FastMatrixHelperA(a[0] - b[0], a[1] - b[1]);
        yaw = fast_subtract_rotations(yaw, gHeroState.heading);
        pitch = vec_distance_xy(a, b);
        pitch = FastMatrixHelperA(pitch, b[2] - a[2]);
        if (yaw > 1.0297443866729736f)
            yaw = 1.0297443866729736f;
        else if (yaw < -1.0297443866729736f)
            yaw = -1.0297443866729736f;
        if (pitch > 0.6108652949333191f)
            pitch = 0.6108652949333191f;
        if (pitch < -0.4363323450088501f)
            pitch = -0.4363323450088501f;
        if (gHeroState.count >= 28) {
            if (yaw > 0.2967059910297394f)
                yaw = 0.2967059910297394f;
            else if (yaw < -0.2967059910297394f)
                yaw = -0.2967059910297394f;
            pitch = 0;
        }
        if (special) {
            SetCameraLimitsSlot2(0.037f, 0.3f);
            D_L00_0025BE10.yaw1c8 = yaw;
            SetCameraLimitsSlot1(0.037f, 0.3f);
            D_L00_0025BE10.pitch114 = pitch;
        } else {
            SetCameraLimitsSlot3(0.021f, 0.27f);
            D_L00_0025BE10.pitch274 = pitch;
            D_L00_0025BE10.yaw278 = yaw * 0.7f;
            SetCameraLimitsSlot2(0.014f, 0.3f);
            D_L00_0025BE10.yaw1c8 = D_L00_0025BE10.yaw278 * 0.55f;
        }
    }
    gHeroState.special = 0;
}
