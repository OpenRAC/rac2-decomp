#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned char D_00188660[];
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern int func_002E5F40(int, int);

/* Starts and updates the racer's two engine sounds, changing their volume and pitch as it speeds up. */
void func_L04_0040DF90(unsigned char *racer, unsigned char *vars)
{
    float elapsed, amount, original;
    if (*(int *)(vars + 0x32c) && FastFloatHelperD(vars + 0x324)) {
        int handle = *(int *)(vars + 0x328);
        if (handle != -1) {
            unsigned char *record = gSoundState + handle * 0x70;
            if (*(void **)(record + 0x88) == racer && record[0x74])
                StopSoundVoice(handle);
        }
        *(int *)(vars + 0x32c) = 0;
        *(int *)(vars + 0x328) = -1;
        *(int *)(vars + 0x324) = 0;
    }
    elapsed = *(float *)(vars + 0x30c) + *(float *)(vars + 0x27c) - 0.050000004f;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (!IsVoicePlayingForOwner(racer, *(int *)(vars + 0x330))) {
        if (racer[0x20] == 3)
            *(int *)(vars + 0x330) = PlayMobySound(20, 5, racer);
        else
            *(int *)(vars + 0x330) = PlayMobySound(0, 5, racer);
    }
    if (!IsVoicePlayingForOwner(racer, *(int *)(vars + 0x334))) {
        if (racer[0x20] == 3)
            *(int *)(vars + 0x334) = PlayMobySound(21, 5, racer);
        else
            *(int *)(vars + 0x334) = PlayMobySound(1, 5, racer);
    }
    if (IsVoicePlayingForOwner(racer, *(int *)(vars + 0x330))) {
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        amount = 1.0f - amount;
        SetSoundSlotField(*(int *)(vars + 0x330), FloatToInt(IntToFloat(1024) * amount));
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        SetVoicePitchBend(*(int *)(vars + 0x330), FloatToInt(amount * 2816.0f));
    }
    if (IsVoicePlayingForOwner(racer, *(int *)(vars + 0x334))) {
        float limit;
        /* Same line on purpose: under -g a line note between the load and the
         * division adds a second nop. */
        amount = elapsed / (limit = 0.45f);
        original = amount;
        limit = 0.85f;
        if (amount < limit) {
            amount = amount * 0.9411764f + 0.2f;
        } else {
            amount -= limit;
            amount = (1.0f - amount) * 0.8f + 0.2f;
        }
        SetSoundSlotField(*(int *)(vars + 0x334), FloatToInt(IntToFloat(1024) * amount));
        amount = (1.0f - original) * -2816.0f;
        SetVoicePitchBend(*(int *)(vars + 0x334), FloatToInt(amount));
    }
}
