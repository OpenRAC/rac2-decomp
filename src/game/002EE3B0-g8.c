#include "common.h"

extern char *func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern float D_001AC248 __attribute__((sda));
extern float D_001AC240 __attribute__((sda));
extern float D_001AC244 __attribute__((sda));

/* Loads the follow speed, pull and range settings that match the follower's current state. */
void func_002EE3B0(unsigned char *owner)
{
    char *object = GetMobyMotionData(owner);
    int state;

    if (!object)
        return;
    if (*(unsigned char **)(object + 0x10))
        state = GetFollowerState(*(unsigned char **)(object + 0x10));
    else
        state = GetFollowerState(owner);
    if (state == 3) {
        D_001AC248 = 0.416666687f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 1) {
        D_001AC248 = 0.400000036f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 13) {
        D_001AC248 = 0.400000036f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 2) {
        D_001AC248 = 0.13333334f;
        D_001AC240 = 0.005f;
        D_001AC244 = 0.025f;
    } else if (state == 5) {
        D_001AC248 = 0.416666687f;
        D_001AC240 = 0.04f;
        D_001AC244 = 0.2f;
    } else if (state == 6) {
        D_001AC248 = 0.366666675f;
        D_001AC240 = 0.03f;
        D_001AC244 = 0.15f;
    } else if (state == 4) {
        D_001AC248 = 0.5f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 8) {
        D_001AC248 = 0.416666687f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 7) {
        D_001AC248 = 0.166666672f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 11) {
        D_001AC248 = 0.5f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 12) {
        float *duration = *(float **)(object + 0x154);
        D_001AC248 = duration ? *duration * (1.0f / 60.0f) : 0.166666672f;
        D_001AC240 = 0.005f;
        D_001AC244 = 0.025f;
    }
    if (*(int *)(object + 0x108) && state != 11 && state != 2 && state != 12) {
        D_001AC240 *= 0.7f;
        D_001AC244 *= 0.7f;
    }
}
