#include "common.h"

extern float D_L12_001B1C74 __attribute__((sda));
extern float D_L12_001B1C70 __attribute__((sda));
extern u8 D_L12_001B9E00[];

extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern void func_002B60B0(char *, float, float, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);

/* Sets up the path enemy on its first frame and every frame scales it and hides it if the hero is close. */
void func_L12_0041A2B8(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float rate;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x30) = 0xC8;
        *(u16 *)(moby + 0x32) = 0xC8;
        qcopy(state + 0x210, moby + 0x10);
        *(float *)(state + 0x21C) = *(float *)(moby + 0xF8);
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 0) {
            StartAnimationBlended(moby, 0, 0, 0);
        }
        {
            float half = 0.5f;
            float quarter = 0.25f;
            float fraction = 0.4f;
            float turn = 0.261799425f;
            float step = 0.00555555569f;
            float pi = 3.14159012f;
            rate = D_L12_001B1C74 * 0.016666668f;
            *(float *)(state + 0x154) = quarter;
            *(float *)(state + 0x120) = fraction;
            *(float *)(state + 0x12C) = *(float *)(state + 0x128) = *(float *)(state + 0x124) = half;
            *(float *)(state + 0x150) = turn;
            *(float *)(state + 0x14C) = step;
            *(int *)(state + 0x15C) = -1;
            *(float *)(state + 0x130) = pi;
        }
        SetControllerSpeedLimits(moby, 0.0088888891f, rate, 0.00349065894f, 0.209439546f);
        *(int *)(state + 0x11C) = 0;
        *(int *)(state + 0x258) = 0;
    }
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L12_001B1C70;
    if (*(u8 *)(moby + 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, D_L12_001B9E00) < 24.0f) {
            UpdateMobyGroundCheck(moby);
            *(u8 *)(moby + 0x6F) = 0x16;
        }
    }
}
