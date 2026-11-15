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

extern TargetState g_hero_state;
extern int D_001B19C8;
extern char *D_L00_001FACE0[];
extern CameraAngles D_L00_0025BE10;

extern char *moby_get_private_value_0(void *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern void hero_build_relative_point(float, float, float, void *, int);
extern void hero_apply_mode_transform_reversed(void *, void *, float);
extern int CollLine(void *, void *, int, int, int);
extern void cam_set_limits_third(float, float);
extern void cam_set_limits_second(float, float);
extern void cam_set_limits_fourth(float, float);

/* Select an unobstructed target and update the clamped pitch/yaw aim angles. */
void UpdateHeroAutoAimAngles(void)
{
    float a[4], b[4];
    int special = 0;
    int mode;
    char *obj, *info, *best;
    int i;
    float distance, angle, score, priority, bestScore, bestPriority;
    float yaw, pitch;

    if (g_hero_state.special)
        special = g_hero_state.flag == 0;
    mode = g_hero_state.mode;
    if (mode != 1 && mode != 4 && mode != 2 && mode != 7 && mode != 0) {
        g_hero_state.special = 0;
        g_hero_state.target = 0;
        return;
    }
    if (!special) {
        if ((unsigned char)(g_hero_state.object)[0x43] == 81)
            return;
        if (D_001B19C8 % 7 == 0) {
            bestScore = 100000000.0f;
            bestPriority = 0.0f;
            obj = D_L00_001FACE0[0];
            best = 0;
            for (i = 0; obj != 0; obj = D_L00_001FACE0[++i]) {
                info = moby_get_private_value_0(obj);
                if (!info)
                    continue;
                distance = vec_distance_xy(g_hero_state.pos, obj + 0x10);
                if ((unsigned char)info[0x28] < distance)
                    continue;
                angle = mat_fast_helper_a(*(float *)(obj + 0x10) - g_hero_state.pos[0],
                                     *(float *)(obj + 0x14) - g_hero_state.pos[1]);
                angle = FastDiffRots(angle, g_hero_state.heading);
                if (angle > 1.9198623895645142f)
                    continue;
                pitch = vec_distance_xy(obj + 0x10, g_hero_state.pos);
                pitch = mat_fast_helper_a(pitch, g_hero_state.pos[2] - *(float *)(obj + 0x18));
                pitch = math_fabs(pitch);
                if (pitch > 1.047197699546814f)
                    continue;
                score = angle * distance + distance;
                if (obj == g_hero_state.target) {
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
            g_hero_state.target = best;
        }
        if (g_hero_state.target) {
            hero_build_relative_point(0, 0, 1.2f, a, 1);
            qcopy(b, g_hero_state.target + 0x10);
            hero_apply_mode_transform_reversed(b, b, 0.5f);
            if (CollLine(a, b, 2, 0, 0))
                g_hero_state.target = 0;
        }
    }
    if (g_hero_state.target || special) {
        char *target, *targetInfo;

        target = g_hero_state.target;
        if (special)
            target = g_hero_state.special;
        qcopy(a, target + 0x10);
        targetInfo = moby_get_private_value_0(target);
        if (targetInfo) {
            if (special)
                a[2] += *(float *)(targetInfo + 0x10);
            else
                a[2] += (unsigned char)targetInfo[0x2a] * 0.125f;
        }
        if (special)
            hero_build_relative_point(0.5f, 0, 0.55f, b, 1);
        else
            hero_build_relative_point(0.3f, 0, 0.85f, b, 1);
        yaw = mat_fast_helper_a(a[0] - b[0], a[1] - b[1]);
        yaw = fast_subtract_rotations(yaw, g_hero_state.heading);
        pitch = vec_distance_xy(a, b);
        pitch = mat_fast_helper_a(pitch, b[2] - a[2]);
        if (yaw > 1.0297443866729736f)
            yaw = 1.0297443866729736f;
        else if (yaw < -1.0297443866729736f)
            yaw = -1.0297443866729736f;
        if (pitch > 0.6108652949333191f)
            pitch = 0.6108652949333191f;
        if (pitch < -0.4363323450088501f)
            pitch = -0.4363323450088501f;
        if (g_hero_state.count >= 28) {
            if (yaw > 0.2967059910297394f)
                yaw = 0.2967059910297394f;
            else if (yaw < -0.2967059910297394f)
                yaw = -0.2967059910297394f;
            pitch = 0;
        }
        if (special) {
            cam_set_limits_third(0.037f, 0.3f);
            D_L00_0025BE10.yaw1c8 = yaw;
            cam_set_limits_second(0.037f, 0.3f);
            D_L00_0025BE10.pitch114 = pitch;
        } else {
            cam_set_limits_fourth(0.021f, 0.27f);
            D_L00_0025BE10.pitch274 = pitch;
            D_L00_0025BE10.yaw278 = yaw * 0.7f;
            cam_set_limits_third(0.014f, 0.3f);
            D_L00_0025BE10.yaw1c8 = D_L00_0025BE10.yaw278 * 0.55f;
        }
    }
    g_hero_state.special = 0;
}
