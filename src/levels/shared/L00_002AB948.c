#include "names.h"
extern unsigned char D_00189E20[];
extern unsigned char D_L00_0025BE10[];
extern int func_00282948(int *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);

/* Adapted from RAC1's hero_idle_and_animation.c (GPL-3.0).
 * Refreshes four idle rotation targets and copies them to their manipulators.
 */
/* Picks new random turn targets for four idle body parts when their timers run out, then applies them. */
void func_L00_002AB948(void) {
    char *base = (char *)gHeroState;
    int *timers;
    char *heroBase;
    int i, jointIndex;
    char *jointTable;

    if (*(int *)(base + 0x2294) != 0) return;
    if (*(unsigned char *)(*(int *)(base + 0x2290) + 0x43) != 0) return;
    timers = (int *)(base + 0x11F0);
    heroBase = base;
    jointTable = D_L00_0025BE10;
    for (i = 0; i < 4; i++) {
        char *targetBase;
        if (FastFloatHelperD(&timers[i])) {
            if (i == 0) {
                int *firstTimer;
                *(float *)(heroBase + 0x11B8) = RandomSignedFloatRange(0.174532949924469f, 0.523598849773407f);
                firstTimer = (int *)(gHeroState + 0x11F0);
                *firstTimer = RandomIntRange(0x46, 0x96);
            } else if (i == 1) {
                *(float *)((char *)timers - 0x28) = RandomSignedFloatRange(0.174532949924469f, 0.523598849773407f);
                timers[1] = RandomIntRange(0x28, 0x5A);
            } else if (i == 2) {
                *(float *)((char *)timers - 0x18) = RandomSignedFloatRange(0.2617994248867035f, 0.8726646900177002f);
                timers[2] = RandomIntRange(0x28, 0x5A);
            } else {
                float oldValue, newValue;
                *(float *)(heroBase + i * 0x10 + 0x11B4) = RandomFloatRange(-0.0872664749622345f, 0.523598849773407f);
                oldValue = *(float *)(heroBase + i * 0x10 + 0x11B8);
                newValue = RandomSignedFloatRange(0.349065899848938f, 0.9599311947822571f);
                *(float *)(heroBase + i * 0x10 + 0x11B8) = newValue;
                if ((oldValue <= 0 && newValue <= 0) || (oldValue >= 0 && newValue >= 0))
                    *(float *)(heroBase + i * 0x10 + 0x11B8) = -*(float *)(heroBase + i * 0x10 + 0x11B8);
                timers[i] = RandomIntRange(0x23, 0x46);
            }
        }
        targetBase = heroBase + i * 0x10;
        jointIndex = i + 13;
        base = (char *)(jointIndex * 0xB0);
        {
            char *jointEntry = jointTable + (int)base;
            *(float *)(jointEntry + 0x68) = *(float *)(targetBase + 0x11B8);
            *(float *)(jointEntry + 0x64) = *(float *)(targetBase + 0x11B4);
        }
    }
}
