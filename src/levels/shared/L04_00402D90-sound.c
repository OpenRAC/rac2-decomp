#include "common.h"
extern float IntToFloat(int);
extern int FloatToInt(float);
extern unsigned char g_sound_state[];
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int snd_set_slot_field(int, int);
extern int snd_set_voice_pitch_bend(int, int);

/* Starts and updates the racer's two engine sounds, changing their volume and pitch as it speeds up. */
void racer_update_engine_sounds(unsigned char *racer, unsigned char *vars)
{
    float elapsed, amount, original;
    if (*(int *)(vars + 0x32c) && math_fast_float_d(vars + 0x324)) {
        int handle = *(int *)(vars + 0x328);
        if (handle != -1) {
            unsigned char *record = g_sound_state + handle * 0x70;
            if (*(void **)(record + 0x88) == racer && record[0x74])
                snd_stop_voice(handle);
        }
        *(int *)(vars + 0x32c) = 0;
        *(int *)(vars + 0x328) = -1;
        *(int *)(vars + 0x324) = 0;
    }
    elapsed = *(float *)(vars + 0x30c) + *(float *)(vars + 0x27c) - 0.050000004f;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (!snd_is_voice_playing_for_owner(racer, *(int *)(vars + 0x330))) {
        if (racer[0x20] == 3)
            *(int *)(vars + 0x330) = PlayMobySound(20, 5, racer);
        else
            *(int *)(vars + 0x330) = PlayMobySound(0, 5, racer);
    }
    if (!snd_is_voice_playing_for_owner(racer, *(int *)(vars + 0x334))) {
        if (racer[0x20] == 3)
            *(int *)(vars + 0x334) = PlayMobySound(21, 5, racer);
        else
            *(int *)(vars + 0x334) = PlayMobySound(1, 5, racer);
    }
    if (snd_is_voice_playing_for_owner(racer, *(int *)(vars + 0x330))) {
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        amount = 1.0f - amount;
        snd_set_slot_field(*(int *)(vars + 0x330), FloatToInt(IntToFloat(1024) * amount));
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        snd_set_voice_pitch_bend(*(int *)(vars + 0x330), FloatToInt(amount * 2816.0f));
    }
    if (snd_is_voice_playing_for_owner(racer, *(int *)(vars + 0x334))) {
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
        snd_set_slot_field(*(int *)(vars + 0x334), FloatToInt(IntToFloat(1024) * amount));
        amount = (1.0f - original) * -2816.0f;
        snd_set_voice_pitch_bend(*(int *)(vars + 0x334), FloatToInt(amount));
    }
}
