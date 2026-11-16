#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { f32 f[0x300]; } Pose;

extern char g_hero_state[];
extern char g_hero_item_attach_records[];

extern void cam_set_limits_first(float, float);
extern void cam_set_limits_second(float, float);
extern void cam_set_limits_third(float, float);
extern void cam_set_limits_fourth(float, float);
extern float hero_get_direction_angle_delta(void *, int);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float ApproachValue(float *, float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);

/* func_PAL_L00_002B7AF0, the PAL copy of func_L00_002B7B80: the same C, where 40 becomes 33, 10.526316f becomes
   8.771929f (x5/6), and the pose constants 0.27f, 0.037f, 0.025f, 0.055f, 0.3f and 0.07f are scaled by 36/25. */
/* Hero pose tweaks by movement mode: per-mode joint offsets written to the level pose table, clamped (modes 2, 8, 0x82, and the 2/4 substates). */
void hero_apply_mode_pose_offsets_pal(void)
{
    float x, nx, s, a, ang, mag, yaw, x8, x82, xs;
    int mode;
    int left, right;

    if (((Hero *)g_hero_state)->h[0x1454 / 2] != 0 && ((Hero *)g_hero_state)->f[0x24B8 / 4] > 0.15f && ((Hero *)g_hero_state)->i[0x2294 / 4] != 11
        && ((Hero *)g_hero_state)->b[0x1456] == 0) {
        ((Pose *)g_hero_item_attach_records)->f[0xA8 / 4] = 0.38880002f;
        ((Pose *)g_hero_item_attach_records)->f[0xA4 / 4] = 0.053280003f;
        ((Pose *)g_hero_item_attach_records)->f[0x154 / 4] = 0.036000002f;
        ((Pose *)g_hero_item_attach_records)->f[0x158 / 4] = 0.38880002f;
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            yaw = hero_get_direction_angle_delta(((Hero *)g_hero_state)->b + 0x1440, 0);
        } else {
            yaw = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1458 / 4], ((Hero *)g_hero_state)->f[0x98 / 4]);
        }
        ((Pose *)g_hero_item_attach_records)->f[0x68 / 4] = yaw;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = -yaw;
        return;
    }
    mode = ((Hero *)g_hero_state)->i[0x2294 / 4];
    if (mode == 2) {
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        if (((Hero *)g_hero_state)->i[0x2298 / 4] == 1) {
            x = ((Hero *)g_hero_state)->f[0x1A4 / 4] * 17.0f;
            if (x > 1.4f) x = 1.4f;
            else if (x < -1.4f) x = -1.4f;
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f < x) x = math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f;
            else if (x < -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f) x = -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                if (x > 1.1f) x = 1.1f;
                else if (x < -1.1f) x = -1.1f;
                cam_set_limits_second(0.0792f, 0.43200004f);
                cam_set_limits_fourth(0.10080001f, 0.43200004f);
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) < x) x = math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]);
                else if (x < -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4])) x = -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]);
            }
            nx = -x;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = nx * 0.11f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] * 0.25f;
            s = ((Hero *)g_hero_state)->f[0x174 / 4] * 8.771929f;
            if (s > 1.0f) s = 1.0f;
            if (s < 0.0f) s = 0.0f;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] * s;
            ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x * 0.31f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = 0.0f;
            ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x * -0.15f;
            ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x * 0.7f;
            ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = math_fabs(x) * -0.15f;
            ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x) * 0.16f;
            ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = nx * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = nx * 0.3f;
            ((Pose *)g_hero_item_attach_records)->f[0x954 / 4] = math_fabs(x) * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xA04 / 4] = math_fabs(x) * 0.2f;
        } else {
            float v = ((Hero *)g_hero_state)->f[0x1A8 / 4];
            float y, ny, d, e;
            if (((Hero *)g_hero_state)->f[0x24B8 / 4] < 0.8f && ((Hero *)g_hero_state)->i[0x1B8 / 4] < 33) {
                ApproachValue(&v, 0.0f, (float)(33 - ((Hero *)g_hero_state)->i[0x1B8 / 4]) * 0.087266475f);
            }
            y = v * 0.5f;
            if (y > 0.8f) y = 0.8f;
            else if (y < -0.8f) y = -0.8f;
            y = y * math_fabs(y) * 1.25f;
            ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = y;
            ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = y;
            d = math_fabs(y);
            ny = -y;
            ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = d * 0.25f;
            ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = ny * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = ny * 0.3f;
        }
    } else if (mode == 8) {
        cam_set_limits_first(0.008f, 0.08f);
        cam_set_limits_second(0.015f, 0.08f);
        cam_set_limits_third(0.015f, 0.08f);
        cam_set_limits_fourth(0.008f, 0.1f);
        x8 = ((Hero *)g_hero_state)->f[0x1A8 / 4] * 1.6f;
        if (x8 > 1.25f) x8 = 1.25f;
        else if (x8 < -1.25f) x8 = -1.25f;
        ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -x8 * 0.52f;
        if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.28f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.28f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x8 * 1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x8 * 0.58f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x8 * -0.28f;
        if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] > 0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = 0.6f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] < -0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = -0.6f;
        ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = math_fabs(x8) * 0.2f;
        if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] > 0.2f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = 0.2f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] < -0.2f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -0.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x8) * 0.16f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -x8 * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -x8 * 0.3f;
    } else if (mode == 0x82) {
        cam_set_limits_first(0.017f, 0.33f);
        cam_set_limits_second(0.015f, 0.25f);
        cam_set_limits_third(0.015f, 0.25f);
        cam_set_limits_fourth(0.008f, 0.25f);
        x82 = ((Hero *)g_hero_state)->f[0x1A8 / 4] * 0.7f;
        if (x82 > 1.2f) x82 = 1.2f;
        else if (x82 < -1.2f) x82 = -1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -x82 * 0.52f;
        if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.28f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.28f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x82 * 1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x82 * 0.58f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x82 * -0.28f;
        if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] > 0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = 0.6f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] < -0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = -0.6f;
        ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x82) * 0.16f;
        ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = FastAddRotations(((Pose *)g_hero_item_attach_records)->f[0x64 / 4], -0.122173056f);
        if (((Hero *)g_hero_state)->f[0x24B8 / 4] > 0.1f) {
            ang = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0 / 4], ((Hero *)g_hero_state)->f[0x98 / 4]);
            mag = ((Hero *)g_hero_state)->f[0x24B8 / 4] * 0.6108653f;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -math_fast_sin_or_cos_b(ang) * mag;
            ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = FastAddRotations(((Pose *)g_hero_item_attach_records)->f[0x64 / 4], math_fast_sin_or_cos_a(ang) * mag);
            if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.47123894f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.47123894f;
            if (((Pose *)g_hero_item_attach_records)->f[0x64 / 4] > 0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = 0.47123894f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x64 / 4] < -0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = -0.47123894f;
        }
        ((Pose *)g_hero_item_attach_records)->f[0x6D4 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x624 / 4] = 0.025f;
        ((Pose *)g_hero_item_attach_records)->f[0x6D8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x628 / 4] = 0.37f;
        left = 1;
        right = 1;
        if (((Hero *)g_hero_state)->b[0x22BB] == 1) {
            right = 0;
        } else if (((Hero *)g_hero_state)->b[0x22BB] == 2) {
            left = 0;
            right = 0;
        }
        a = FastAddRotations(((Hero *)g_hero_state)->f[0x118 / 4] * 5.0f, 0.296706f);
        if (left) {
            ((Pose *)g_hero_item_attach_records)->f[0x5E8 / 4] = -0.3490659f;
            ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = -a;
            if (((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] > 0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = 0.6108653f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] < -0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = -0.6108653f;
        }
        if (right) {
            ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = a;
            ((Pose *)g_hero_item_attach_records)->f[0x698 / 4] = 0.3490659f;
            if (((Pose *)g_hero_item_attach_records)->f[0x690 / 4] > 0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = 0.6108653f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x690 / 4] < -0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = -0.6108653f;
        }
        ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -((Hero *)g_hero_state)->f[0x118 / 4] * 7.7f;
        if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] > 0.64577186f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = 0.64577186f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] < -0.64577186f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -0.64577186f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -x82 * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -x82 * 0.3f;
    } else if (((Hero *)g_hero_state)->i[0x229C / 4] == 2 || ((Hero *)g_hero_state)->i[0x229C / 4] == 4) {
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        xs = ((Hero *)g_hero_state)->f[0x1A8 / 4];
        if (xs > 1.4f) xs = 1.4f;
        else if (xs < -1.4f) xs = -1.4f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = xs * 0.29f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = xs * -0.27f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = xs * 0.87f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -xs * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -xs * 0.3f;
    }
}

