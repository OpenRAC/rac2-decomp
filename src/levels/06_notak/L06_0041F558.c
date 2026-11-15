#include "common.h"

extern int func_00282978(char *);
extern float func_00283248(float, float);
extern void func_002B0990(char *, char *, float, int, int);
extern void func_002AB8C0(char *, char *);
extern float func_002A89A8(char *, int, float);
extern float func_00282C48(float);
extern float func_002AA3A8(char *, float, float, float, float, char *);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(char *, char *, int, float, float);

/* Keeps the actor on the ground and turns its upper body toward the player while it attacks. */
void func_L06_0041F558(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float groundHeight, angle;

    UpdateColorFade(moby, vars + 0x50);
    FastDecTimer(vars + 0x24A);
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE)
        ++*(unsigned short *)(moby + 0x96);
    groundHeight = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
    if (FloatAbs(*(float *)(moby + 0x18) - groundHeight) < 10.0f) {
        SpringFloatToGoal(moby + 0x18, groundHeight, 0.00083333341171965f,
                      0.010000000707805157f, 0.18000000715255737f, vars + 0x49C);
        if (*(float *)(moby + 0x18) < groundHeight)
            *(float *)(moby + 0x18) = groundHeight;
    }
    if (FastDiffRots(*(float *)(moby + 0xF8),
                      FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14)))
            <= 2.6179940700531006f && (unsigned char)moby[0x95] == 2) {
        angle = fast_subtract_rotations(
            FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                          *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            *(float *)(moby + 0xF8));
        if (angle > 1.396263599395752f)
            angle = 1.396263599395752f;
        else if (angle < -1.396263599395752f)
            angle = -1.396263599395752f;
        *(float *)(vars + 0x588) = angle * 0.75f;
        *(float *)(vars + 0x508) = angle * 0.4f;
        UpdateEasedNode(moby, vars + 0x4A0, 1, 0.02f, 0.3f);
        UpdateEasedNode(moby, vars + 0x520, 2, 0.02f, 0.3f);
        SetValueAndStartSmoothChange(moby, vars + 0x4A0, 2.5f, 1, 1);
    }
}
