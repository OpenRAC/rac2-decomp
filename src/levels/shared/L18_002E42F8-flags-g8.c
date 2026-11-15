#include "names.h"

extern char D_00189E20[];
extern int D_001A79F0;
extern int ref_L18_002E42F8_00;
extern char ref_L18_002E42F8_01[];
extern float func_00282C48(float);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern short func_00278E78(void);
extern void func_L18_002E0070(int, int);
extern int func_L00_002B9B88(int, int);

/* Same body as func_L00_002C8E10 plus a mode-4 early exit before the resident checks. */
/* Checks whether the hero has walked off a ledge and, if so, starts the falling state. */
int func_L18_002E42F8(void)
{
    float start[4], end[4];
    float range;
    char *hero = gHeroState;
    int falling;

    if (*(int *)(hero + 0x2294) == 0x74 || *(int *)(hero + 0x2294) == 0x67)
        return 0;
    falling = 0;
    if (*(unsigned char *)(hero + 0x1494)) {
        int motion = *(int *)(hero + 0x229C);
        if (motion == 0x11) {
            if (*(int *)(hero + 0x2298) != 1 && *(float *)(hero + 0x118) > 0.0f
                    && *(float *)(hero + 0x88) > *(float *)(hero + 0x330) - 0.4f)
                falling = 1;
        } else if (motion != 0x12 && motion != 3) {
            range = 0.2f;
            if (range < FloatAbs(*(float *)(hero + 0xF8)) + 0.07f)
                range = FloatAbs(*(float *)(hero + 0xF8)) + 0.07f;
            if (FloatAbs(*(float *)(hero + 0x330) - (*(float *)(hero + 0x88) + 0.45f)) < range
                    && (*(int *)(hero + 0x229C) != 4 || *(unsigned char *)(hero + 0x49E))
                    && *(float *)(hero + 0x24C4) > 0.8f && *(float *)(hero + 0x118) < 0.0f)
                falling = 1;
            {
                char *q = gHeroState;

                if (*(float *)(q + 0x88) < *(float *)(q + 0x330) - 0.8f
                        && (*(int *)(q + 0x229C) != 4 || *(unsigned char *)(q + 0x49E)))
                    falling = 1;
            }
        }
    }
    hero = gHeroState;
    range = 0.27f;
    if (range < FloatAbs(*(float *)(hero + 0xF8)) + 0.07f)
        FloatAbs(*(float *)(hero + 0xF8));
    if (*(int *)(hero + 0x2294) == 0x12 && *(unsigned char *)(hero + 0x49E)
            && *(float *)(hero + 0x88) < *(float *)(hero + 0x330) - 0.7f)
        falling = 1;
    {
        char *g = gHeroState;

        if (*(unsigned char *)(g + 0x22B4) == 4) {
            if (falling) {
                *(int *)(g + 0x24CC) = 0;
                SetHeroAction_L18(0x91, 1);
                return 1;
            }
            return 0;
        }
    }
    if (gCurrentMapIndex != 0xC) {
        char *resident = gHeroState;
        int motion = *(int *)(resident + 0x229C);
        if (motion != 0x11 && motion != 0x12 && motion != 7
                && *(int *)(resident + 0x2294) != 0x12 && (ref_L18_002E42F8_00 & 15) == 0) {
            float distance = 4.0f;
            if (ref_L18_002E42F8_00 % 0x3F == 0)
                distance = 16.0f;
            BuildOffsetVectorPair(start, end, 0, distance, 1.3f);
            if (CollLine(start, end, 2, *(void **)(resident + 0x2290), 0)) {
                *(short *)(resident + 0x1490) = GetCollHitMaterial();
                if (*(short *)(resident + 0x1490) == 0) {
                    start[2] = *(float *)ref_L18_002E42F8_01 - 0.01f;
                    if (!CollLine(start, end, 2, *(void **)(resident + 0x2290), 0)) {
                        if (*(int *)(resident + 0x229C) == 0x14 || *(int *)(resident + 0x24CC) == 0)
                            SetHeroAction_L18(0x67, 1);
                        else
                            SetHeroAction_L18(0x33, 1);
                        return 1;
                    }
                }
            }
        }
    }
    if (falling) {
        char *fallState = gHeroState;
        if (*(int *)(fallState + 0x229C) == 0x14 || *(int *)(fallState + 0x24CC) == 0)
            SetHeroAction_L18(0x67, 1);
        else
            SetHeroAction_L18(0x36, 1);
        PlayHeroSound(3, 0);
    }
    return falling;
}