extern char g_hero_state[];
extern char g_hero_item_attach_records[];
typedef struct {
    char reserved000[0x174];
    float weight;
    char reserved178[0x2C];
    float x, y;
    char reserved1AC[0x20E8];
    int mode;
    int reserved2298;
    int submode;
} CameraPlayerPrefix;
#define PLAYER (*(CameraPlayerPrefix *)D_00189E20)
extern float math_fabs(float);
typedef struct {
    char pad[0x10E0];
    float f10E0;
    char p10E4[4];
    float f10E8;
    char p10EC[0x1190 - 0x10EC];
    float f1190, f1194, f1198;
    char p119C[0x1240 - 0x119C];
    float f1240;
} MotionPose;

/* Updates hero motion response pose terms for modes 64, 75 and substates 2/4. */
void UpdateHeroMotionResponseParameters_pal(void)
{
    float negative, weight;
    if (PLAYER.mode == 64) {
        float turn, scaled;
        turn = PLAYER.x * 9.0f;
        if (turn > 0.7f) turn = 0.7f;
        else if (turn < -0.7f) turn = -0.7f;
        turn = turn * math_fabs(turn) * 1.25f;
        weight = PLAYER.weight * 16.666666f;
        negative = -turn;
        scaled = negative * 0.2f;
        ((MotionPose *)g_hero_item_attach_records)->f1240 = scaled;
        if (weight > 1.0f) weight = 1.0f;
        if (weight < 0.0f) weight = 0.0f;
        ((MotionPose *)g_hero_item_attach_records)->f10E8 = turn;
        ((MotionPose *)g_hero_item_attach_records)->f1240 = scaled * weight;
        ((MotionPose *)g_hero_item_attach_records)->f10E0 = negative * 0.35f;
        ((MotionPose *)g_hero_item_attach_records)->f1198 = turn * 1.35f;
        ((MotionPose *)g_hero_item_attach_records)->f1194 = math_fabs(turn) * 0.25f;
    } else if (PLAYER.mode == 75) {
        float turn, a, b, d, c;
        turn = PLAYER.y * 1.6f;
        if (turn > 1.25f) turn = 1.25f;
        else if (turn < -1.25f) turn = -1.25f;
        a = -turn * 0.52f;
        ((MotionPose *)g_hero_item_attach_records)->f1240 = a;
        if (a > 0.28f) ((MotionPose *)g_hero_item_attach_records)->f1240 = 0.28f;
        else if (a < -0.28f) ((MotionPose *)g_hero_item_attach_records)->f1240 = -0.28f;
        b = turn * 1.7f;
        ((MotionPose *)g_hero_item_attach_records)->f1198 = b;
        ((MotionPose *)g_hero_item_attach_records)->f10E8 = turn * 0.58f;
        if (b > 0.7f) ((MotionPose *)g_hero_item_attach_records)->f1198 = 0.7f;
        else if (b < -0.7f) ((MotionPose *)g_hero_item_attach_records)->f1198 = -0.7f;
        d = math_fabs(turn) * 0.2f;
        ((MotionPose *)g_hero_item_attach_records)->f1194 = d;
        c = 0.2f;
        if (c < d) goto store_clamp;
        c = -0.2f;
        if (d < c) {
        store_clamp:
            ((MotionPose *)g_hero_item_attach_records)->f1194 = c;
        }
        ((MotionPose *)g_hero_item_attach_records)->f1190 = math_fabs(turn) * 0.16f;
    } else if (PLAYER.submode == 2 || PLAYER.submode == 4) {
        float turn;
        turn = PLAYER.y;
        if (turn > 1.4f) turn = 1.4f;
        else if (turn < -1.4f) turn = -1.4f;
        ((MotionPose *)g_hero_item_attach_records)->f10E8 = turn * 0.29f;
        ((MotionPose *)g_hero_item_attach_records)->f1198 = turn * 0.87f;
    }
}

