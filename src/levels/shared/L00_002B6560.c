#include "common.h"

extern int func_L00_002ADEA0(int);
extern void func_L00_002D34C0(void *, void *, float);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AA2E8(float *, float, float);
extern float func_00282C10(float);
extern void func_L00_002B9BB0(int, int, int);
extern void func_002E59F8(int);
/* The EE passes the three floats independently of the two integer arguments. */
extern void func_L00_002D36E0(void *, float, float, float, int);
extern int func_002761F8(void *, void *, int, int, int);

extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern char D_00188660[];
extern char D_00189E20[];
extern int D_00138320[];
extern char D_00189EA0[];

typedef struct {
    float initial, acceleration;
    int duration;
} HeroMotionEntry;

typedef struct {
    char pad[20];
    HeroMotionEntry *entries;
    int index, ticks;
    float value;
} HeroMotionSequence;

/* Apply gravity and the current jump or hovering motion to the hero's velocity. */
void func_L00_002B6560(void)
{
    float offset[4], rayEnd[4], rayStart[4], currentSpeed;
    float speed, distance;
    int near, clear;

    {
        char *hero = (char *)&gHeroState;
        int state = *(int *)(hero + 0x2294), age;

        if (!((state == 27 && *(int *)(hero + 0x1B8) < 10) ||
              (state == 137 && (age = *(int *)(hero + 0x1B8)) < 12) ||
              (state == 72 && *(int *)(hero + 0x1B8) < 13))) {
            if (*(int *)(hero + 0x1B8) < *(short *)(hero + 0x4AC)) {
                SetViewSpaceHeight(hero + 0xF0, hero + 0xF0, 0.0f);
                ApplyHeroModeTransform(hero + 0xF0, hero + 0xF0, 0.013333334f);
            } else if (*(unsigned char *)(hero + 0x49C)) {
                SetViewSpaceHeight(hero + 0xF0, hero + 0xF0, 0.0f);
                ApplyHeroModeTransform(hero + 0xF0, hero + 0xF0, 0.015000001f);
            } else {
                float fallSpeed;

                ApplyHeroModeTransform(hero + 0xF0, hero + 0xF0, *(float *)(hero + 0x520));
                fallSpeed = GetViewSpaceHeight(hero + 0xF0);
                if (fallSpeed < -*(float *)(hero + 0x4A0))
                    fallSpeed = -*(float *)(hero + 0x4A0);
                SetViewSpaceHeight(hero + 0xF0, hero + 0xF0, fallSpeed);
            }
        }
    }
    {
        char *hero = (char *)&gHeroState;

        if (*(int *)(hero + 0x2294) == 14) {
            speed = 0.116666675f;
            near = 0;
            if (gItemOwnedFlags[2] && *(short *)(hero + 0x24FC) == 0)
                near = hero_slot_item_id(3) == 3;
            {
                char *position = gHeroPosition;

                FastVecSub(offset, position, position + 0x3E0);
                distance = GetViewSpaceHeight(offset);
                clear = 1;
                if (near) {
                    char *hero = position - 0x80;

                    if (!*(unsigned char *)(hero + 0x49E)) {
                        UpdateSoundSlotObject(4, *(int *)(hero + 0x2290), 13);
                    } else {
                        int index = *(int *)(hero + 0x243C);

                        if (index != -1) {
                            char *entry = gSoundState + index * 112;

                            if (*(int *)(entry + 0x88) == *(int *)(hero + 0x2290) &&
                                *(unsigned char *)(entry + 0x74)) {
                                StopSoundVoice(index);
                            }
                        }
                        {
                            char *heroAlt = (char *)gHeroState;

                            *(int *)(heroAlt + 0x243C) = -1;
                        }
                    }
                    BuildHeroRelativePoint(rayStart, 0.0f, 0.0f, 1.0f, 1);
                    BuildHeroRelativePoint(rayEnd, 0.0f, 0.0f, 2.7f, 1);
                    if (CollLine(rayStart, rayEnd, 2, 0, 0))
                        clear = 0;
                }
            }
            if (near && clear) {
                if (distance > 2.8f)
                    speed *= 0.47f;
                else if (distance > 2.2f)
                    speed *= 0.7f;
            } else {
                if (distance > 2.1f)
                    speed *= 0.45f;
                else if (distance > 1.7f)
                    speed *= 0.7f;
            }
            if (hero_slot_item_id(3) == 3) {
                char *hero = (char *)gHeroState;

                if (*(short *)(hero + 0x24FC) == 0) {
                    if (clear)
                        speed *= 1.25f;
                }
            }
            {
                char *hero = (char *)&gHeroState;

                if (*(int *)(hero + 0x1B8) < 8) {
                    currentSpeed = GetViewSpaceHeight(hero + 0xF0);
                    if (currentSpeed < speed)
                        ApproachValue(&currentSpeed, speed, 0.041666668f);
                    SetViewSpaceHeight(hero + 0xF0, hero + 0xF0, currentSpeed);
                }
            }
        } else {
            int zero = 0;
            char *heroCheck;

            if (*(float *)(hero + 0x4B0) == 0.0f && *(float *)(hero + 0x4B4) == 0.0f)
                zero = 1;
            if ((D_00138320[0] & 0x40) || zero ||
                (heroCheck = (char *)gHeroState, *(int *)(heroCheck + 0x2294) == 18)) {
                char *hero = (char *)&gHeroState;

                if (*(float *)(hero + 0x4A8) < *(float *)(hero + 0x50C) &&
                    *(int *)(hero + 0x1B8) <= *(short *)(hero + 0x518)) {
                    *(float *)(hero + 0x4A8) +=
                        (*(float *)(hero + 0x50C) - *(float *)(hero + 0x508)) /
                        (float)*(short *)(hero + 0x518);
                    if (*(float *)(hero + 0x50C) < *(float *)(hero + 0x4A8))
                        *(float *)(hero + 0x4A8) = *(float *)(hero + 0x50C);
                    *(float *)(hero + 0x4B0) +=
                        square_root(*(float *)(hero + 0x4A8) * 2.0f * *(float *)(hero + 0x520)) -
                        *(float *)(hero + 0x4B4) - *(float *)(hero + 0x4B0);
                }
            }
            {
                char *hero = (char *)&gHeroState;

                if (*(int *)(hero + 0x1B8) >= *(short *)(hero + 0x4AC) &&
                    *(float *)(hero + 0x4B0) > 0.0f) {
                    OffsetPointInViewSpace(hero + 0xF0, hero + 0xF0, *(float *)(hero + 0x4B0));
                    *(float *)(hero + 0x4B4) += *(float *)(hero + 0x4B0);
                    *(float *)(hero + 0x4B0) = 0.0f;
                }
            }
            {
                char *hero = (char *)&gHeroState;

                if (*(unsigned char *)(hero + 0x49D) &&
                    *(int *)(hero + 0x1B8) >= *(int *)(hero + 0x430) &&
                    *(int *)(hero + 0x1B8) < *(int *)(hero + 0x434)) {
                    HeroMotionSequence *sequence = (HeroMotionSequence *)(hero + 0x430);

                    sequence->ticks++;
                    while (sequence->index == -1 || sequence->ticks >= sequence->entries[sequence->index].duration) {
                        sequence->ticks = 0;
                        sequence->index++;
                        if (sequence->entries[sequence->index].initial != -999999.0f)
                            sequence->value = sequence->entries[sequence->index].initial * 0.00027777778450399637f;
                    }
                    if (sequence->ticks > 0)
                        sequence->value += sequence->entries[sequence->index].acceleration * 0.00027777778450399637f;
                    OffsetPointInViewSpace((char *)&gHeroState + 0xF0,
                                     (char *)&gHeroState + 0xF0, sequence->value);
                }
            }
        }
    }
}
