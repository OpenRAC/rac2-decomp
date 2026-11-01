#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002B7AF0);

#include "common.h"
extern char D_00189E20[];
extern char D_L00_0025BE10[];
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
extern float func_00282C48(float);
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
void func_PAL_L00_002B88A0(void)
{
    float negative, weight;
    if (PLAYER.mode == 64) {
        float turn, scaled;
        turn = PLAYER.x * 9.0f;
        if (turn > 0.7f) turn = 0.7f;
        else if (turn < -0.7f) turn = -0.7f;
        turn = turn * func_00282C48(turn) * 1.25f;
        weight = PLAYER.weight * 16.666666f;
        negative = -turn;
        scaled = negative * 0.2f;
        ((MotionPose *)D_L00_0025BE10)->f1240 = scaled;
        if (weight > 1.0f) weight = 1.0f;
        if (weight < 0.0f) weight = 0.0f;
        ((MotionPose *)D_L00_0025BE10)->f10E8 = turn;
        ((MotionPose *)D_L00_0025BE10)->f1240 = scaled * weight;
        ((MotionPose *)D_L00_0025BE10)->f10E0 = negative * 0.35f;
        ((MotionPose *)D_L00_0025BE10)->f1198 = turn * 1.35f;
        ((MotionPose *)D_L00_0025BE10)->f1194 = func_00282C48(turn) * 0.25f;
    } else if (PLAYER.mode == 75) {
        float turn, a, b, d, c;
        turn = PLAYER.y * 1.6f;
        if (turn > 1.25f) turn = 1.25f;
        else if (turn < -1.25f) turn = -1.25f;
        a = -turn * 0.52f;
        ((MotionPose *)D_L00_0025BE10)->f1240 = a;
        if (a > 0.28f) ((MotionPose *)D_L00_0025BE10)->f1240 = 0.28f;
        else if (a < -0.28f) ((MotionPose *)D_L00_0025BE10)->f1240 = -0.28f;
        b = turn * 1.7f;
        ((MotionPose *)D_L00_0025BE10)->f1198 = b;
        ((MotionPose *)D_L00_0025BE10)->f10E8 = turn * 0.58f;
        if (b > 0.7f) ((MotionPose *)D_L00_0025BE10)->f1198 = 0.7f;
        else if (b < -0.7f) ((MotionPose *)D_L00_0025BE10)->f1198 = -0.7f;
        d = func_00282C48(turn) * 0.2f;
        ((MotionPose *)D_L00_0025BE10)->f1194 = d;
        c = 0.2f;
        if (c < d) goto store_clamp;
        c = -0.2f;
        if (d < c) {
        store_clamp:
            ((MotionPose *)D_L00_0025BE10)->f1194 = c;
        }
        ((MotionPose *)D_L00_0025BE10)->f1190 = func_00282C48(turn) * 0.16f;
    } else if (PLAYER.submode == 2 || PLAYER.submode == 4) {
        float turn;
        turn = PLAYER.y;
        if (turn > 1.4f) turn = 1.4f;
        else if (turn < -1.4f) turn = -1.4f;
        ((MotionPose *)D_L00_0025BE10)->f10E8 = turn * 0.29f;
        ((MotionPose *)D_L00_0025BE10)->f1198 = turn * 0.87f;
    }
}

