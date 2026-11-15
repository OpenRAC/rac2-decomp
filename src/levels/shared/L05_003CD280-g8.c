#include "include_asm.h"
#include "names.h"

extern int D_001A79F0;
extern float func_00282E48(void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern int func_L05_0037AAC8(int);
extern int func_002A77E0(int);
extern int func_0030CBA8(int);
extern void func_00326198(int, int);
typedef struct L05Slot40 {
    int state;
    int next;
    int pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40;
extern L05Slot40 D_002A1800[];
extern void func_0029CC50(int, int, int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern int D_L05_001AFAA0 __attribute__((sda));

extern void func_L05_003CD598(char *);

/* Flies the pickup toward the player, shrinking as it nears, and heals the player when it is
   collected. */
void func_L05_003CD280(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001AFAA0 != 0) {
        scale = fast_vec_dist((void *)(D_L05_001AFAA0 + 0x10), object + 0x10);

        if (gCurrentMapIndex == 0x14) {
            SpringVectorToTarget(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            SpringVectorToTarget(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
    check_scale:
        if (scale < 0.5f) {
            int slot = func_L05_0037AAC8(6);
            int add = D_002A1800[slot].limit;

            if (RandomIntBelow(4) != 0) {
                UpdateThrownObject(func_0030CBA8(0x1283), -1);
                add = 0x21;
            } else {
                UpdateThrownObject(func_0030CBA8(0x1284), -1);
            }
            PlaySoundFromClassBank(0xC, 0, object, 0xFBF);
            D_002A1800[slot].value += add;
            if (D_002A1800[slot].limit < D_002A1800[slot].value)
                D_002A1800[slot].value = D_002A1800[slot].limit;
            MarkMobySpawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    func_L05_003CD598(object);
}

