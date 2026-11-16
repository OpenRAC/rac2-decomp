#include "names.h"
/* func_PAL_L04_004125C8, the PAL copy of func_L04_0040DF90: the same C. */
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

/* Updates the bike engine sounds: starts the two engine loops if they are not playing and bends
   their volume and pitch with the bike speed (PAL). */
void racer_update_engine_sounds_pal(unsigned char *moby, unsigned char *vars)
{
    float elapsed, amount, original;
    if (*(int *)(vars + 0x32c) && math_fast_float_d(vars + 0x324)) {
        int handle = *(int *)(vars + 0x328);
        if (handle != -1) {
            unsigned char *record = g_sound_state + handle * 0x70;
            if (*(void **)(record + 0x88) == moby && record[0x74])
                snd_stop_voice(handle);
        }
        *(int *)(vars + 0x32c) = 0;
        *(int *)(vars + 0x328) = -1;
        *(int *)(vars + 0x324) = 0;
    }
    elapsed = *(float *)(vars + 0x30c) + *(float *)(vars + 0x27c) - 0.060000002f;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x330))) {
        if (moby[0x20] == 3)
            *(int *)(vars + 0x330) = PlayMobySound(20, 5, moby);
        else
            *(int *)(vars + 0x330) = PlayMobySound(0, 5, moby);
    }
    if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x334))) {
        if (moby[0x20] == 3)
            *(int *)(vars + 0x334) = PlayMobySound(21, 5, moby);
        else
            *(int *)(vars + 0x334) = PlayMobySound(1, 5, moby);
    }
    if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x330))) {
        amount = elapsed * 2.4999998f;
        if (amount > 1.0f) amount = 1.0f;
        amount = 1.0f - amount;
        snd_set_slot_field(*(int *)(vars + 0x330), FloatToInt(IntToFloat(1024) * amount));
        amount = elapsed * 2.4999998f;
        if (amount > 1.0f) amount = 1.0f;
        snd_set_voice_pitch_bend(*(int *)(vars + 0x330), FloatToInt(amount * 2816.0f));
    }
    if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x334))) {
        float limit;
        /* Same line on purpose: under -g a line note between the load and the
         * division adds a second nop. */
        amount = elapsed / (limit = 0.54f);
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
