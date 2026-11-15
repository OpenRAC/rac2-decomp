#include "common.h"

/* Word +4 of the player-stat block is read at an offset from the block's name: that form never
   fills a delay slot, where a bare small-data name would. */
typedef struct { int bolts; int counter; u8 suffix[0x38]; } PlayerStatBlock;
extern PlayerStatBlock D_001A79F8 __attribute__((sda));

extern int D_L05_001B1300 __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned short D_0018D030 __attribute__((nosda));
extern float func_00282E48(void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern void func_L05_0041C4E8(char *);
extern int func_00288E18(int, int);
extern int func_00288FB8(int);
extern void func_L00_0030DD70(int, int);

/* Flies the object at the cached class-0xFBF moby. On arrival it plays a sound, bumps the
   player-stat counter and deletes itself; until then it keeps turning. */
/* Moves the pickup toward the target object, speeding up as it gets close. When it arrives it counts one more pickup and removes itself. */
void func_L05_0041C1F0(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (gHomingPickupTarget != 0) {
        distance = fast_vec_dist((void *)(gHomingPickupTarget + 0x10), object + 0x10);

        if (gCurrentMapIndex[0] == 0x14) {
            SpringVectorToTarget(object + 0x10, (void *)(gHomingPickupTarget + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
        } else if (distance < 60.0f) {
            float *classData = *(float **)(object + 0x24);
            float newScale = classData[9] * 0.02222222276031971f * distance;

            *(float *)(object + 0x2C) = newScale;
            {
                float minScale = classData[9] * 0.30000001192092896f;

                if (newScale < minScale)
                    *(float *)(object + 0x2C) = minScale;
            }
            SpringVectorToTarget(object + 0x10, (void *)(gHomingPickupTarget + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
        if (distance < 0.5f) {
            if (gPlayerBolts.counter == 0) {
                if (D_0018D030 == 0 && gCurrentMapIndex[0] == 0x19)
                    RequestSubtitleVoiceLine(0xA3B, 0x92);
            } else {
                CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x1282), -1);
            }
            PlaySoundFromClassBank(0xC, 0, object, 0xFBF /* moby class 4031 */);
            gPlayerBolts.counter = gPlayerBolts.counter + 1;
            MarkMobySpawned(object);
            return;
        }
    }
    DrawGlowRingSprites_L05(object);
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), 0.01f);
}
