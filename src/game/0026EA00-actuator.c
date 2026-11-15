#include "include_asm.h"
#include "names.h"

/* Scratch-array layout and pointer updates follow RAC1 actuator_CalcPower,
 * src/game/actuator.c (OpenRAC/Lombyte, GPL-3.0). */
extern float func_00283CE0(int), func_00283180(float);
extern int func_00283CF0(float);
typedef struct {
    unsigned char kind, permanent, output, multiply;
    short delay, duration, frame, rise, fall;
    unsigned char amplitude, bias;
} WaveChannel;
extern WaveChannel D_001B5180[8];

/* Adds up all active wave channels into two output values and returns how many channels are active. */
int func_0026F810(int *out)
{
    int scratch[3][4];
    int *count;
    int *mulcount;
    int i, active = 0;

    mulcount = scratch[1];
    count = scratch[2];
    for (i = 0; i < 2; i++) {
        out[i] = 0;
        scratch[0][i] = 0;
        scratch[1][i] = 0;
        scratch[2][i] = 0;
    }
    for (i = 0; i < 8; i++) {
        WaveChannel *s;
        int phase, value;

        if (!D_001B5180[i].kind)
            continue;
        active++;
        if (!D_001B5180[i].permanent) {
            if (D_001B5180[i].duration-- <= 0)
                D_001B5180[i].kind = 0;
        }
        if (D_001B5180[i].delay) {
            D_001B5180[i].delay--;
            continue;
        }
        s = &D_001B5180[i];
        D_001B5180[i].frame++;
        value = 0;
        phase = s->frame % (s->rise + s->fall);
        switch (s->kind) {
        case 0:
            break;
        case 1:
            if (phase < s->rise)
                value = s->amplitude + s->bias;
            else
                value = s->bias;
            break;
        case 2:
            if (phase < s->rise)
                value = s->amplitude * phase / s->rise;
            else
                value = s->amplitude * (s->fall + s->rise - phase) / s->fall;
            value += s->bias;
            break;
        case 3:
            if (phase < s->rise)
                value = s->amplitude * phase / s->rise + s->bias;
            break;
        case 4:
            if (phase >= s->rise)
                value = s->amplitude * (s->fall + s->rise - phase) / s->fall + s->bias;
            break;
        case 5: {
            float angle;

            if (phase < s->fall)
                angle = IntToFloat(phase) * 3.1415927f / IntToFloat(s->fall);
            else
                angle = 3.1415927f - IntToFloat(phase - s->fall) * 3.1415927f / IntToFloat(s->rise);
            angle = FastSinOrCosA(angle);
            {
                float a = IntToFloat(s->amplitude);
                value = FloatToInt((angle * a + a) * 0.5f) + s->bias;
            }
            if (value > 255)
                value = 255;
            break;
        }
        }
        if (s->multiply) {
            scratch[0][s->output] += value;
            {
                int *p = mulcount + s->output;
                *p = *p + 1;
            }
        } else {
            out[s->output] += value;
            {
                int *p = count + s->output;
                *p = *p + 1;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        int j = i;

        if (count[j])
            out[j] /= count[j];
        if (mulcount[j]) {
            scratch[0][j] /= mulcount[j];
            out[j] = out[j] * scratch[0][j] / 255;
        }
    }
    return active;
}
